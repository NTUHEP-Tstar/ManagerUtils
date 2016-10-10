/********************************************************************************
 *
 *  Filename    : SampleGroup.cc
 *  Description : Implementation for sample grouping class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleGroup.hpp"

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"

#include <exception>
#include <iostream>
using namespace std;
using namespace mgr;

// ------------------------------------------------------------------------------
//   Setting static variables
// ------------------------------------------------------------------------------
string SampleGroup::_sample_cfg_prefix = "./";

// ------------------------------------------------------------------------------
//   Constructors/destructor and Initializer
// ------------------------------------------------------------------------------
SampleGroup::SampleGroup( const string& name ) :
   Named( name )
{
}

SampleGroup::SampleGroup( const string& name, const string& file_name ) :
   Named( name )
{
   InitFromFile( file_name );
}

SampleGroup::SampleGroup( const string& name, const ConfigReader& cfg ) :
   Named( name )
{
   InitFromReader( cfg );
}


void
SampleGroup::InitFromFile( const string& file_name )
{
   InitFromReader( ConfigReader( file_name ) );
}

void
SampleGroup::InitFromReader( const ConfigReader& cfg )
{
   if( cfg.HasStaticTag( "Sample Config Prefix" ) ){
      _sample_cfg_prefix = cfg.GetStaticString( "Sample Config Prefix" );
   }

   if( !cfg.HasInstance( Name() ) ){
      // Not found in config file, assuming it is single sample in default
      const string jsonfile = cfg.GetStaticString( "Default Json" );
      const string fullpath = SampleCfgPrefix() + jsonfile;
      ConfigReader sample_cfg( fullpath );

      SampleList().push_back( new SampleMgr( Name(), sample_cfg ) );
      SetLatexName( SampleList().back()->LatexName() );
      SetRootName( SampleList().back()->RootName() );
   } else if( cfg.HasTag( Name(), "Sample List" ) ){
      const string rootname  = cfg.GetString( Name(), "Root Name" );
      const string latexname = cfg.GetString( Name(), "Latex Name" );
      SetLatexName( latexname );
      SetRootName( rootname );

      const string jsonfile
         = cfg.HasTag( Name(), "Subset Json" ) ?
           cfg.GetString( Name(), "Subset Json" ) :
           cfg.GetStaticString( "Default Json" );
      const string fullpath = SampleCfgPrefix() + jsonfile;
      ConfigReader samplecfg( fullpath );

      for( const auto& name : cfg.GetStringList( Name(), "Sample List" ) ){
         SampleList().push_back( new SampleMgr( name, samplecfg ) );
      }
   } else if( cfg.HasTag( Name(), "File List" ) ){
      const string rootname  = cfg.GetString( Name(), "Root Name" );
      const string latexname = cfg.GetString( Name(), "Latex Name" );
      SetLatexName( latexname );
      SetRootName( rootname );

      for( const auto& json : cfg.GetStringList( Name(), "File List" ) ){
         ConfigReader samplecfg( SampleCfgPrefix() + json );

         for( const auto& sampletag : samplecfg.GetInstanceList() ){
            SampleList().push_back( new SampleMgr( sampletag, samplecfg ) );
         }
      }
   } else if( cfg.HasTag( Name(), "Single Sample" ) ){
      const string jsonfile = cfg.GetString( Name(), "Single Sample" );
      const string fullpath = SampleCfgPrefix() + jsonfile;
      ConfigReader samplecfg( fullpath );
      SampleList().push_back( new SampleMgr( Name(), samplecfg ) );
      SetLatexName( SampleList().back()->LatexName() );
      SetRootName( SampleList().back()->RootName() );
   }
}

SampleGroup::~SampleGroup()
{
   for( auto& sample : _samplelist ){
      delete sample;
   }
}

/*******************************************************************************
*   Sample Access functions
*******************************************************************************/
SampleMgr* SampleGroup::Sample( const std::string& name )
{
   for( auto& sample: SampleList() ){
      if( sample->Name() == name ){
         return sample;
      }
   }
   return NULL;
}

const SampleMgr* SampleGroup::Sample( const std::string& name ) const
{
   for( const auto& sample : SampleList() ){
      if( sample->Name() == name ){
         return sample;
      }
   }
   return NULL;
}

// ------------------------------------------------------------------------------
//   Summary Methods
// ------------------------------------------------------------------------------
unsigned
SampleGroup::EventsInFile() const
{
   unsigned ans = 0;

   for( const auto& sample : _samplelist ){
      ans += sample->EventsInFile();
   }

   return ans;
}

Parameter
SampleGroup::ExpectedYield() const
{
   Parameter ans( 0, 0, 0 );

   for( const auto& sample : _samplelist ){
      ans += sample->ExpectedYield();
   }

   return ans;
}

Parameter
SampleGroup::TotalCrossSection() const
{
   Parameter ans( 0, 0, 0 );

   for( const auto& sample : SampleList() ){
      ans += sample->CrossSection();
   }

   return ans;
}

Parameter
SampleGroup::AvgSelectionEfficiency() const
{
   if( Sample()->IsRealData() ){
      double pass = 0;
      double orig = 0;

      for( const auto& sample : SampleList() ){
         pass += sample->EventsInFile();
         orig += sample->EventsInFile() /
                 sample->SelectionEfficiency().CentralValue();
      }

      const double cen = pass / orig;
      const double err = sqrt( cen * ( 1-cen ) / ( orig -1 ) );
      return Parameter( cen, err, err );

   } else {
      Parameter ans( 0, 0, 0 );
      double total_cx = 0.;

      for( const auto& sample : SampleList() ){
         ans += sample->CrossSection() * sample->KFactor() *
                sample->SelectionEfficiency();
         total_cx += sample->CrossSection() * sample->KFactor();
      }

      ans /= total_cx;
      return ans;
   }
}
