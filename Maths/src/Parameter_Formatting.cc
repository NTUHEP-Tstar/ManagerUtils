/*******************************************************************************
 *
 *  Filename    : Parameter_Formatting.cc
 *  Description : String Formatting functions for Parameter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <cstdlib>
#include <cmath>

using namespace std;

string Parameter::LatexFormat( int precision ) const
{
   char buffer_1[1024];
   char buffer_2[1024];
   double cen = _centralValue;
   double up  = _error_up;
   double down= _error_down;
   int    exp = 0;

   if( fabs(cen) < 0.001 ){
      while( fabs(cen) < 1. ){
         cen*=10;
         up*=10;
         down*=10;
         --exp;
      }
   } else if( fabs(cen) > 10000 ){
      while( fabs(cen) > 10.  ){
         cen  /=10;
         up   /=10;
         down /=10;
         ++exp;
      }
   }

   char float_format[64];
   char buff_1_format[64];
   if( precision > 0 ){
      double temp = cen;
      while( temp < 1 ){
         temp *= 10 ;
         ++precision;
      }
      sprintf(float_format,"%%.%dlf",precision);
   } else {
      sprintf(float_format,"%%lg");
   }


   if( up == down ){
      if( up == 0. ){
         sprintf( buff_1_format , "%s" , float_format );
         sprintf( buffer_1 , buff_1_format , cen );
      } else {
         sprintf( buff_1_format, "%s\\pm%s" , float_format, float_format );
         sprintf( buffer_1, buff_1_format , cen , up );
      }
   } else {
      sprintf( buff_1_format , "%s^{%s}_{%s}" , float_format, float_format, float_format );
      sprintf( buffer_1, buff_1_format , cen, up , down );
   }

   if( exp != 0 ){
      if( up == 0. ){
         sprintf( buffer_2 , "$%s\\times 10^{%d}$" , buffer_1 , exp );
      } else {
         sprintf( buffer_2 , "$(%s)\\times 10^{%d}$" , buffer_1, exp );
      }
   } else {
      sprintf( buffer_2 , "$%s$" , buffer_1 );
   }

   return buffer_2;
}

string Parameter::DataCardFormat() const
{
   char buffer[1024];
   if( _error_up == _error_down ){
      sprintf( buffer, "%lg" , 1.+RelAvgError() );
   } else {
      sprintf( buffer, "%lg/%lg" , 1.+RelUpperError() , 1.-RelLowerError() );
   }
   return buffer;
}
