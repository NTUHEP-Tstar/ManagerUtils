/*******************************************************************************
 *
 *  Filename    : PackagePathMgr.cc
 *  Description : One Line descrption of file contents
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/PackagePathMgr.hpp"
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include <exception>
#include <cstdlib>
using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructor & Destructor
//------------------------------------------------------------------------------
PackagePathMgr::PackagePathMgr(
      const std::string& package     ,
      const std::string& sub_package ,
      const std::string& settings_dir,
      const std::string& results_dir ,
      const std::string& samples_dir
):
   _package_name(package)        ,
   _sub_package_name(sub_package),
   _settings_dir(settings_dir)   ,
   _results_dir(results_dir)     ,
   _samples_dir(samples_dir)

{
}

PackagePathMgr::~PackagePathMgr()
{

}


//------------------------------------------------------------------------------
//   Public functions
//------------------------------------------------------------------------------
string PackagePathMgr::PackageDir() const
{
   return GetEnv("CMSSW_BASE") + "/src/" + _package_name + "/";
}

string PackagePathMgr::SubPackageDir() const
{
   return PackageDir() + _sub_package_name + "/";
}

string PackagePathMgr::SettingsDir() const
{
   return SubPackageDir() + _settings_dir + "/";
}

string PackagePathMgr::ResultsDir() const
{
   return SubPackageDir() + _results_dir +"/" ;
}

string PackagePathMgr::SamplesDir() const
{
   return SubPackageDir() + _samples_dir + "/";
}
