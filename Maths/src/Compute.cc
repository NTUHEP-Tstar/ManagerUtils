/*******************************************************************************
*
*  Filename    : Compute.cc
*  Description : Definition of variables and function defined in Common.hpp
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Compute.hpp"


namespace mgr {

namespace gsl {
/*******************************************************************************
*   GSL settings constants
*******************************************************************************/
extern const double   epsilon         = 1e-10;
extern const unsigned max_iteration = 1e+4;

/*******************************************************************************
*   GSL iterator solver
*******************************************************************************/
extern void
IterateSolver( gsl_multiroot_fsolver* solver )
{
  int status;
  size_t iteration = 0;

  do {
    iteration++;
    status = gsl_multiroot_fsolver_iterate( solver );
    if( status ){ break; }
    status = gsl_multiroot_test_residual( solver->f, epsilon );

  } while( status == GSL_CONTINUE && iteration < max_iteration );
}

/******************************************************************************/

extern void
IterateSolver( gsl_root_fsolver* solver )
{
  int status;
  size_t iter = 0;
  double lo;
  double hi;

  do {
    iter++;
    status = gsl_root_fsolver_iterate( solver );
    lo     = gsl_root_fsolver_x_lower( solver );
    hi     = gsl_root_fsolver_x_upper( solver );
    status = gsl_root_test_interval( lo, hi, 0, epsilon );
    if( status == GSL_SUCCESS ){
      break;
    }
  } while( status == GSL_CONTINUE && iter < max_iteration );
}

}; /* namespace gsl  */

/*******************************************************************************
*   Statistical Interval values
*******************************************************************************/
namespace stat {

extern const double onesigma_interval = 0.6826895;
extern const double twosigma_interval = 0.9544997;

} /* stat */


}/* mgr */
