/*******************************************************************************
 *
 *  Filename    : TriggerMatching.cc
 *  Description : Implementation of trigger matching algorithms
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Main reference :
 *    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD2016#Trigger
*******************************************************************************/
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <string>

#include "TLorentzVector.h"

//------------------------------------------------------------------------------
//   Core function
//------------------------------------------------------------------------------
pat::TriggerObjectStandAloneCollection::const_iterator MatchTrgObj(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
)
{
   for( auto objiter = trgobjlist.begin() ; objiter != trgobjlist.end() ; ++objiter ){
      auto obj = * objiter ; // making duplicate
      obj.unpackPathNames( trgnames );
      for( const auto& path : obj.pathNames() ){
         if( path.find(req_trigger) == std::string::npos ){ continue; } // required pathname must exists
         if( !obj.hasPathName(path) )                     { continue; } // object must has said path
         if( reco::deltaR( recoobj, obj ) < mindelta_r ){
            return objiter;
         }
      }
   }
   return trgobjlist.end();
}

//------------------------------------------------------------------------------
//   Extended functions using results of core functions
//-----------------------------------------------------------------------------
bool HasTriggerMatch(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
)
{
   auto match = MatchTrgObj( recoobj, trgobjlist, req_trigger, trgnames, mindelta_r) ;
   return match != trgobjlist.end();
}

TLorentzVector TriggerMatchP4(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
){
   auto match = MatchTrgObj( recoobj, trgobjlist, req_trigger, trgnames, mindelta_r) ;
   if( match == trgobjlist.end() ){
      return TLorentzVector( match->px(), match->py(), match->pz(), match->energy() );
   } else {
      return TLorentzVector( 0,0,0,0);
   }
}
