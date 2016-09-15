/*******************************************************************************
*
*  Filename    : Parameter_Formatting.cc
*  Description : String Formatting functions for Parameter class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string
FloatingPoint( double x, const int precision )
{
   char buffer[100];
   char retstr[1024];
   unsigned index;
   if( precision < 0 ){
      // if request indefinite precision, try 8 and strip trailing zeros
      sprintf( buffer, "%%.8lf" );
   } else {
      sprintf( buffer, "%%.%df", precision );
   }

   sprintf( retstr, buffer, x );

   if( precision < 0 ){
      index = strlen( retstr )-1;

      while( retstr[index] == '0'  ){
         retstr[index] = '\0';// wiping to end of string character
         if( index == 0 ){ break; }
         --index;
      }

      if( retstr[index] == '.' ){
         retstr[index] = '\0';
      }
   }
   return retstr;
}

string
FloatingPoint( const Parameter& x,  const int precision )
{
   char full_string[256];

   const string cen = precision >= 0 ?
                      FloatingPoint( x.CentralValue(),  precision ) :
                      FloatingPoint( x.CentralValue(),  -1 );
   const string up = precision >= 0 ?
                      FloatingPoint( x.AbsUpperError(), precision ) :
                      FloatingPoint( x.AbsUpperError(), -1 );
   const string lo = precision >= 0 ?
                      FloatingPoint( x.AbsLowerError(), precision ) :
                      FloatingPoint( x.AbsLowerError(), -1 );

   if( x.AbsUpperError() == x.AbsLowerError() ){
      if( x.AbsUpperError() == 0. ){
         sprintf( full_string, "$%s$", cen.c_str() );
      } else {
         sprintf( full_string, "$%s\\pm%s$", cen.c_str(), up.c_str() );
      }
   } else {
      sprintf( full_string, "$%s^{+%s}_{-%s}$", cen.c_str(),
         up.c_str(), lo.c_str() );
   }
   return full_string;
}

string
Scientific( const Parameter& x, const unsigned precision )
{
   char base_string[256];
   char full_string[256];
   int exponent = 0;

   double cen = x.CentralValue();
   double up  = x.AbsUpperError();
   double lo  = x.AbsLowerError();

   while( fabs( cen ) > 10 ){
      exponent++;
      cen /= 10;
      up  /= 10;
      lo  /= 10;
   }

   while( fabs( cen ) < 1. ){
      exponent--;
      cen *= 10;
      up  *= 10;
      lo  *= 10;
   }

   const string censtr = FloatingPoint( cen, precision );
   const string upstr  = FloatingPoint( up, precision  );
   const string lostr  = FloatingPoint( lo, precision  );

   if( up == lo ){
      if( up == 0 ){
         sprintf( base_string, "%s", censtr.c_str() );
      } else {
         sprintf( base_string, "%s\\pm%s", censtr.c_str(), upstr.c_str() );
      }
   } else {
      sprintf( base_string, "%s^{+%s}_{-%s}", censtr.c_str(),
         upstr.c_str(), lostr.c_str() );
   }

   if( exponent == 0 ){
      sprintf( full_string, "$%s$", base_string );
   } else {
      if( up == lo ){// Special case for symmetric errors
         sprintf( full_string, "$(%s) \\times 10^{%d}$", base_string,
            exponent );
      } else {
         sprintf( full_string, "$%s \\times 10^{%d}$", base_string, exponent );
      }
   }
   return full_string;
}

string
HiggsDataCard( const Parameter& x )
{
   char buffer[1024];
   if( x.CentralValue() == 0 &&
       x.AbsUpperError() == 0 &&
       x.AbsLowerError() == 0 ){
      return "--";// special case for null parameter
   } else if( x.AbsUpperError() == x.AbsLowerError() ){
      sprintf( buffer, "%lg", 1.+x.RelAvgError() );
   } else {
      sprintf( buffer, "%lg/%lg", 1.+ x.RelUpperError(),
         1.- x.RelLowerError() );
   }
   return buffer;
}
