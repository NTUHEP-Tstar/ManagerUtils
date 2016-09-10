/*******************************************************************************
 *
 *  Filename    : TriggerMatching.hpp
 *  Description : Functions for Trigger Object matching
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Attempts to match a reco::Candidate object to a trigger object in a
 *  list of trigger objects with a specified trigger. The triggerNames
 *  object required is extracted directly from the edm::Event and
 *  edm::TriggerResults class. By default, we will be using the recommended
 *  cone size of 0.1.
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PHYS_UTILS_HPP
#define MANAGERUTILS_PHYS_UTILS_HPP

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

#include <string>

#include "TLorentzVector.h"

//------------------------------------------------------------------------------
//   HasTriggerMatch:
//     Check if matching trigger object exists.
//------------------------------------------------------------------------------
extern bool HasTriggerMatch(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
);


//------------------------------------------------------------------------------
//   TriggerMatchP4
//      Attempt to return the four momentum of the trigger object. If the trigger
//      object doesn't exist. It will return a (0,0,0,0) four momentum.
//------------------------------------------------------------------------------
TLorentzVector TriggerMatchP4(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
);

//------------------------------------------------------------------------------
//   MatchTrgObj
//     Return a vector::const_iterator to the first tracker object matched with the
//     reco::Candidate object within a radius of midelta_r. returns the end()
//     iterator if match is not found.
//     It is not recommended to use this function directly, but to use the functions above.
//------------------------------------------------------------------------------
extern pat::TriggerObjectStandAloneCollection::const_iterator MatchTrgObj(
   const reco::Candidate& recoobj,
   const pat::TriggerObjectStandAloneCollection& trgobjlist,
   const std::string& req_trigger,
   const edm::TriggerNames& trgnames,
   const double mindelta_r = 0.1
);



#endif /* end of include guard: MANAGERUTILS_PHYS_UTILS_HPP */
