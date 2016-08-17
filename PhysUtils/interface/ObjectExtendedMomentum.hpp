/*******************************************************************************
 *
 *  Filename    : ObjectExtendedMomentum.hpp
 *  Description : Helper template functions inserting/obtaining extended vectors
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP
#define MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDMOMENTUM_HPP

#include "TLorentzVector.h"
#include <string>

template<class T>
void AddLorentzVector( T& obj, const TLorentzVector& vec , const std::string& name )
{
   obj.addUserFloat( name+"pt" , vec.Pt()     );
   obj.addUserFloat( name+"eta", vec.Eta()    );
   obj.addUserFloat( name+"phi", vec.Phi()    );
   obj.addUserFloat( name+"e"  , vec.Energy() );
}

template<class T>
TLorentzVector GetLorentzVector( const T& obj, const std::string& name )
{
   TLorentzVector ans;
   double pt  ;
   double eta ;
   double phi ;
   double e   ;
   if(  obj.hasUserFloat(name+"pt" ) && obj.hasUserFloat(name+"eta") && obj.hasUserFloat(name+"phi") && obj.hasUserFloat(name+"e") ){
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
