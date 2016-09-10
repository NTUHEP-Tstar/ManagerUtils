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

//------------------------------------------------------------------------------
//   General function: writing a double as a floating point string
//   with given precision. Notice, that precisions higher than 8
//   or smaller than 0 will be rounded down to 10.
//------------------------------------------------------------------------------
extern std::string FloatingPoint( double, const int precision );

//------------------------------------------------------------------------------
//   Latex style string format
//   Both will be in the form of
//        {central_value}^{upper_error}_{lower_error}
//   With the Scientific option moving a common exponent factor outside like
//        {central_value}^{upper_error}_{lower_error} \times 10^{exp}
//   if exp != 0
//
//   If the precision is set to be non-negative
//   The precision represents the number of digits to display for behind the
//   decimal point for the central value. And number of precision of the error will
//   be one greater than that of the central value
//
//   If the precision is set to negative, (only possible for floating point notation)
//   It will dump all of the digits (stripping trailing zeros)
//------------------------------------------------------------------------------
extern std::string FloatingPoint( const Parameter&, const int precision=-1. );
extern std::string Scientific   ( const Parameter&, const unsigned sig );

//------------------------------------------------------------------------------
//   Higgs combine data card format
//------------------------------------------------------------------------------
extern std::string HiggsDataCard( const Parameter& );


#endif /* end of include guard: MANAGERUTILS_MATHS_PARAMETERFORMAT_HPP */
