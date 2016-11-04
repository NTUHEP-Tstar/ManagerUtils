/*******************************************************************************
*
*  Filename    : SampleMgrLoader.hpp
*  Description : Functions for  (un)loading sample wide double variables to
*                SampleMgr from text file
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  ====
*
* Expected file to be in the format of
*  <Original Event Count>
*  <Selected Event Count>
*  <Tag> <Tag double>
*  <Tag> <tag double>
*  ...
*
* In the attempt to write to a file with value already existing, it will over
* write the values that exists in the sample mgr, leaving all other values
* intact.
*
*******************************************************************************/
#ifndef MANAGERUTILS_SAMPLEMGR_SAMPLEMGRLOADER_HPP
#define MANAGERUTILS_SAMPLEMGR_SAMPLEMGRLOADER_HPP

#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include <string>

namespace mgr {

extern void SaveCacheToFile( const SampleMgr&, const std::string& filename );

extern void LoadCacheFromFile( SampleMgr&, const std::string& filename );


}; /* mgr */



#endif /* end of include guard: MANAGERUTILS_SAMPLEMGR_SAMPLEMGRLOADER_HPP */
