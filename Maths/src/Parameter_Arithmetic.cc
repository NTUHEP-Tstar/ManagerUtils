/*******************************************************************************
*
*  Filename    : ParameterArithmetic.cc
*  Description : One Line descrption of file contents
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include "ManagerUtils/Maths/interface/Compute.hpp"

#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_vector.h>
#include <iostream>
#include <vector>

using namespace std;

namespace mgr {

/*******************************************************************************
*   Constant values
*******************************************************************************/
static const double minerrprod = 1e-4;

/*******************************************************************************
*   Approximate Loglikelihood functions and first derivative.
*   Note that GSl solver doesn't play well with discontinuous functions, so we
*   need to force sigma+ * sigma- to be a finitely small value instead of 0.
*******************************************************************************/
static double
LogLikelihood( double x, const Parameter& parm )
{
  const double hatx = parm.CentralValue();
  const double V    = parm.AbsUpperError() * parm.AbsLowerError() + minerrprod;
  const double Vp   = parm.AbsUpperError() - parm.AbsLowerError();
  const double num  = ( x-hatx )* ( x - hatx );
  const double de   = V + ( x-hatx ) * Vp;
  const double ans  = -0.5  * num / de;
  return ans;
}

/******************************************************************************/

static double
WeightFactor( double x, const Parameter& parm )
{
  const double hatx = parm.CentralValue();
  const double V    = parm.AbsUpperError() * parm.AbsLowerError() + minerrprod;
  const double Vp   = parm.AbsUpperError() - parm.AbsLowerError();
  const double ans  = -0.5 * ( 2*V+Vp*( x-hatx ) ) / ( ( V + Vp*( x-hatx ) ) * ( V+Vp*( x-hatx ) ) );
  return ans;
}

/*******************************************************************************
*
*   SumMultiDimFunc
*   The GSL function representation for the system equation we are attempting
*   to solve:
*      (x_i - \hat{x}_i ) * w_i = k u / x_i;
*      \prod x_i                 = u;
*      \sum  LogLikelihood       = - 0.5;
*   for the input:
*      x_i = gsl_vector_get(x,i)
*      k   = gsl_vector_get(x,N+1)
*      u   = gsl_vector_get(x,N+2)
*   The input params will contain:
*      The vector of Parameter class instances
*      the desired value of the LogLikelihood function
*
*******************************************************************************/
static int
SumMultiDimFunc(
  const gsl_vector* inputlist,
  void*             params,
  gsl_vector*       outputlist )
{
  const vector<Parameter>& parmlist = *( ( vector<Parameter>* )params );

  const double k = gsl_vector_get( inputlist, parmlist.size() );
  const double u = gsl_vector_get( inputlist, parmlist.size()+1 );

  double sumx          = 0;
  double loglikelihood = 0;

  // Computing results for Lagrangian results
  for( size_t i = 0; i < parmlist.size(); ++i  ){
    const Parameter& parm = parmlist.at( i );

    const double x      = gsl_vector_get( inputlist, i );
    const double hatx   = parm.CentralValue();
    const double weight = WeightFactor( x, parm );

    // computing sum
    sumx          += x;
    loglikelihood += LogLikelihood( x, parm );

    // Setting partial differential results
    gsl_vector_set( outputlist, i, ( x-hatx )*weight - k );
  }

  gsl_vector_set( outputlist, parmlist.size(),   sumx - u  );
  gsl_vector_set( outputlist, parmlist.size()+1, loglikelihood + 0.5 );

  return GSL_SUCCESS;
}

/******************************************************************************/

static int
ProdMultiDimFunc(
  const gsl_vector* inputlist,
  void*             params,
  gsl_vector*       outputlist )
{
  const vector<Parameter>& parmlist = *( ( vector<Parameter>* )params );

  const double k = gsl_vector_get( inputlist, parmlist.size() );
  const double u = gsl_vector_get( inputlist, parmlist.size()+1 );

  double prodx = 1;

  for( size_t i = 0; i < parmlist.size(); ++i  ){
    prodx *= gsl_vector_get( inputlist, i );
  }

  double loglikelihood = 0;

  // Computing results for Lagrangian results
  for( size_t i = 0; i < parmlist.size(); ++i  ){
    const Parameter& parm = parmlist.at( i );

    const double x      = gsl_vector_get( inputlist, i );
    const double hatx   = parm.CentralValue();
    const double weight = WeightFactor( x, parm );

    // computing sum
    loglikelihood += LogLikelihood( x, parm );

    // Setting partial differential results
    gsl_vector_set( outputlist, i, ( x-hatx )*weight * x  - k * prodx );
  }

  gsl_vector_set( outputlist, parmlist.size(),   prodx - u  );
  gsl_vector_set( outputlist, parmlist.size()+1, loglikelihood + 0.5 );


  return GSL_SUCCESS;
}


/*******************************************************************************
*   Main function for interfacing with user
*******************************************************************************/
Parameter
Sum( const vector<Parameter>& parmlist )
{
  // Defining dimension of GSL problem
  const size_t dim = parmlist.size() + 2;

  // Declaring GSL objects
  gsl_multiroot_fsolver* solver = gsl_multiroot_fsolver_alloc(
    gsl_multiroot_fsolver_hybrids,
    dim
    );

  gsl_multiroot_function func = {
    &SumMultiDimFunc,
    dim,
    (void*)( &parmlist )
  };

  gsl_vector* xupper = gsl_vector_alloc( dim );
  gsl_vector* xlower = gsl_vector_alloc( dim );

  // Declaring helper variables
  double ksumup    = 0;
  double ksumdown  = 0;
  double sum       = 0;
  double errupsum  = 0;
  double errlowsum = 0;

  /*******************************************************************************
  *   Guessing initial value for upper/lower error :
  *   x_i  = \hat{x}_i \pm \sigma_i^+/2
  *   k    = Average[ sigma_i * WeightFactor( hatx_i \pm sigma_i) ]
  *   u    = (sum x_i) + sqrt( sum  sigma_i * sigma_i /4 )
  *   Smalling the error avoids bad solutions when summing extremely different
  *   central values together.
  *******************************************************************************/
  for( size_t i = 0; i < parmlist.size(); ++i  ){
    const Parameter& p = parmlist.at( i );

    sum       += p.CentralValue();
    errupsum  += p.AbsUpperError() * p.AbsUpperError() / 4.;
    errlowsum += p.AbsLowerError() * p.AbsLowerError() / 4.;
    ksumup    += p.AbsUpperError() * WeightFactor( p.CentralValue() + p.AbsUpperError(), p );
    ksumdown  += -p.AbsLowerError() * WeightFactor( p.CentralValue() - p.AbsLowerError(), p );

    gsl_vector_set( xlower, i, p.CentralValue() - p.AbsLowerError()/2. );
    gsl_vector_set( xupper, i, p.CentralValue() + p.AbsUpperError()/2. );
  }

  gsl_vector_set( xupper, parmlist.size(),   ksumup / parmlist.size() );
  gsl_vector_set( xupper, parmlist.size()+1, sum + sqrt( errupsum ) );
  gsl_vector_set( xlower, parmlist.size(),   ksumdown / parmlist.size() );
  gsl_vector_set( xlower, parmlist.size()+1, sum - sqrt( errlowsum ) );

  // Getting upper bound value:
  gsl_multiroot_fsolver_set( solver, &func, xupper );
  gsl::IterateSolver( solver );
  const double uppervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

  // Getting lower bound value
  gsl_multiroot_fsolver_set( solver, &func, xlower );
  gsl::IterateSolver( solver );
  const double lowervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

  // Freeing GSL objects
  gsl_multiroot_fsolver_free( solver );
  gsl_vector_free( xupper );
  gsl_vector_free( xlower );

  // Returning results
  return Parameter(
    sum,
    uppervalue - sum,
    sum - lowervalue
    );
}

/******************************************************************************/

Parameter
Prod( const vector<Parameter>& parmlist )
{
  // Defining dimension of GSL problem
  const size_t dim = parmlist.size() + 2;


  // Declaring helper variables
  double kup        = 1;
  double kdown      = 1;
  double produp     = 1;
  double proddown   = 1;
  double cenval     = 1;
  double uppervalue = 1;
  double lowervalue = 1;

  vector<Parameter> normparmlist;

  gsl_multiroot_fsolver* solver = gsl_multiroot_fsolver_alloc(
    gsl_multiroot_fsolver_hybrids,
    dim
    );

  gsl_multiroot_function func = {
    &ProdMultiDimFunc,
    dim,
    (void*)( &normparmlist )
  };

  gsl_vector* xupper = gsl_vector_alloc( dim );
  gsl_vector* xlower = gsl_vector_alloc( dim );

  /*******************************************************************************
  *   Guessing initial value for upper/lower error :
  *   x_i  = \hat{x}_i + \sigma_i^+
  *   k    = Average[ x_i * sigma_i * WeightFactor( hatx_i \pm sigma_i ) / u ]
  *   u    = (sum x_i) + sqrt( sum  (sigma_i * sigma_i)/hatx_i )
  *******************************************************************************/
  // Declaring GSL objects
  for( size_t i = 0; i < parmlist.size(); ++i  ){
    const Parameter& p    = parmlist.at( i );
    const Parameter normp = p.NormParam();

    const double hatx  = 1;
    const double xup   = 1 + ( p.RelUpperError() + minerrprod )/1.2;
    const double xdown = 1 - ( p.RelLowerError() + minerrprod )/1.2;

    produp   *= xup;
    proddown *= xdown;

    kup   *= fabs( ( xup-hatx ) * xup * WeightFactor( xup, normp ) );
    kdown *= fabs( ( xdown-hatx ) * xdown  * WeightFactor( xdown, normp ) );

    gsl_vector_set( xupper, i, xup );
    gsl_vector_set( xlower, i, xdown );

    normparmlist.push_back( normp );
  }

  gsl_vector_set( xupper, parmlist.size(),   -pow( kup, 1./parmlist.size() ) / produp );
  gsl_vector_set( xupper, parmlist.size()+1, produp  );
  gsl_vector_set( xlower, parmlist.size(),   pow( kdown,  1./parmlist.size() ) / proddown );
  gsl_vector_set( xlower, parmlist.size()+1, proddown );

  // Getting upper bound value
  gsl_multiroot_fsolver_set( solver, &func, xupper );
  gsl::IterateSolver( solver );
  uppervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

  // Getting lower bound value:
  gsl_multiroot_fsolver_set( solver, &func, xlower );
  gsl::IterateSolver( solver );
  lowervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

  // Freeing GSL objects
  gsl_multiroot_fsolver_free( solver );
  gsl_vector_free( xupper );
  gsl_vector_free( xlower );

  if( uppervalue < cenval || cenval < lowervalue ){
    cerr << "[PROD] Warnig! nagative error detected!" << endl;

    for( const auto& parm : parmlist ){
      cout << parm.CentralValue() << " " << parm.AbsUpperError() << " " << parm.AbsLowerError() << endl;
    }
  }


  for( const auto& parm : parmlist ){
    cenval     *= parm.CentralValue();
    uppervalue *= parm.CentralValue();
    lowervalue *= parm.CentralValue();
  }

  // Returning results
  return Parameter(
    cenval,
    uppervalue - cenval,
    cenval - lowervalue
    );

}/* mgr */
}
