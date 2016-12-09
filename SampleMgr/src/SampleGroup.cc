/********************************************************************************
 *
 *  Filename    : SampleGroup.cc
 *  Description : Implementation for sample grouping class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleGroup.hpp"

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"
#include "ManagerUtils/Maths/interface/Efficiency.hpp"

#include <exception>
#include <iostream>
using namespace std;
using namespace mgr;

/*******************************************************************************
*   Static varaibles
*******************************************************************************/
string SampleGroup::_cfgprefix = "./";


/*******************************************************************************
*   Constructor/Destructor and initializer functiosn
*******************************************************************************/
SampleGroup::SampleGroup( const string& name ) :
   Named( name )
{
}

/******************************************************************************/

SampleGroup::SampleGroup( const string& name, const string& file_name ) :
   Named( name )
{
   InitFromFile( file_name );
}

/******************************************************************************/

SampleGroup::SampleGroup( const string& name, const ConfigReader& cfg ) :
   Named( name )
{
   InitFromReader( cfg );
}

/******************************************************************************/

void
SampleGroup::InitFromFile( const string& file_name )
{
   InitFromReader( ConfigReader( file_name ) );
}

/******************************************************************************/

void
SampleGroup::InitFromReader( const ConfigReader& cfg )
{
   if( cfg.HasStaticTag( "Sample Config Prefix" ) ){
      SetSampleCfgPrefix( cfg.GetStaticString( "Sample Config Prefix" ) );
   }
   auto type = GetType( cfg );
   if( type == Undef ){
      const auto samplecfg = GetUndefConfig( cfg );
      SampleList().push_back( SampleMgr( Name(), samplecfg ) );
      SetLatexName( SampleList().back().LatexName() );
      SetRootName( SampleList().back().RootName() );

   } else if( type == Standard ){
      const string rootname  = cfg.GetString( Name(), "Root Name" );
      const string latexname = cfg.GetString( Name(), "Latex Name" );
      SetLatexName( latexname );
      SetRootName( rootname );

      const auto samplecfg = GetSampleListConfig( cfg );

      for( const auto& name : GetSampleList( cfg ) ){
         SampleList().push_back( SampleMgr( name, samplecfg ) );
      }

   } else if( type == FileList ){
      const string rootname  = cfg.GetString( Name(), "Root Name" );
      const string latexname = cfg.GetString( Name(), "Latex Name" );
      SetLatexName( latexname );
      SetRootName( rootname );

      for( const auto& config : GetConfigList( cfg ) ){
         for( const auto& tag : config.GetInstanceList() ){
            SampleList().push_back( SampleMgr( tag, config ) );
         }
      }
   } else if( type == Single ){
      const auto samplecfg = GetSingleConfig( cfg );
      SampleList().push_back( SampleMgr( Name(), samplecfg ) );
      SetLatexName( SampleList().back().LatexName() );
      SetRootName( SampleList().back().RootName() );
   } else {
      throw std::invalid_argument("Unrecognized JSON file format for mgr::SampleGroup instance " + Name() );
   }
}

/******************************************************************************/

SampleGroup::~SampleGroup()
{
}

/*******************************************************************************
*   Sample Group Config file format detection
*******************************************************************************/
mgr::SampleGroup::ConfigType
SampleGroup::GetType( const mgr::ConfigReader& cfg ) const
{
   if( !cfg.HasInstance( Name() ) ){
      if( !cfg.HasStaticTag( "Default Json" ) ){ return ERROR; }
      return Undef;
   } else if( cfg.HasTag( Name(), "Sample List" ) ){
      if( cfg.HasTag( Name(), "Subset Json" ) ){ return Standard; }
      if( cfg.HasStaticTag( "Default Json" ) ){ return Standard; }
      return ERROR;
   } else if( cfg.HasTag( Name(), "File List" ) ){
      return FileList;
   } else if( cfg.HasTag( Name(), "Single Sample" ) ){
      return Single;
   } else {
      return ERROR;
   }
}

/******************************************************************************/

mgr::ConfigReader
SampleGroup::GetUndefConfig( const mgr::ConfigReader& cfg ) const
{
   const string jsonfile = cfg.GetStaticString( "Default Json" );
   const string fullpath = SampleCfgPrefix() + jsonfile;
   return ConfigReader( fullpath );
}

/******************************************************************************/

mgr::ConfigReader
SampleGroup::GetSampleListConfig( const mgr::ConfigReader& cfg ) const
{
   if( cfg.HasTag( Name(), "Subset Json" ) ){
      const string jsonfile = cfg.GetString( Name(), "Subset Json" );
      const string fullpath = SampleCfgPrefix() + jsonfile;
      return ConfigReader( fullpath );
   } else {
      return GetUndefConfig( cfg );
   }
}

/******************************************************************************/

mgr::ConfigReader
SampleGroup::GetSingleConfig( const mgr::ConfigReader& cfg ) const
{
   const string jsonfile = cfg.GetString( Name(), "Single Sample" );
   const string fullpath = SampleCfgPrefix() + jsonfile;
   return ConfigReader( fullpath );
}

/******************************************************************************/

vector<mgr::ConfigReader>
SampleGroup::GetConfigList( const mgr::ConfigReader& cfg ) const
{
   vector<mgr::ConfigReader> ans;

   for( const auto& json : cfg.GetStringList( Name(), "File List" ) ){
      ans.emplace_back( SampleCfgPrefix() + json );
   }

   return ans;
}

/******************************************************************************/

vector<string>
SampleGroup::GetSampleList( const mgr::ConfigReader& cfg ) const
{
   return cfg.GetStringList( Name(), "Sample List" );
}


/*******************************************************************************
*   Sample Access functions
*******************************************************************************/
SampleMgr&
SampleGroup::Sample( const std::string& name )
{
   for( auto& sample : SampleList() ){
      if( sample.Name() == name ){
         return sample;
      }
   }

   throw std::out_of_range( "Name is not within range!!" );
}

/******************************************************************************/

const SampleMgr&
SampleGroup::Sample( const std::string& name ) const
{
   for( const auto& sample : SampleList() ){
      if( sample.Name() == name ){
         return sample;
      }
   }

   throw std::out_of_range( "Name is not within range!!" );
}

/*******************************************************************************
*   Extended variables
*******************************************************************************/
double
SampleGroup::ExpectedYield() const
{
   double ans = 0;

   for( const auto& sample : _samplelist ){
      ans += sample.ExpectedYield();
   }

   return ans;
}

/******************************************************************************/

Parameter
SampleGroup::TotalCrossSection() const
{
   Parameter ans( 0, 0, 0 );

   for( const auto& sample : SampleList() ){
      ans += sample.CrossSection();
   }

   return ans;
}

/******************************************************************************/

Parameter
SampleGroup::AvgSelectionEfficiency() const
{
   if( Sample().IsRealData() ){
      double pass = 0;
      double orig = 0;

      for( const auto& sample : SampleList() ){
         pass += sample.SelectedEventCount();
         orig += sample.OriginalEventCount();
      }

      return Efficiency( pass, orig );

   } else {
      Parameter ans( 0, 0, 0 );
      double totalxsec = 0.;

      for( const auto& sample : SampleList() ){
         ans += sample.CrossSection() * sample.KFactor() *
                sample.SelectionEfficiency();
         totalxsec += sample.CrossSection() * sample.KFactor();
      }

      ans /= totalxsec;
      return ans;
   }
}
