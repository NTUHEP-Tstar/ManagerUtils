/*******************************************************************************
 *
 *  Filename    : Parameter.cc
 *  Description : Implmentation of arithmetics for Parameter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;

//------------------------------------------------------------------------------
//   Constructor and desctructor
//------------------------------------------------------------------------------
Parameter::Parameter()
{
   _centralValue = 0;
   _error_up = 0;
   _error_down = 0;
}

Parameter::Parameter(
   const double c ,
   const double error_up ,
   const double error_down ):
   _centralValue(c),
   _error_up( error_up ),
   _error_down( error_down)
{
   if( _error_up < 0 ){
      cerr << "Warning! Upper error is small than zero! Assuming flipped sign" << endl;
      _error_up = - _error_up;
   }
   if( _error_down < 0 ){
      cerr << "Warning! Lower error is small than zero! Assuming flipped sign" << endl;
      _error_down = - _error_down;
   }
}

Parameter::Parameter( const Parameter& x )
{
   *this = x;
}

Parameter::~Parameter(){}

//------------------------------------------------------------------------------
//   Assignment operator
//------------------------------------------------------------------------------
Parameter& Parameter::operator=( const Parameter& x )
{
   _centralValue = x._centralValue;
   _error_up      = x._error_up;
   _error_down    = x._error_down ;
   return *this;
}
