/*******************************************************************************
 *
 *  Filename    : MuonVar.cc
 *  Description : Special functions for getting muon extended variables
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "DataFormats/PatCandidates/interface/Muon.h"
#include <algorithm>

//------------------------------------------------------------------------------
//   Muon PF Isolation,
//   https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
//------------------------------------------------------------------------------

extern const double MUPFISO_TIGHT = 0.12;
extern const double MUPFISO_LOOSE = 0.20;

double MuPfIso( const pat::Muon& mu )
{
   const double chghad = mu.pfIsolationR04().sumChargedHadronPt;
   const double neuhad = mu.pfIsolationR04().sumNeutralHadronEt;
   const double pho    = mu.pfIsolationR04().sumPhotonEt;
   const double pu     = mu.pfIsolationR04().sumPUPt;
   const double pt     = mu.pt();

   return (chghad+std::max(0.0,neuhad+pho-0.5*pu))/pt;
}
