/*******************************************************************************
*
*  Filename    : samplemgr_test.cc
*  Description : Unit testing range for SampleMgr classes
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include <iostream>

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

using namespace std;
using namespace mgr;

int
main( int argc, char* argv[] )
{
   cout << "=====[UNIT TESTING FROM SAMPLEMGR CLASS]=====" << endl;

   SampleMgr::InitStaticFromFile( "./sample_static.json" );
   SampleMgr::SetFilePrefix( "./" );

   cout << "=====[STATIC VARIABLE TEST]=====" << endl;
   cout << SampleMgr::TotalLuminosity() << endl;
   cout << SampleMgr::FilePrefix() << endl;

   cout << "=====[FIRST INSTANCE TEST]=====" << endl;
   SampleMgr mysample( "TTJets" );
   mysample.InitFromFile( "./SampleJson_1.json" );


   cout << mysample.LatexName() << endl;
   cout << mysample.RootName() << endl;
   cout << mysample.EventsInFile() << endl;
   cout << mysample.ExpectedYield() << endl;

   cout << "=====[EVENT LOOP TEST]=====" << endl;
   int i = 0;
   fwlite::Handle<std::vector<pat::Jet> > Jets;

   for( mysample.Event().toBegin(); !mysample.Event().atEnd(); ++mysample.Event(), ++i ){
      if( i > 10 ){break; }
      cout << "[Event] " << i << endl;
      Jets.getByLabel( mysample.Event().Base(), "skimmedPatJets" );

      for( const auto& jet : *Jets.product() ){
         cout << jet.pt() << " " << flush;
      }

      cout << endl;
   }

   return 0;
}
