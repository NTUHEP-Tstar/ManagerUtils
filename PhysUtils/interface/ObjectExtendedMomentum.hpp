/*******************************************************************************
*
*  Filename    : ObjectExtendedMomentum.hpp
*  Description : Helper template functions inserting/obtaining extended vectors
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Instead of using the userData() method of pat objects, we opt for a slightly
*  simpler method of storing the vectors pt, eta, phi and energy in userFloat()
*  formats and writting additiona functions for wrapping. These two functions
*  should be used in together:
*     AddLorentzVector( my_pat_object , my_new_vector , name )
*     GetLorentzVector( my_pat_object , name )
*  Notice that the get functions will return the original objects four momentum
*  if the vector with the corresponding name is not found.
*
*******************************************************************************/
#ifndef MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP
#define MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP

#include "TLorentzVector.h"
#include <string>

namespace mgr {
/*******************************************************************************
*   *AddLorentzVector
*   Store the envets under the pat::Object.
*******************************************************************************/
template<class T>
void
AddLorentzVector( T& obj, const TLorentzVector& vec, const std::string& name );

/*******************************************************************************
*   * HasLorentzVector
*   Check if all the variables for accessing a TLorentzVector exist under given
*   name
*******************************************************************************/
template<class T>
bool
HasLorentzVector( const T& obj, const std::string& name );

/*******************************************************************************
*   GetLorentzVector
*     Returning a TLorentzVector based on the information stored in the
*     pat::Object. If the information doesn't exists, return the
*     original four momentum
*******************************************************************************/
template<class T>
TLorentzVector
GetLorentzVector( const T& obj, const std::string& name );

} /* mgr */


// Including implementation file.
#include "ManagerUtils/PhysUtils/src/ObjectExtendedMomentum.ipp"

#endif/* end of include guard: MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP */
