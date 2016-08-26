/*******************************************************************************
 *
 *  Filename    : ParameterFormat.hpp
 *  Description : Producing a string representing a Parameter with a specific format
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_PARAMETERFORMAT_HPP
#define MANAGERUTILS_MATHS_PARAMETERFORMAT_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <string>

extern std::string FloatingPoint( const Parameter&, int precision );

extern std::string Scientific( const Parameter&, unsigned sig );

extern std::string HiggsDataCard( const Parameter&, unsigned precision = 6 );


#endif /* end of include guard: MANAGERUTILS_MATHS_PARAMETERFORMAT_HPP */
