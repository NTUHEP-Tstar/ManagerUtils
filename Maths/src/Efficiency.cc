/*******************************************************************************
 *
 *  Filename    : Efficiency.cc
 *  Description : Implementation for efficiency wrappers
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/Maths/interface/Efficiency.hpp"
#include "TEfficiency.h"
//------------------------------------------------------------------------------
//   Defining constants
//------------------------------------------------------------------------------
extern const bool SHORTEST_INTERVAL = true;
extern const bool CENTRAL_INTERVAL  = false;
extern const double ONESIGMA_INTERVAL = 0.6826895 ;
extern const double TWOSIGMA_INTERVAL = 0.9544997 ;

//------------------------------------------------------------------------------
//   Default method
//------------------------------------------------------------------------------

Parameter Efficiency( double passed,  double total )
{
   static const double uniform_priory_alpha = 1. ;
   static const double uniform_priory_beta  = 1. ;
   return BayesianEfficiency(
      passed, total,
      ONESIGMA_INTERVAL,
      SHORTEST_INTERVAL,
      uniform_priory_alpha,
      uniform_priory_beta
   );
}

//------------------------------------------------------------------------------
//   General Wrappers
//------------------------------------------------------------------------------
Parameter BayesianEfficiency(
   double passed, double total,
   double confidencelevel,
   bool   confidencemethod,
   double alpha, double beta
)
{
   const double central = (passed + alpha - 1.)/(total + alpha + beta - 2.);
   const double err_up  = TEfficiency::Bayesian(
      total, passed ,
      confidencelevel,
      alpha, beta,
      true  ,  // For upper boundary
      confidencemethod
   ) - central ;
   const double err_down = central - TEfficiency::Bayesian(
      total, passed ,
      confidencelevel,
      alpha, beta,
      false  ,  // For lower boundary
      confidencemethod
   );
   return Parameter( central , err_up, err_down );
}
