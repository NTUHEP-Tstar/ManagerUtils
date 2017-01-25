/*******************************************************************************
*
*  Filename    : Efficiency.cc
*  Description : Implementation for efficiency wrappers
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Compute.hpp"
#include "ManagerUtils/Maths/interface/Parameter/CommonDistro.hpp"
#include "TEfficiency.h"

namespace mgr {

/*******************************************************************************
*   Defining static constants
*******************************************************************************/
const bool Efficiency::shortest_interval = true;
const bool Efficiency::central_interval  = false;

/*******************************************************************************
*   Default Method
*******************************************************************************/
Parameter
Efficiency::Default( double passed,  double total )
{
  static const double uniform_priory_alpha = 1.;
  static const double uniform_priory_beta  = 1.;
  return Bayesian(
    passed, total,
    stat::onesigma_interval,
    shortest_interval,
    uniform_priory_alpha,
    uniform_priory_beta
    );
}

/*******************************************************************************
*   General Wrapper functions
*******************************************************************************/
Parameter
Efficiency::Bayesian(
  double passed,
  double total,
  double confidencelevel,
  bool   confidencemethod,
  double alpha,
  double beta
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

}/* mgr */
