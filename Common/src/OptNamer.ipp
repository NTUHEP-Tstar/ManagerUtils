/*******************************************************************************
*
*  Filename    : OptNamer.ipp
*  Description : Implementation of template functions for options access
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_COMMON_OPTNAMER_IPP
#define MANAGERUTILS_COMMON_OPTNAMER_IPP

#include "ManagerUtils/Common/interface/BoostUtils/PTreeUtils.hpp"

/******************************************************************************/

template<typename T>
T
mgr::OptNamer::GetInput( const std::string& opt ) const
{
  return _argmap[opt].as<T>();
}

/******************************************************************************/

template<typename T>
std::vector<T>
mgr::OptNamer::GetInputList( const std::string& opt ) const
{
  return _argmap[opt].as<std::vector<T> >();
}

/******************************************************************************/

template<typename T>
T
mgr::OptNamer::GetExt( const std::string& opt, const std::string& exttag ) const
{
  return ExtQuery<T>( opt, GetInput<std::string>(opt), exttag );
}

/******************************************************************************/

template<typename T>
T
mgr::OptNamer::ExtQuery(
  const std::string& option,
  const std::string& optioninput,
  const std::string& tag ) const
{
  return mgr::GetSingle<T>( Tree() ,option, optioninput, tag );
}

#endif/* end of include guard: MANAGERUTILS_COMMON_OPTNAMER_IPP */
