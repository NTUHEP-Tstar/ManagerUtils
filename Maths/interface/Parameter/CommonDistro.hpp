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
#ifndef MANAGERUTILS_MATHS_PARAMETER_COMMONDISTRO_HPP
#define MANAGERUTILS_MATHS_PARAMETER_COMMONDISTRO_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"

namespace mgr {

/*******************************************************************************
*   Efficiency - all efficiency related structures obtained here
*******************************************************************************/

namespace Efficiency
{
/*******************************************************************************
*   Interaction flags and constants
*******************************************************************************/
extern const bool shortest_interval;
extern const bool central_interval;

/***********************************************************************************
* Returns the parameter for a selection efficiency with "passed" passed number of *
* of events and "total" total number of events. Assumes: Baysian with uniform     *
* prior functions                                                                 *
* @param  passed Passed number of events                                          *
* @param  total  Total number of events                                           *
* @return        Returned value                                                   *
***********************************************************************************/
extern Parameter Default( double passed,  double total );

/********************************************************************
* General wrapper function for the TEfficiency::Bayesian functions *
********************************************************************/
extern Parameter Bayesian(
  double passed,
  double total,
  double confidencelevel,
  bool   confidencemethod,
  double alpha,
  double beta
  );

// TODO:: Add extra method
};// Efficiency



namespace Poisson
{
/********************************************************************
* Get the error interval of Poisson interval base on a observation *
* @param  obs input observation                                    *
* @return     Paramter with asymmetric error                       *
********************************************************************/
extern Parameter Default( double obs );
};// Poisson

}/* mgr */




#endif/* end of include guard: MANAGERUTILS_MATHS_EFFICIENCY_HPP */
