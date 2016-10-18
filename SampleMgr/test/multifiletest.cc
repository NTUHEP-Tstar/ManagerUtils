/*******************************************************************************
*
*  Filename    : multifiletest.cc
*  Description : Unit testing file for Multifile objects
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/MultiFile.hpp"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include <vector>
#include <iostream>
#include <cstdio>

int
main( int argc, char const* argv[] )
{
   mgr::MultiFileEvent ev({
      "root://eoscms.cern.ch//store/user/yichen/tstar_store/massreco/MuonControl/TT_TuneCUETP8M1_13TeV-powheg-pythia8_1.root",
      "root://eoscms.cern.ch//store/user/yichen/tstar_store/massreco/MuonControl/TT_TuneCUETP8M1_13TeV-powheg-pythia8_2.root"
   });

   unsigned i = 1 ;
   fwlite::Handle<std::vector<pat::Jet>> jethandle;
   for( ev.toBegin() ; !ev.atEnd() ; ++ev , ++i){
      const auto& event = ev.Base();
      jethandle.getByLabel( event , "skimmedPatJets" );

      printf(
         "\r[%u/%u] [%u/%u] : %lu",
         ev.FileIdx(),
         ev.FileCount(),
         i,
         ev.size(),
         jethandle->size()
      );
      fflush(stdout);
   }

   unsigned j = 0 ;
   fwlite::Handle<std::vector<pat::Muon>> muonhandle ;
   for( ev.toBegin() ; !ev.atEnd() ; ++ev , ++j){
      const auto& event = ev.Base();
      muonhandle.getByLabel( event , "skimmedPatMuons" );

      printf(
         "\r[%u/%u] [%u/%u] : %lu",
         ev.FileIdx(),
         ev.FileCount(),
         j,
         ev.size(),
         muonhandle->size()
      );
      fflush(stdout);
   }

   return 0;
}
