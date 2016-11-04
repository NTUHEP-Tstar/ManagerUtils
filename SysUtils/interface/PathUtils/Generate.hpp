/*******************************************************************************
*
*  Filename    : Generate.hpp
*  Description : Generating File names and paths
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Main implementation in src/PathUtils_Generate.cc
*******************************************************************************/
#ifndef MANAGERUTILS_SYSUTILS_PATHUTILS_GENERATE_HPP
#define MANAGERUTILS_SYSUTILS_PATHUTILS_GENERATE_HPP

#include <string>

/*******************************************************************************
*   Generating of random string
*******************************************************************************/
extern std::string RandomString(
   const unsigned n
);

/**
 * Generate a random file name of length n
 * @param  n      [description]
 * @param  ext    [description]
 * @param  hidden [description]
 * @return        [description]
 */
extern std::string RandomFileName(
   const unsigned n ,
   const std::string& ext ="" ,
   const bool hidden=true
);


#endif /* end of include guard: MANAGERUTILS_SYSUTILS_PATHUTILS_GENERATE_HPP */
