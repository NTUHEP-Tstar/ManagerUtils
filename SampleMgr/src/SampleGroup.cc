/********************************************************************************
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
//   Constructors/destructor and Initializer
//------------------------------------------------------------------------------
SampleGroup::SampleGroup( const string& name ):
   Named( name )
{
}

SampleGroup::SampleGroup( const string& name, const string& file_name ):
   Named(name)
{
   InitFromFile( file_name );
}

SampleGroup::SampleGroup( const string& name, const ConfigReader& cfg ):
   Named(name)
{
   InitFromReader( cfg );
}


void SampleGroup::InitFromFile( const string& file_name )
{
   InitFromReader( ConfigReader(file_name) );
}

void SampleGroup::InitFromReader( const ConfigReader& cfg )
{
   if( !cfg.HasInstance( Name() ) ) { // Not found in config file, assuming it is single sample in default
      ConfigReader sample_cfg( cfg.GetStaticString("Default Json") );
      SampleList().push_back( new SampleMgr( Name() , sample_cfg ) );
      SetLatexName( SampleList().back()->LatexName() );
   } else if( cfg.HasTag( Name(), "Sample List" ) ){
      string latex_name = cfg.GetString( Name(), "Latex Name" );
      string sample_json_file = "";
      if( cfg.HasTag( Name() , "Subset Json") ){
         sample_json_file = cfg.GetString( Name() , "Subset Json" );
      } else {
         sample_json_file = cfg.GetStaticString( "Default Json" );
      }
      ConfigReader sample_cfg( sample_json_file );
      SetLatexName( latex_name );
      const vector<string> sample_name_list = cfg.GetStringList( Name(), "Sample List" );
      for( const auto& sample_name : sample_name_list ){
         SampleList().push_back( new SampleMgr( sample_name, sample_cfg ) );
      }
   } else if( cfg.HasTag( Name(), "File List") ){
      string latex_name = cfg.GetString( Name() , "Latex Name" );
      for( const auto& json_file : cfg.GetStringList( Name(), "File List") ){
         ConfigReader sample_cfg( json_file );
         for( const auto& sample_tag : sample_cfg.GetInstanceList() ){
            SampleList().push_back( new SampleMgr( sample_tag , sample_cfg ) );
         }
      }
   } else if( cfg.HasTag( Name(), "Single Sample") ){
      ConfigReader sample_cfg( cfg.GetString( Name(), "Single Sample") );
      SampleList().push_back( new SampleMgr( Name(), sample_cfg ) );
      SetLatexName( SampleList().back()->LatexName() );
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
