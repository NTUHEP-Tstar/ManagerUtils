/*******************************************************************************
*
*  Filename    : Compute.hpp
*  Description : Common values and functions for computation
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_GSLSETTINGS_HPP
#define MANAGERUTILS_MATHS_GSLSETTINGS_HPP

#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_roots.h>

namespace mgr {

namespace gsl{
/*******************************************************************************
*   GSL settings constants
*******************************************************************************/
extern const double   epsilon;
extern const unsigned max_iteration;

/*******************************************************************************
*   GSL iterator solver
*******************************************************************************/
extern void IterateSolver( gsl_multiroot_fsolver* solver );
extern void IterateSolver( gsl_root_fsolver* solver );

/*******************************************************************************
*   Statistical Interval values
*******************************************************************************/
};

namespace stat {
extern const double onesigma_interval;
extern const double twosigma_interval;

} /* stat */


}/* mgr */

#endif/* end of include guard: MANAGERUTILS_MATHS_GSLSETTINGS_HPP */
