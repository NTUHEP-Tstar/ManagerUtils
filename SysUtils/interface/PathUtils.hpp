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
//   Path related functions
//------------------------------------------------------------------------------
extern std::string  GetEnv( const std::string& );
extern std::string  ConvertToAbsPath( const std::string& );
extern std::string  CMSSWSrc();
extern std::vector<std::string> Glob( const std::string& );



#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PATHUTILS */
