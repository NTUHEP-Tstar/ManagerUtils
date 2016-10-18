/*******************************************************************************
*
*  Filename    : PathUtils.cc
*  Description : Implementations of functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <glob.h>
#include <libgen.h>
#include <sys/time.h>

#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"

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

/*******************************************************************************
*   Globbing related functions
*******************************************************************************/
vector<string>
Glob( const string& path )
{
   static const std::string remoteprefix="root://";
   if( std::mismatch(remoteprefix.begin(), remoteprefix.end(), path.begin()).first == remoteprefix.end() ){
      return GlobRemote( path );
   } else {
      return GlobLocal( path );
   }
}

/******************************************************************************/
vector<string>
GlobLocal( const string& path )
{
   glob_t glob_result;
   glob( path.c_str(), GLOB_TILDE, NULL, &glob_result );
   vector<string> ret( glob_result.gl_pathv, glob_result.gl_pathv + glob_result.gl_pathc );
   globfree( &glob_result );
   return ret;
}

/******************************************************************************/

vector<string>
GlobRemote( const string& fullpath )
{
   vector<string> ans;
   const string remoteurl  = GetServerURL( fullpath );
   const string remotepath = GetRemotePath( fullpath );

   // xrdfs does not take globbing arguments!
   // We must impliment it ourself directory by directory
   vector<string> tokens;
   boost::split( tokens, remotepath, boost::is_any_of( "/" ) );

   string pathquery;
   string globquery;

   vector<std::pair<std::string,unsigned>> querylist;
   querylist.emplace_back( "", 1 );
   for( unsigned i = 0 ; i < querylist.size() ; ++i  ){
      const string  querydir = querylist[i].first;
      const unsigned querydepth = querylist[i].second ;

      if( querydepth >= tokens.size() ){ continue; }
      const string cmd = str( boost::format("xrdfs %1% ls %2% ") % remoteurl % querydir );
      string rawoutput = GetCMDOutput( cmd ); // cannot be const!
      vector<string> outlist;
      boost::split( outlist, rawoutput, boost::is_any_of("\n") );

      std::regex globregex( GlobToRegex(querydir + '/' + tokens[querydepth]) );
      for( const auto& out : outlist ){
         if( std::regex_match(out, globregex) ){
            querylist.emplace_back( out, querydepth+1);
         }
      }
   }

   std::regex finalglob( GlobToRegex(remotepath) );
   for( const auto& querypair: querylist ){
      if( std::regex_match( querypair.first, finalglob )){
         const std::string fullfilepath = str( boost::format( "root://%1%/%2%")%remoteurl%querypair.first  );
         ans.push_back( fullfilepath );
      }
   }

   return ans;
}

/******************************************************************************/

std::string
GlobToRegex( const std::string& query )
{
   static const std::regex starmatch( "\\*" );
   static const std::string starrep( ".*" );

   static const std::regex qmmatch( "\\?" );
   static const std::string qmrep( "." );

   std::string ans = query;
   ans = std::regex_replace( ans, starmatch, starrep );
   ans = std::regex_replace( ans, qmmatch, qmrep );
   return ans;
}

/*******************************************************************************
*   Remote Helper functions
*******************************************************************************/
std::string
GetServerURL( const std::string& remotepath )
{
   std::regex urlregex( "root:\\/\\/([a-z.]+)\\/\\/.*" );
   std::smatch urlmatch;
   if( std::regex_match( remotepath, urlmatch, urlregex ) ){
      if( urlmatch.size() == 2 ){
         return urlmatch[1].str();
      } else {
         throw std::invalid_argument( "Input contains more than one url!" );
         return "";
      }
   } else {
      throw std::invalid_argument( "Input does not contain server url!" );
      return "";
   }
}
std::string
GetRemotePath( const std::string& remotepath )
{
   std::regex pathregex( "root:\\/\\/[a-z.]+\\/(\\/.+)" );
   std::smatch pathmatch;
   if( std::regex_match( remotepath, pathmatch, pathregex ) ){
      if( pathmatch.size() == 2 ){
         return pathmatch[1].str();
      } else {
         throw std::invalid_argument( "Input doesn't give a remote path!" );
         return "";
      }
   } else {
      throw std::invalid_argument( "Input doesn't give a remote path!" );
      return "";
   }
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
