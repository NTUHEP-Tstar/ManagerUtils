/*******************************************************************************
*
*  Filename    : ParameterArithmetic.hpp
*  Description : Arithmetic opertion with good error propagation estimates
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Main reference from here:
*
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_PARAMETER_ARITHMETIC_HPP
#define MANAGERUTILS_MATHS_PARAMETER_ARITHMETIC_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/Common/interface/Variadic.hpp"
#include <vector>

namespace mgr {
/*******************************************************************************
*   Main calculation functions, do mot call from outside
*   - Implemented in ParamterArithmethic.cc
*******************************************************************************/
Parameter Sum( const std::vector<Parameter>& );
Parameter Prod( const std::vector<Parameter>& );

/*******************************************************************************
*   Template variadic functions for better interfacing
*   ex. Sum( a, b, c , d );
*******************************************************************************/
template<typename Tf, typename ... Ts>
Parameter
Sum( Tf x,  Ts ... args )
{
  return Sum( MakeVector<Parameter>( x, args ... ) );
}

template<typename Tf, typename ... Ts>
mgr::Parameter
Prod( Tf x, Ts ... args )
{
  return Prod( MakeVector<Parameter>( x, args ... ) );
}
} /* mgr */


#endif/* end of include guard: MANAGERUTILS_MATHS_PARAMETERARITHMETIC_HPP */
