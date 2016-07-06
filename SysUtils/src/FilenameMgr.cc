/*******************************************************************************
 *
 *  Filename    : FilenameMgr.cc
 *  Description : One Line descrption of file contents
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/FilenameMgr.hpp"
#include <exception>
#include <cstdlib>
using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructor & Destructor
//------------------------------------------------------------------------------
FilenameMgr::FilenameMgr(const string& package, const string& subpackage):
   _package_name(package),
   _sub_package_name(subpackage)
{
}

FilenameMgr::~FilenameMgr()
{

}

//------------------------------------------------------------------------------
//   Static public functions
//------------------------------------------------------------------------------
string FilenameMgr::ConvertToAbsPath(const string& path)
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

string FilenameMgr::GetEnv( const string& arg )
{
   return getenv( arg.c_str() );
}


//------------------------------------------------------------------------------
//   Instance public functions
//------------------------------------------------------------------------------
string FilenameMgr::SubPackageDir() const
{
   return GetEnv("CMSSW_BASE") + "/src/" + _package_name + "/" + _sub_package_name + "/";
}

string FilenameMgr::ResultsDir() const
{
   return SubPackageDir() + "results/" ;
}
