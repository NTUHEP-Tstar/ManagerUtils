/*******************************************************************************
 *
 *  Filename    : Parameter_Formatting.cc
 *  Description : String Formatting functions for Parameter class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

string FloatingPoint( const Parameter& x,  int precision )
{
   char central_format[64];
   char error_format[64];
   char full_format[64];
   char full_string[256];

   const double cen = x.CentralValue();
   const double up  = x.AbsUpperError();
   const double lo  = x.AbsLowerError();

   if( precision >= 0 ){
      sprintf( central_format, "%%.%dlf" , precision );
      sprintf( error_format  , "%%.%dlf" , precision+1 );
   } else {
      sprintf( central_format, "%%lg" );
      sprintf( error_format  , "%%lg" );
   }

   if( up == lo ){
      if( up == 0. ){
         sprintf( full_format, "%s" , central_format );
         sprintf( full_string, full_format, cen  );
      } else {
         sprintf( full_format, "%s\\pm%s" , central_format, error_format );
         sprintf( full_string, full_format, cen, up  );
      }
   } else {
      sprintf( full_format, "%s^{%s}_{%s}", central_format, error_format, error_format );
      sprintf( full_string, full_format , cen, up, lo );
   }
   return full_string;
}

string Scientific( const Parameter& x, unsigned precision )
{
   char central_format[64];
   char error_format  [64];
   char base_format   [64];
   char base_string   [256];
   char full_string   [256];
   int  exponent = 0 ;

   double cen = x.CentralValue()  ;
   double up  = x.AbsUpperError() ;
   double lo  = x.AbsLowerError() ;

   while( fabs(cen) > 10 ){
      exponent++;
      cen /= 10 ;
      up  /= 10 ;
      lo  /= 10 ;
   } while ( fabs(cen) < 1. ){
      exponent--;
      cen *= 10 ;
      up  *= 10 ;
      lo  *= 10 ;
   }

   sprintf( central_format, "%%.%dlf" , precision );
   sprintf( error_format  , "%%.%dlf" , precision+1 );

   // Printing base part to string
   if( up == lo ){
      if( up == 0 ){
         sprintf( base_format, "%s" , central_format );
         sprintf( base_string, base_format , cen );
      } else {
         sprintf( base_format, "%s\\pm%s" , central_format, error_format );
         sprintf( base_string, base_format, cen, up );
      }
   } else {
      sprintf( base_format, "%s^{%s}_{%s}", central_format, error_format, error_format );
      sprintf( base_string, base_format   , cen, up , lo );
   }

   if( exponent == 0 ){
      sprintf( full_string, "$%s$", base_string );
   } else {
      if( up == lo ){ // Special base for symmetric errors
         sprintf( full_string, "$(%s) \\times 10^{%d}$", base_string, exponent );
      } else {
         sprintf( full_string, "$%s \\times 10^{%d}$", base_string, exponent );
      }
   }
   return full_string;
}

string HiggsDataCard( const Parameter& x )
{
   char buffer[1024];
   if( x.CentralValue() == 0 && x.AbsUpperError() == 0 && x.AbsLowerError() == 0 ){
      return "--"; // special case for null parameter
   } else if( x.AbsUpperError() == x.AbsLowerError() ){
      sprintf( buffer, "%lg" , 1.+x.RelAvgError() );
   } else {
      sprintf( buffer, "%lg/%lg" , 1.+ x.RelUpperError() , 1.- x.RelLowerError() );
   }
   return buffer;
}
