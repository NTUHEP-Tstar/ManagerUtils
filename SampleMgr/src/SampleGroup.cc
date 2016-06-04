/*******************************************************************************
 *
 *  Filename    : SampleGroup.cc
 *  Description : Implementation for sample grouping class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleGroup.hpp"

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"

#include <iostream>
#include <exception>
using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructors
//------------------------------------------------------------------------------
SampleGroup::SampleGroup( const string& name ):
   Named( name )
{
}

SampleGroup::SampleGroup( const string& name, const string& file_name ):
   Named(name)
{
   ConfigReader cfg( file_name );
   SetLatexName( cfg.GetString( Name(), "Latex Name") );
   const string sample_file = cfg.GetStaticString( "Sample Config File" );
   try{
      const auto& sample_name_list  = cfg.GetStringList( Name(), "Sample List" );
      for( const auto& sample_name : sample_name_list ){
         _samplelist.push_back( new SampleMgr(sample_name, sample_file ));
      }
   } catch( exception& e ){
      _samplelist.push_back( new SampleMgr(Name(), sample_file) );
   }
}

SampleGroup::~SampleGroup()
{
   for( auto& sample : _samplelist ) { delete sample; }
}

unsigned SampleGroup::EventsInFile() const
{
   unsigned ans = 0;
   for( const auto& sample : _samplelist ){
      ans += sample->EventsInFile();
   }
   return ans;
}

Parameter SampleGroup::ExpectedYield() const
{
   Parameter ans(0,0,0);
   for( const auto& sample : _samplelist ){
      ans += sample->ExpectedYield();
   }
   return ans;
}
