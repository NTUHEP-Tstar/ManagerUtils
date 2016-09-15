/*******************************************************************************
*
*  Filename    : PluginAlias.hpp
*  Description : Using MACROS functions to help with EDM plugin functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_EDMUTILS_PLUGINALIAS_HPP
#define MANAGERUTILS_EDMUTILS_PLUGINALIAS_HPP


#define GETTOKEN( PARAMSET, TYPE, TAG ) \
   ( consumes< TYPE >( PARAMSET.getParameter<edm::InputTag>( TAG ) ) )

#define GETFILEPATH( PARAMSET, TAG )\
   ( PARAMSET.getParameter<edm::FileInPath>(TAG).fullPath() )

#endif /* end of include guard: MANAGERUTILS_EDMUTILS_PLUGINALIAS_HPP */
