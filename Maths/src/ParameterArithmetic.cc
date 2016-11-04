/*******************************************************************************
*
*  Filename    : ParameterArithmetic.cc
*  Description : One Line descrption of file contents
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <float.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_vector.h>
#include <vector>

using namespace std;


/*******************************************************************************
*   Approximate Loglikelihood functions and appro
*******************************************************************************/
static double
LogLikelihood( double x, const Parameter& parm )
{
   const double hatx = parm.CentralValue();
   const double V    = parm.AbsUpperError() * parm.AbsLowerError();
   const double Vp   = parm.AbsUpperError() - parm.AbsLowerError();
   if( parm.AbsUpperError() == 0 && x > hatx ){
      return -DBL_MAX;
   } else if( parm.AbsLowerError() == 0 && x < hatx ){
      return -DBL_MAX;
   } else if( parm.AbsLowerError() == 0 && parm.AbsLowerError() == 0 ){
      return 0;
   } else {
      return -0.5  * ( x-hatx ) * ( x-hatx ) / ( V + ( x-hatx )*Vp );
   }
}

/******************************************************************************/

static double
WeightFactor( double x, const Parameter& parm )
{
   const double hatx = parm.CentralValue();
   const double V    = parm.AbsUpperError() * parm.AbsLowerError();
   const double Vp   = parm.AbsUpperError() - parm.AbsLowerError();
   if( parm.AbsUpperError() == 0 && x > hatx ){
      return 0;
   } else if( parm.AbsLowerError() == 0 && x < hatx ){
      return 0;
   } else {
      return -0.5 * ( 2*V+Vp*( x-hatx ) ) / ( ( V + Vp*( x-hatx ) ) * ( V+Vp*( x-hatx ) ) );
   }
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
      const double x      = gsl_vector_get( inputlist, i );
      const double hatx   = parmlist.at( i ).CentralValue();
      const double weight = WeightFactor( x, parmlist.at( i ) );

      // computing sum
      sumx          += x;
      loglikelihood += LogLikelihood( x, parmlist.at( i ) );

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

   double prodx         = 1;
   double loglikelihood = 0;

   // Computing results for Lagrangian results
   for( size_t i = 0; i < parmlist.size(); ++i  ){
      const double x      = gsl_vector_get( inputlist, i );
      const double hatx   = parmlist.at( i ).CentralValue();
      const double weight = WeightFactor( x, parmlist.at( i ) );

      // computing sum
      prodx         *= x;
      loglikelihood += LogLikelihood( x, parmlist.at( i ) );

      // Setting partial differential results
      gsl_vector_set( outputlist, i, ( x-hatx )*weight * x  - k * u );
   }

   gsl_vector_set( outputlist, parmlist.size(),   prodx - u  );
   gsl_vector_set( outputlist, parmlist.size()+1, loglikelihood + 0.5 );

   return GSL_SUCCESS;
}

/******************************************************************************/

static void
IterateSolver( gsl_multiroot_fsolver* solver )
{
   static const double precision     = 1e-10;
   static const size_t max_iteration = 1e+4;
   int status;
   size_t iteration = 0;

   do {
      iteration++;
      status = gsl_multiroot_fsolver_iterate( solver );
      if( status ){ break; }
      status = gsl_multiroot_test_residual( solver->f, precision );
   } while( status == GSL_CONTINUE && iteration < max_iteration );
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
   *   x_i  = \hat{x}_i \pm \sigma_i^+
   *   k    = Average[ sigma_i * WeightFactor( hatx_i \pm sigma_i) ]
   *   u    = (sum x_i) + sqrt( sum  sigma_i * sigma_i )
   *******************************************************************************/
   for( size_t i = 0; i < parmlist.size(); ++i  ){
      const Parameter& p = parmlist.at( i );

      sum       += p.CentralValue();
      errupsum  += p.AbsUpperError() * p.AbsUpperError();
      errlowsum += p.AbsLowerError() * p.AbsLowerError();
      ksumup    += p.AbsUpperError() * WeightFactor( p.CentralValue() + p.AbsUpperError(), p );
      ksumdown  += -p.AbsLowerError() * WeightFactor( p.CentralValue() - p.AbsLowerError(), p );

      gsl_vector_set( xlower, i, p.CentralValue() - p.AbsLowerError() );
      gsl_vector_set( xupper, i, p.CentralValue() + p.AbsUpperError() );
   }

   gsl_vector_set( xupper, parmlist.size(),   ksumup / parmlist.size() );
   gsl_vector_set( xupper, parmlist.size()+1, sum + sqrt( errupsum ) );
   gsl_vector_set( xlower, parmlist.size(),   ksumdown / parmlist.size() );
   gsl_vector_set( xlower, parmlist.size()+1, sum - sqrt( errlowsum ) );

   // Getting upper bound value:
   gsl_multiroot_fsolver_set( solver, &func, xupper );
   IterateSolver( solver );
   const double uppervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

   // Getting lower bound value
   gsl_multiroot_fsolver_set( solver, &func, xlower );
   IterateSolver( solver );
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

   // Declaring GSL objects
   gsl_multiroot_fsolver* solver = gsl_multiroot_fsolver_alloc(
      gsl_multiroot_fsolver_hybrids,
      dim
      );

   gsl_multiroot_function func = {
      &ProdMultiDimFunc,
      dim,
      (void*)( &parmlist )
   };

   gsl_vector* xupper = gsl_vector_alloc( dim );
   gsl_vector* xlower = gsl_vector_alloc( dim );

   // Declaring helper variables
   double ksumup    = 0;
   double ksumdown  = 0;
   double cenprod   = 1;
   double produp    = 1;
   double proddown  = 1;
   double errupsum  = 0;
   double errlowsum = 0;

   /*******************************************************************************
   *   Guessing initial value for upper/lower error :
   *   x_i  = \hat{x}_i + \sigma_i^+
   *   k    = Average[ x_i * sigma_i * WeightFactor( hatx_i \pm sigma_i ) / u ]
   *   u    = (sum x_i) + sqrt( sum  (sigma_i * sigma_i)/hatx_i )
   *******************************************************************************/
   for( size_t i = 0; i < parmlist.size(); ++i  ){
      const Parameter& p = parmlist.at( i );
      const double xup   = p.CentralValue() + p.AbsUpperError();
      const double xdown = p.CentralValue() - p.AbsLowerError();

      cenprod  *= p.CentralValue();
      produp   *= xup;
      proddown *= xdown;

      errupsum  += p.RelUpperError() * p.RelUpperError();
      errlowsum += p.RelLowerError() * p.RelLowerError();
      ksumup    += p.AbsUpperError() * xup * WeightFactor( xup, p );
      ksumdown  += -p.AbsLowerError() * xdown  * WeightFactor( xdown, p );

      gsl_vector_set( xupper, i, xup );
      gsl_vector_set( xlower, i, xdown );
   }
   gsl_vector_set( xupper, parmlist.size(),   ksumup / parmlist.size() / produp );
   gsl_vector_set( xupper, parmlist.size()+1, cenprod * ( 1 +  sqrt( errupsum ) ) );
   gsl_vector_set( xlower, parmlist.size(),   ksumdown / parmlist.size() );
   gsl_vector_set( xlower, parmlist.size()+1, cenprod * ( 1 - sqrt( errlowsum ) ) );

   // Getting upper bound value
   gsl_multiroot_fsolver_set( solver, &func, xupper );
   IterateSolver( solver );
   const double uppervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

   // Getting lower bound value:
   gsl_multiroot_fsolver_set( solver, &func, xlower );
   IterateSolver( solver );
   const double lowervalue = gsl_vector_get( solver->x, parmlist.size() + 1 );

   // Freeing GSL objects
   gsl_multiroot_fsolver_free( solver );
   gsl_vector_free( xupper );
   gsl_vector_free( xlower );

   // Returning results
   return Parameter(
      cenprod,
      uppervalue - cenprod,
      cenprod - lowervalue
      );
}
