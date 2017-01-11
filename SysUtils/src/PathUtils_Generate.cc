/*******************************************************************************
*
*  Filename    : PathUtils_Generate.cc
*  Description : Implementation of functions for generating file names
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include <cstdlib>
#include <sys/time.h>
#include <string>

using namespace std;

/******************************************************************************/

string
RandomString( const unsigned n )
{
   static const string alphanum = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz";

   string ans = "";
   struct timeval time;
   gettimeofday( &time, NULL );
   srand( time.tv_usec );// Initializing to microseconds to avoid name collision

   for( unsigned i = 0; i < n; ++i ){
      ans.push_back( alphanum[rand()%alphanum.length()] );
   }

   return ans;
}

/******************************************************************************/

string
RandomFileName( const unsigned n, const string& ext, const bool hidden  )
{
   string ans = RandomString( n );

   if( ext != "" ){
      ans += "." + ext;
   }

   if( hidden ){
      ans = "." + ans;
   }

   return ans;
}
