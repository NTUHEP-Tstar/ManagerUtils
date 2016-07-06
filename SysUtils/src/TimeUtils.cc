/*******************************************************************************
 *
 *  Filename    : TimeUtils.cc
 *  Description : Implementation of time related system functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *   Additional comments
 *
*******************************************************************************/
#include <string>
#include <ctime>

using namespace std;

string CurrentDateTime()
{
   // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
   // for more information about date/time format
   time_t     now = time(0);
   struct tm  tstruct;
   char       buf[80];
   tstruct = *localtime(&now);
   strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
   return buf;
}
