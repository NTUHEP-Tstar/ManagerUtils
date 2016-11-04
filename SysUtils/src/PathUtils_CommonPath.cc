/*******************************************************************************
*
*  Filename    : PathUtils.cc
*  Description : Implementations of functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include <string>
#include <boost/filesystem.hpp>
#include <unistd.h>
using namespace std;

/******************************************************************************/

string
GetEnv( const std::string& x )
{
   return getenv( x.c_str() );
}


/******************************************************************************/

string
ConvertToAbsPath( const std::string& path )
{
   string ans = path;
   if( ans.empty() ){
      return "/";
   }

   if( ans[0] != '/' ){
      ans = GetEnv( "PWD" ) + "/" + ans;
   }
   return ans;
}


/******************************************************************************/

string
Basename( const std::string& mypath )
{
   boost::filesystem::path pathobj( mypath );
   return pathobj.filename().string();
}

/******************************************************************************/

string
CMSSWSrc()
{
   return GetEnv( "CMSSW_BASE" ) + "/src/";
}

/******************************************************************************/

string
PackagePath( const std::string& x )
{
   return CMSSWSrc() + x + "/";
}

/******************************************************************************/

string
SubPackagePath( const std::string& x, const std::string& y )
{
   return PackagePath( x ) + y + "/";
}
