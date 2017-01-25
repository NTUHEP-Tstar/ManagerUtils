/*******************************************************************************
*
*  Filename    : Paramter_CommonDistro_Poisson.cc
*  Description : Implementation for Poisson mesurement functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter/CommonDistro.hpp"
#include "ManagerUtils/Maths/interface/Compute.hpp"
#include <cmath>
#include <gsl/gsl_roots.h>

namespace mgr {
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

/******************************************************************************/

static double
PoissonGSL(
  double lambda,
  void*  parm
  )
{
  const double obs = *( (double*)parm );
  return PoissonLikelihood( obs, obs ) - PoissonLikelihood( lambda, obs ) - 0.5;
}

/*******************************************************************************
*   Implementing static member function of Poisson namespace class
*******************************************************************************/

Parameter
Poisson::Default( const double obs )
{
  gsl_root_fsolver* solver = gsl_root_fsolver_alloc( gsl_root_fsolver_brent );

  gsl_function func;
  func.function = &PoissonGSL;
  func.params   = (void*)( &obs );

  gsl_root_fsolver_set( solver, &func, obs, 2*obs );
  gsl::IterateSolver( solver );
  const double upper = gsl_root_fsolver_root( solver );

  gsl_root_fsolver_set( solver, &func, gsl::epsilon, obs );
  gsl::IterateSolver( solver );
  const double lower = gsl_root_fsolver_root( solver );

  gsl_root_fsolver_free( solver );

  return Parameter(
    obs,
    upper-obs,
    obs-lower
    );
}

}/* mgr */
