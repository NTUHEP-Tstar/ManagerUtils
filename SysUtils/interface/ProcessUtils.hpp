/*******************************************************************************
 *
 *  Filename    : ProcessUtils.hpp
 *  Description : Utility functions for process detection and handling
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_SYSUTILS_PROCESSUTILS
#define MANAGERUTILS_SYSUTILS_PROCESSUTILS

#include <string>

//------------------------------------------------------------------------------
//   ** GetCMDOutput( x )
//   Storing the stdout of a shell command to a string x. Notice that nothing
//   output of the string will be displayed on screen, so the user is resposible
//   so ensure that the input command could be completed.
//------------------------------------------------------------------------------
extern std::string GetCMDSTDOutput( const std::string& x );
extern std::string GetCMDERROutput( const std::string& x );
extern std::string GetCMDOutput( const std::string& );

//------------------------------------------------------------------------------
//   ** NumOfThreads
//   Display the number of threads available to the machine
//------------------------------------------------------------------------------
extern unsigned NumOfThreads();

//------------------------------------------------------------------------------
//   ** HasProcess( a , b )
//   Return the number of processes containing the string 'a', while excluding
//   processes containing the results 'b'. If b is left blank, no-exclusion
//   will be processed.
//------------------------------------------------------------------------------
extern int  HasProcess( const std::string& x, const std::string& exclude="" );

//------------------------------------------------------------------------------
//   ** WaitProcess(a,b)
//   Sleep until the results of HasProcess(a,b) returns 0. Will also display
//   system time while waiting.
//------------------------------------------------------------------------------
extern void WaitProcess(
   const std::string& process_tag,
   const std::string& exclude="",
   const unsigned     waitmills=100
);

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PROCESSUTILS */
