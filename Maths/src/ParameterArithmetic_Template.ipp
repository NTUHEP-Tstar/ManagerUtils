/*******************************************************************************
*
*  Filename    : ParameterArithmetic_Template.ipp
*  Description : Template functions implementations
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Main goal is to reduce variadic functions in to standard input format
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_PARAMETERARITHMETIC_TEMPLATE_IPP
#define MANAGERUTILS_MATHS_PARAMETERARITHMETIC_TEMPLATE_IPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include <vector>
/*******************************************************************************
*   Template functions change function to
*******************************************************************************/
template<typename Tf>
std::vector<Parameter>
MakeVector( Tf x )
{
   return std::vector<Parameter>( {x} );
}

template<typename Tf, typename ... Ts>
std::vector<Parameter>
MakeVector( Tf x, Ts ... arg )
{
   Parameter first( x );
   std::vector<Parameter> ans = MakeVector( arg ... );
   ans.insert( ans.begin(), first );
   return ans;
}

/*******************************************************************************
*   Section Name
*******************************************************************************/
template<typename Tf, typename ... Ts>
Parameter
Sum( Tf x,  Ts ... args )
{
   return Sum( MakeVector( x, args ... ) );
}

template<typename Tf, typename ... Ts>
Parameter
Prod( Tf x, Ts ... args )
{
   return Prod( MakeVector( x, args ... ) );
}

#endif/* end of include guard: MANAGERUTILS_MATHS_PARAMETERARITHMETIC_TEMPLATE_IPP */
