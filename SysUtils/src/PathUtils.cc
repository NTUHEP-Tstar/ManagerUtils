/*******************************************************************************
*
*  Filename    : PathUtils.cc
*  Description : Implementations of functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <glob.h>
#include <libgen.h>
#include <sys/time.h>

using namespace std;

// ------------------------------------------------------------------------------
//   Path related functions
// ------------------------------------------------------------------------------
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

/******************************************************************************/

string
SubPackageResultsPath( const std::string& x, const std::string& y )
{
   return SubPackagePath( x, y ) + "results/";
}

/******************************************************************************/
vector<string>
Glob( const string& path )
{
   glob_t glob_result;
   glob( path.c_str(), GLOB_TILDE, NULL, &glob_result );
   vector<string> ret( glob_result.gl_pathv, glob_result.gl_pathv + glob_result.gl_pathc );
   globfree( &glob_result );
   return ret;
}

/******************************************************************************/

string
RandomFileName( const unsigned n, const string& ext, const bool hidden  )
{
   const static string alphanum = "0123456789"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz";

   string ans = "";
   struct timeval time;
   gettimeofday( &time, NULL );
   srand( time.tv_usec );// Initializing to microseconds to avoid name collision

   for( unsigned i = 0; i < n; ++i ){
      ans.push_back( alphanum[rand()%alphanum.length()] );
   }

   if( ext != "" ){
      ans += "." + ext;
   }

   if( hidden ){
      ans = "." + ans;
   }

   return ans;
}
