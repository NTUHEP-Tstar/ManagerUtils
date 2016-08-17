/*******************************************************************************
 *
 *  Filename    : Parameter_Arithmatics.cc
 *  Description : Arithmatics operator for asymmetric errors
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Note:
 *    * All assuming 0 correlation
 *    * Using simple but wrong algorithm for asymmetric errors
 *  TODO: Update to http://www.phas.ubc.ca/~oser/p509/Lec_10.pdf
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <cmath>

using namespace std;

//------------------------------------------------------------------------------
//   Key Arithmatics
//------------------------------------------------------------------------------
Parameter& Parameter::operator+=( const Parameter& x )
{
   _centralValue += x._centralValue;
   _error_up      = sqrt(_error_up   *_error_up    + x._error_up  *x._error_up  );
   _error_down    = sqrt(_error_down *_error_down  + x._error_down*x._error_down);
   return *this;
}

Parameter& Parameter::operator*=( const Parameter& x )
{
   _error_up      = sqrt( x._centralValue *x._centralValue*_error_up   *_error_up     + _centralValue* _centralValue * x._error_up   *x._error_up  );
   _error_down    = sqrt( x._centralValue *x._centralValue*_error_down *_error_down  + _centralValue* _centralValue * x._error_down *x._error_down);
   _centralValue *= x._centralValue;
   return *this;
}

Parameter& Parameter::operator*=( const double x )
{
   _centralValue *= x;
   _error_up *= fabs(x);
   _error_down *= fabs(x);
   return *this;
}

Parameter& Parameter::operator/=( const double x )
{
   _centralValue /= x;
   _error_up /= fabs(x);
   _error_down /= fabs(x);
   return *this;
}

//------------------------------------------------------------------------------
//   Extended functions
//------------------------------------------------------------------------------
Parameter Parameter::operator+( const Parameter& x ) const
{
   Parameter ans( *this );
   ans+=x;
   return ans;
}

Parameter Parameter::operator*( const Parameter& x ) const
{
   Parameter ans( *this );
   ans *= x;
   return ans;
}

Parameter Parameter::operator*( const double x ) const
{
   Parameter ans( *this );
   ans *= x;
   return ans;
}

Parameter Parameter::operator/( const double x ) const
{
   Parameter ans(*this);
   ans /= x ;
   return ans;
}

Parameter operator*( const double y , const Parameter& x )
{
   return x * y ;
}


Parameter operator/( const double y, const Parameter& x )
{
   const double centralValue = y / x._centralValue;
   const double err_up       = centralValue * x.RelUpperError();
   const double err_dw       = centralValue * x.RelLowerError();
   return Parameter( centralValue, err_up, err_dw ); 
}
