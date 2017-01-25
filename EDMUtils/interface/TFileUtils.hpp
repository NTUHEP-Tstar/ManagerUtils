/*******************************************************************************
*
*  Filename    : TFileUtils.hpp
*  Description : Helper functions for interacting with TFiles for EDM Plugins
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_EDMUTILS_TFILEUTILS_HPP
#define MANAGERUTILS_EDMUTILS_TFILEUTILS_HPP

#include "TObject.h"
#include <string>

extern TObject* GetCloneFromFile( const std::string& filename, const std::string& obj );


#endif/* end of include guard: MANAGERUTILS_EDMUTILS_TFILEUTILS_HPP */
