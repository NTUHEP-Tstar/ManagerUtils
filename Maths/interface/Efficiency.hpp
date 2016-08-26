/*******************************************************************************
 *
 *  Filename    : Efficiency.hpp
 *  Description : Wraper function for our parameter to TEfficiency class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_EFFICIENCY_HPP
#define MANAGERUTILS_MATHS_EFFICIENCY_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"

//------------------------------------------------------------------------------
//   Interaction flags and constants
//------------------------------------------------------------------------------
extern const bool SHORTEST_INTERVAL ;
extern const bool CENTRAL_INTERVAL  ;
extern const double ONESIGMA_INTERVAL ;
extern const double TWOSIGMA_INTERVAL ;

// Default method
//   - Baysian with uniform priory
//   - 1 sigma confidence level, shortest interval method
Parameter Efficiency( double passed,  double total );


// General wrapper method
Parameter BayesianEfficiency(
   double passed, double total,
   double confidencelevel,
   bool   confidencemethod,
   double alpha, double beta
);

// TODO:: Add extra method

#endif /* end of include guard: MANAGERUTILS_MATHS_EFFICIENCY_HPP */
