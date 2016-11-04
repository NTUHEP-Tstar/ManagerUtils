/*******************************************************************************
*
*  Filename    : Efficiency.cc
*  Description : Implementation for efficiency wrappers
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Efficiency.hpp"
#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "TEfficiency.h"
#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

/*******************************************************************************
*   Defining constants
*******************************************************************************/
extern const bool SHORTEST_INTERVAL   = true;
extern const bool CENTRAL_INTERVAL    = false;
extern const double ONESIGMA_INTERVAL = 0.6826895;
extern const double TWOSIGMA_INTERVAL = 0.9544997;

/*******************************************************************************
*   Default Method
*******************************************************************************/
Parameter
Efficiency( double passed,  double total )
{
   static const double uniform_priory_alpha = 1.;
   static const double uniform_priory_beta  = 1.;
   return BayesianEfficiency(
      passed, total,
      ONESIGMA_INTERVAL,
      SHORTEST_INTERVAL,
      uniform_priory_alpha,
      uniform_priory_beta
      );
}

/*******************************************************************************
*   General Wrapper functions
*******************************************************************************/
Parameter
BayesianEfficiency(
   double passed, double total,
   double confidencelevel,
   bool confidencemethod,
   double alpha, double beta
   )
{
   const double central = ( passed + alpha - 1. )/( total + alpha + beta - 2. );
   const double err_up  = TEfficiency::Bayesian(
      total, passed,
      confidencelevel,
      alpha, beta,
      true,// For upper boundary
      confidencemethod
      ) - central;
   const double err_down = central - TEfficiency::Bayesian(
      total, passed,
      confidencelevel,
      alpha, beta,
      false,// For lower boundary
      confidencemethod
      );
   return Parameter( central, err_up, err_down );
}

/*******************************************************************************
*   Poisson functions
*******************************************************************************/
static double
PoissonLikelihood(
   const double lambda,
   const double obs
   )
{
   return obs * log( lambda ) - lambda;
}

static double
PoissonGSL(
   double lambda,
   void*  parm
   )
{
   const double obs = *( (double*)parm );
   return PoissonLikelihood( obs, obs ) - PoissonLikelihood( lambda, obs ) - 0.5;
}

Parameter
Poisson( const double obs )
{
   int status;
   unsigned iter;
   static const unsigned max_iter = 100;

   gsl_root_fsolver* solver = gsl_root_fsolver_alloc( gsl_root_fsolver_brent );

   gsl_function func;
   func.function = &PoissonGSL;
   func.params   = (void*)( &obs );

   // Solving upper region
   double lo = obs;
   double hi = 2*obs;

   gsl_root_fsolver_set( solver, &func, lo, hi );
   iter = 0;

   do {
      iter++;
      status = gsl_root_fsolver_iterate( solver );
      lo     = gsl_root_fsolver_x_lower( solver );
      hi     = gsl_root_fsolver_x_upper( solver );
      status = gsl_root_test_interval( lo, hi, 0, 1e-7 );
      if (status == GSL_SUCCESS) {
         break;
      }
   } while( status == GSL_CONTINUE && iter < max_iter );

   const double upper = gsl_root_fsolver_root( solver );

   // sovling lower error
   lo = 0.0001;
   hi = obs;

   gsl_root_fsolver_set( solver, &func, lo, hi );
   iter = 0;

   do {
      iter++;
      status = gsl_root_fsolver_iterate( solver );
      lo     = gsl_root_fsolver_x_lower( solver );
      hi     = gsl_root_fsolver_x_upper( solver );
      status = gsl_root_test_interval( lo, hi, 0, 1e-7 );
      if (status == GSL_SUCCESS) {
         break;
      }
   } while( status == GSL_CONTINUE && iter < max_iter );

   const double lower = gsl_root_fsolver_root( solver );

   gsl_root_fsolver_free( solver );

   return Parameter(
      obs,
      upper-obs,
      obs-lower
      );
}
