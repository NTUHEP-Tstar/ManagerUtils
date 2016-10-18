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

/*******************************************************************************
*   * Basename
*   * Stripping path to basename
*******************************************************************************/
extern std::string Basename( const std::string& );

//------------------------------------------------------------------------------
//   ** CMSSWSrc
//   Returns the absolute patth of the CMSSW_X_Y_Z/src directory this program
//   is in.
//------------------------------------------------------------------------------
extern std::string  CMSSWSrc();


/*******************************************************************************
*   Globbing related functions:
*   - Glob: Master function that handle both remote and local globbing queries
*   - GlobToRegex: Translating glob notation to regex expression
*******************************************************************************/
extern std::vector<std::string> Glob( const std::string& );
extern std::vector<std::string> GlobLocal( const std::string& );
extern std::vector<std::string> GlobRemote( const std::string& );

extern std::string GlobToRegex( const std::string& );

/*******************************************************************************
*   Helper functions for remote
*******************************************************************************/
extern std::string GetServerURL( const std::string& );
extern std::string GetRemotePath( const std::string& );


/*******************************************************************************
*   ** RandomFileName
*   Generating a random filename of length n, with extension if desired, adding
*   the hidden flag will add the prefix '.', enabled by default
*******************************************************************************/
extern std::string RandomFileName( const unsigned n , const std::string& ext ="" , const bool hidden=true );



#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PATHUTILS */
