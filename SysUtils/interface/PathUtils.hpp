/*******************************************************************************
 *
 *  Filename    : PathUtils.hpp
 *  Description : C++ Wrapper functions for path interaction
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Powered by boost/filesystem and POSIX
 *
*******************************************************************************/
#ifndef MANAGERUTILS_SYSUTILS_PATHUTILS
#define MANAGERUTILS_SYSUTILS_PATHUTILS

#include <vector>
#include <string>

//------------------------------------------------------------------------------
//  ** GetEnv
//  Getting a system environment variable, takes C++ string as input and output
//------------------------------------------------------------------------------
extern std::string  GetEnv( const std::string& );

//------------------------------------------------------------------------------
//   ** ConvertToAbsPath
//   Changes a relative path to absolute one
//------------------------------------------------------------------------------
extern std::string  ConvertToAbsPath( const std::string& );

//------------------------------------------------------------------------------
//   ** CMSSWSrc
//   Returns the absolute patth of the CMSSW_X_Y_Z/src directory this program
//   is in.
//------------------------------------------------------------------------------
extern std::string  CMSSWSrc();

//------------------------------------------------------------------------------
//   ** Glob
//   Return the globbing results by the input string query. Returns C++ strings
//------------------------------------------------------------------------------
extern std::vector<std::string> Glob( const std::string& );


#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PATHUTILS */
