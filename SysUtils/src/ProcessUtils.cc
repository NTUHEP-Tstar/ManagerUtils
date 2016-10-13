/*******************************************************************************
*
*  Filename    : SystemUtils.cc
*  Description : System interaction utility functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"
#include "ManagerUtils/SysUtils/interface/TimeUtils.hpp"

#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>

using namespace std;

#define MAX_BUFFER 65536

unsigned
NumOfThreads()
{
   return std::thread::hardware_concurrency();
}

string
GetCMDOutput( const string& cmd )
{
   FILE* pipe = popen( cmd.c_str(), "r" );
   if( !pipe ){ return ""; }
   char buffer[MAX_BUFFER];
   std::string result = "";

   while( !feof( pipe ) ){
      if( fgets( buffer, MAX_BUFFER, pipe ) ){
         result += buffer;
      }
   }

   pclose( pipe );
   return result;
}

int
HasProcess( const string& x, const string& exclude )
{
   string cmd = "ps aux | grep ^${USER}";
   cmd += " | grep " + x;
   cmd += " | grep --invert-match grep ";
   if( exclude != "" ){
      cmd += "| grep --invert-match  " + exclude;
   }
   cmd += " | wc --lines";

   string ans = GetCMDOutput( cmd );
   return stoi( ans );
}

void
WaitProcess( const string& x, const string& exclude )
{
   while( 1 ){
      int proc_count     = HasProcess( x, exclude );
      string time_string = CurrentDateTime();
      printf( "\r[%s] Still %d instance(s) running...",
         time_string.c_str(),
         proc_count );
      fflush( stdout );
      if( proc_count == 0 ){ break; }
      system( "sleep 1" );
   }

   printf( "All Done!\n" );
   fflush( stdout );
}
