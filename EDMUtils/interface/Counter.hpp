/*******************************************************************************
*
*  Filename    : Counter.hpp
*  Description : Class exposed to EMD framework to allow for run wide caching
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Inspired by edm::MergeableCounter, rewritten for <double>
*******************************************************************************/
#ifndef MANAGERUTILS_EDMUTILS_COUNTER_HPP
#define MANAGERUTILS_EDMUTILS_COUNTER_HPP

namespace mgr {

class Counter
{
public:
  // constructor
  Counter();
  Counter( const double );
  virtual
  ~Counter();

  // Most have this function to allow run level storage
  bool mergeProduct( const Counter& nextCounter );

  // Saving value
  double value;
};

}/* mgr  */

#endif/* end of include guard: MANAGERUTILS_EDMUTILS_COUNTER_HPP */
