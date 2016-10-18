/*******************************************************************************
*
*  Filename    : SampleMgr.cc
*  Description : Implementation for sample Manager
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"

#include <iostream>
#include <string>

using namespace std;
using namespace mgr;

// ------------------------------------------------------------------------------
//   Constructor/destructor and Initializers
// ------------------------------------------------------------------------------
double SampleMgr::_luminocity  = 0;
string SampleMgr::_file_prefix = "./";

SampleMgr::SampleMgr( const string& name ) :
   Named( name )
{
}

SampleMgr::SampleMgr( const string& name, const string& file_name ) :
   Named( name )
{
   InitFromFile( file_name );
}

SampleMgr::SampleMgr( const string& name, const ConfigReader& cfg ) :
   Named( name )
{
   InitFromReader( cfg );
}

void
SampleMgr::InitStaticFromFile( const string& file_name )
{
   InitStaticFromReader( ConfigReader( file_name ) );
}

void
SampleMgr::InitStaticFromReader( const ConfigReader& cfg )
{
   if( cfg.HasStaticTag( "Total Luminosity" ) ){
      SetTotalLuminosity( cfg.GetStaticDouble( "Total Luminosity" ) );
   }

   if( cfg.HasStaticTag( "File Prefix" ) ){
      SetFilePrefix( cfg.GetStaticString( "File Prefix" ) );
   }
}

void
SampleMgr::InitFromFile( const string& file_name )
{
   InitFromReader( ConfigReader( file_name ) );
}

void
SampleMgr::InitFromReader( const ConfigReader& cfg )
{
   SetLatexName( cfg.GetString(  Name(), "Latex Name"    ) );
   SetRootName( cfg.GetString( Name(), "Root Name" ) );
   SetCrossSection( cfg.GetParameter(  Name(), "Cross Section" ) );
   SetKFactor( cfg.GetParameter(  Name(), "K Factor"      ) );
   _filelist = cfg.GetStringList( Name(), "EDM Files"     );

   ForceNewEvent();// Creating the event files

   // Try to read configuration file first, otherwise try and lod from file
   if( cfg.HasTag( Name(), "Selection Efficiency" ) ){
      _selection_eff = cfg.GetParameter( Name(), "Selection Efficiency" );
   }
}


SampleMgr::~SampleMgr()
{
}

// ------------------------------------------------------------------------------
//   Globbed File List
// ------------------------------------------------------------------------------
vector<string>
SampleMgr::GlobbedFileList() const
{
   vector<string> ans;

   for( const auto& filename : FileList() ){
      const auto globq =  FilePrefix().back() == '/' ?
            FilePrefix() + filename : FilePrefix() + "/" + filename;

      for( const auto& file : Glob( globq ) ){
         ans.push_back( file );
      }
   }

   return ans;
}

// ------------------------------------------------------------------------------
//   ChainEvent construction
// ------------------------------------------------------------------------------
mgr::MultiFileEvent&
SampleMgr::Event()
{
   return _event;
}

mgr::MultiFileEvent&
SampleMgr::Event() const
{
   return _event;
}

void
SampleMgr::ForceNewEvent() const
{
   _event.reset( GlobbedFileList() );
}

// ------------------------------------------------------------------------------
//   Computation results
// ------------------------------------------------------------------------------
bool
SampleMgr::IsRealData() const
{
   if( Event().size() ){
      return Event().Base().isRealData();
   } else {
      return false;
   }
}

size_t
SampleMgr::EventsInFile() const
{
   return Event().size();
}

Parameter
SampleMgr::ExpectedYield() const
{
   if( IsRealData() ){
      return Parameter( Event().size(), 0, 0 );
   } else {
      return TotalLuminosity() * CrossSection() * SelectionEfficiency() *
             KFactor();
   }
}

/*******************************************************************************
*   Sample Cache varaible
*******************************************************************************/
bool
SampleMgr::HasCacheDouble( const string& x ) const
{
   return _cachemap.count( x );
}

/******************************************************************************/

void
SampleMgr::AddCacheDouble( const string& key, const double x )
{
   _cachemap[key] = x ;
}

/******************************************************************************/

double SampleMgr::GetCacheDouble( const string& key ) const
{
   return _cachemap.at(key);
}

/******************************************************************************/

bool
SampleMgr::HasCacheString( const string& x ) const
{
   return _stringcache.count(x);
}

/******************************************************************************/

void
SampleMgr::AddCacheString( const string& key, const string& x )
{
   _stringcache[key] = x ;
}

/******************************************************************************/

string
SampleMgr::GetCacheString( const string& key ) const
{
   return _stringcache.at(key);
}
