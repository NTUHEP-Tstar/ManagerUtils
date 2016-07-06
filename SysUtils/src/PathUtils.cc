/*******************************************************************************
 *
 *  Filename    : PathUtils.cc
 *  Description : Implementations of functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include <cstdlib>
#include <string>
#include <vector>
#include <glob.h>

using namespace std;

string GetEnv( const std::string& x )
{
   return getenv( x.c_str() );
}

string ConvertToAbsPath( const std::string& path )
{
   string ans = path ;
   if( ans.empty() ){
      return "/";
   }

   if( ans[0] != '/') {
      ans = GetEnv("PWD") + "/" + ans;
   }
   return ans;
}

string CMSSWSrc()
{
   return GetEnv("CMSSW_BASE") + "/src/";
}

vector<string> Glob( const string& path )
{
   glob_t glob_result;
   glob(path.c_str(),GLOB_TILDE,NULL,&glob_result);
   vector<string> ret( glob_result.gl_pathv , glob_result.gl_pathv + glob_result.gl_pathc );
   globfree(&glob_result);
   return ret;
}
