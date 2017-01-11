/*******************************************************************************
*
*  Filename    : Format.hpp
*  Description : Wrapper function for boost::format error mitigation during runtime
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#ifndef MANAGERUTILS_SYSUTILS_FORMAT_HPP
#define MANAGERUTILS_SYSUTILS_FORMAT_HPP

#include <boost/format.hpp>
#include <string>

namespace mgr{

boost::format format( const std::string& fmt );

}

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_FORMAT_HPP */
