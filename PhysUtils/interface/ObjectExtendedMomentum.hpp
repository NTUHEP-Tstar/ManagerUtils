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

//------------------------------------------------------------------------------
// AddLorentzVector
//   Storing the events under the pat object, the true indicates that it will
//   attempt to override the variable if it already exists.
//------------------------------------------------------------------------------
template<class T>
void AddLorentzVector( T& obj, const TLorentzVector& vec , const std::string& name )
{
   obj.addUserFloat( name+"pt" , vec.Pt()     , true );
   obj.addUserFloat( name+"eta", vec.Eta()    , true );
   obj.addUserFloat( name+"phi", vec.Phi()    , true );
   obj.addUserFloat( name+"e"  , vec.Energy() , true );
}

//------------------------------------------------------------------------------
//  HasLorentzVector
//    Checking if all the variables for accessing a TLorentzVector exists
//------------------------------------------------------------------------------
template<class T>
bool HasLorentzVector( const T& obj, const std::string& name )
{
   if(  obj.hasUserFloat(name+"pt" )
        && obj.hasUserFloat(name+"eta")
        && obj.hasUserFloat(name+"phi")
        && obj.hasUserFloat(name+"e") ){
      return true;
   } else {
      return false;
   }

}

//------------------------------------------------------------------------------
//  GetLorentzVector
//    Constructing a TLorentzVector object based on the information stored in
//    the pat object, if the information doesn't exist, return the original
//    four momentum.
//------------------------------------------------------------------------------
template<class T>
TLorentzVector GetLorentzVector( const T& obj, const std::string& name )
{
   TLorentzVector ans;
   double pt  ;
   double eta ;
   double phi ;
   double e   ;
   if( HasLorentzVector( obj, name ) ){
      pt  = obj.userFloat( name+"pt" );
      eta = obj.userFloat( name+"eta");
      phi = obj.userFloat( name+"phi");
      e   = obj.userFloat( name+"e");
   } else {
      pt  = obj.pt();
      eta = obj.eta();
      phi = obj.phi();
      e   = obj.energy();
   }
   ans.SetPtEtaPhiE( pt, eta, phi, e );
   return ans;
}


#endif /* end of include guard: MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP */
