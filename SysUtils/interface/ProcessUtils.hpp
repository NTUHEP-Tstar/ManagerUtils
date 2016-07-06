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
extern unsigned NumOfThreads();
extern std::string GetCMDOutput( const std::string& x );
extern int  HasProcess( const std::string& x, const std::string& exclude="" );
extern void WaitProcess( const std::string& process_tag , const std::string& exclude="" );

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PROCESSUTILS */
