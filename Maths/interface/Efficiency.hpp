/*******************************************************************************
*
*  Filename    : Efficiency.hpp
*  Description : Wraper function for our parameter to TEfficiency class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Wrapper functions for storing selection efficiencies to the Parameter
*  objects. Mainly powered by the TEfficiency static functions
*
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_EFFICIENCY_HPP
#define MANAGERUTILS_MATHS_EFFICIENCY_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"


/*******************************************************************************
*   Interaction flags and constants
*******************************************************************************/
extern const bool SHORTEST_INTERVAL;
extern const bool CENTRAL_INTERVAL;
extern const double ONESIGMA_INTERVAL;
extern const double TWOSIGMA_INTERVAL;


/***********************************************************************************
 * Returns the parameter for a selection efficiency with "passed" passed number of *
 * of events and "total" total number of events. Assumes: Baysian with uniform     *
 * prior functions                                                                 *
 * @param  passed Passed number of events                                          *
 * @param  total  Total number of events                                           *
 * @return        Returned value                                                   *
 ***********************************************************************************/

Parameter Efficiency( double passed,  double total );


/********************************************************************
 * General wrapper function for the TEfficiency::Bayesian functions *
 ********************************************************************/
Parameter BayesianEfficiency(
   double passed,
   double total,
   double confidencelevel,
   bool   confidencemethod,
   double alpha,
   double beta
   );

// TODO:: Add extra method


/********************************************************************
 * Get the error interval of Poisson interval base on a observation *
 * @param  obs input observation                                    *
 * @return     Paramter with asymmetric error                       *
 ********************************************************************/
Parameter Poisson( double obs );



#endif/* end of include guard: MANAGERUTILS_MATHS_EFFICIENCY_HPP */
