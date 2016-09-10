/*******************************************************************************
 *
 *  Filename    : ObjectExtendedVars.cc
 *  Description : Extended variables for physical objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDVARS_HPP
#define MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDVARS_HPP

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

//------------------------------------------------------------------------------
//   Muon Particle flow isolation, ( with recommended working point values )
//   For definition, see the POG group :
//   https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
//------------------------------------------------------------------------------
extern const double MUPFISO_TIGHT;
extern const double MUPFISO_LOOSE;
extern double MuPfIso( const pat::Muon& );

//------------------------------------------------------------------------------
//   Muon track objects isolation, ( with recommended working point values )
//   For definition, see the POG group :
//   https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2
//------------------------------------------------------------------------------
extern const double MUTRACKISO_TIGHT;
extern const double MUTRACKISO_LOOSE;
extern double MuTrackIso( const pat::Muon& );

//------------------------------------------------------------------------------
//  Particle Flow MiniIsolation:
//    Code reference :
//    github.com/manuelfs/CfANtupler/blob/master/minicfa/interface/miniAdHocNTupler.h#L54
//------------------------------------------------------------------------------
extern double PFMiniIsolation(
   const edm::Handle<pat::PackedCandidateCollection>& pfcands,
   const reco::Candidate* ptcl,
   const double r_iso_min,
   const double r_iso_max,
   const double kt_scale,
   const bool charged_only
); // in src/PFMiniIsolation.cc


#endif /* end of include guard: MANAGERUTILS_PHYSUTILS_OBJECTEXTENDEDVARS_HPP */
