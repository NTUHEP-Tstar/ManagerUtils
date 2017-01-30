/*******************************************************************************
*
*  Filename    : MuonVar.cc
*  Description : Special functions for getting muon extended variables
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "DataFormats/PatCandidates/interface/Muon.h"
#include <algorithm>

namespace mgr {
/*******************************************************************************
*   Muon PF Isolation
*   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
*******************************************************************************/
extern const double MUPFISO_TIGHT = 0.15;
extern const double MUPFISO_LOOSE = 0.25;

double
MuPfIso( const pat::Muon& mu )
{
  const double chghad = mu.pfIsolationR04().sumChargedHadronPt;
  const double neuhad = mu.pfIsolationR04().sumNeutralHadronEt;
  const double pho    = mu.pfIsolationR04().sumPhotonEt;
  const double pu     = mu.pfIsolationR04().sumPUPt;
  const double pt     = mu.pt();

  return ( chghad+std::max( 0.0, neuhad+pho-0.5*pu ) )/pt;
}


/*******************************************************************************
*   Muon Track Isolation
*   https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Trigger
*******************************************************************************/
extern const double MUTRACKISO_TIGHT = 0.05;
extern const double MUTRACKISO_LOOSE = 0.10;

double
MuTrackIso( const pat::Muon& mu )
{
  return mu.isolationR03().sumPt / mu.pt();
}

} /* mgr */
