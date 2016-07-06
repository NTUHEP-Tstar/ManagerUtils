/*******************************************************************************
 *
 *  Filename    : FilenameMgr.hpp
 *  Description : Helper class for handling file names
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#ifndef MANAGERUTILS_SYSUTILS_FILENAMEMGR_HPP
#define MANAGERUTILS_SYSUTILS_FILENAMEMGR_HPP

#include <string>
#include <map>

namespace mgr
{

class FilenameMgr {
public:
   FilenameMgr(const std::string& package, const std::string& sub_package);
   virtual ~FilenameMgr ();

   // Static functions
   static std::string ConvertToAbsPath( const std::string& path );
   static std::string GetEnv( const std::string& arg );

   // Instance functions for getting file names
   std::string SubPackageDir() const;
   std::string ResultsDir() const;


private:
   const std::string _package_name;
   const std::string _sub_package_name;
};

}

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_FILENAMEMGR_HPP */
