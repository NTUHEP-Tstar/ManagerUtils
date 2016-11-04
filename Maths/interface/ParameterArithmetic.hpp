/*******************************************************************************
*
*  Filename    : ParameterArithmetic.hpp
*  Description : Arithmetic opertion with good error propagation estimates
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Main reference from here:
*
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_PARAMETERARITHMETIC_HPP
#define MANAGERUTILS_MATHS_PARAMETERARITHMETIC_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include <vector>

/*******************************************************************************
*   Main calculation functions
*   - Implemented in ParamtereArithmethic.cc
*******************************************************************************/
Parameter Sum( const std::vector<Parameter>& );
Parameter Prod( const std::vector<Parameter>& );

/*******************************************************************************
*   Template variadic functions for better interfacing
*   ex. Sum( a, b, c , d );
*******************************************************************************/
template<typename Tf, typename ... Ts>
Parameter Sum( Tf x,  Ts ... args );

template<typename Tf, typename ... Ts>
Parameter Prod( Tf x, Ts ... args );

#include "ManagerUtils/Maths/src/ParameterArithmetic_Template.ipp"


#endif/* end of include guard: MANAGERUTILS_MATHS_PARAMETERARITHMETIC_HPP */
