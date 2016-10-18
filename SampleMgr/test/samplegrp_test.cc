/*******************************************************************************
 *
 *  Filename    : samplegrp_test.cc
 *  Description : Unit testing for Sample group class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"
#include "ManagerUtils/SampleMgr/interface/SampleGroup.hpp"
#include <iostream>

using namespace std;
using namespace mgr;

void DumpInfo( const SampleGroup& );

int main(int argc, char* argv[])
{
   cout << "=====[UNIT TESTING FOR SAMPLEGROUP CLASS]=====" << endl;

   ConfigReader cfg( "./group.json" );

   cout << "=====[SUBSET GROUP TESTING]=====" << endl;

   SampleMgr::InitStaticFromFile("./sample_static.json");
   SampleMgr::SetFilePrefix("./");

   SampleGroup  subset( "SubSetInFile" );
   subset.InitFromReader( cfg );
   DumpInfo( subset );

   SampleGroup subset_default( "SubSetInFile_WithDefault" );
   subset_default.InitFromReader( cfg );
   DumpInfo( subset_default );

   cout << "=====[FILE BASED GROUP TESTING]=====" << endl;
   SampleGroup  whole_file( "AllGroupsInFiles", cfg );
   DumpInfo( whole_file );

   cout << "=====[SINGLE SAMPLE TESTING]=====" << endl;
   SampleGroup single_in_file( "TTJets2" );
   single_in_file.InitFromReader( cfg );
   DumpInfo( single_in_file );

   cout << "=====[SINGLE SAMPLE TESTING]=====" << endl;
   SampleGroup single_default( "TTJets" );
   single_default.InitFromReader( cfg );
   DumpInfo( single_default );

   return 0;
}


void DumpInfo( const SampleGroup& x )
{
   cout << x.Name() << " " << x.LatexName() << endl;
   for( const auto& sample : x.SampleList() ){
      cout << "   > "
           << sample.Name() << " " << sample.LatexName()
           << sample.EventsInFile() << endl;
   }
}
