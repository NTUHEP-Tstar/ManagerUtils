/*******************************************************************************
*
*  Filename    : RooFitUtils.hpp
*  Description : Helper functions for RooFit pointer container to stl containers
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_ROOFITUTILS_HPP
#define MANAGERUTILS_ROOTMGR_ROOFITUTILS_HPP

#include <vector>

#include "RooArgSet.h"

namespace mgr {

/*******************************************************************************
*   Convertion from RooArglist
*******************************************************************************/
template<typename T>
std::vector<T*> FromRooArgSet( RooArgSet* );

} /* mgr */


#include "ManagerUtils/RootMgr/src/RooFitUtils.ipp"

#endif /* end of include guard: MANAGERUTILS_ROOTMGR_ROOFITUTILS_HPP */
