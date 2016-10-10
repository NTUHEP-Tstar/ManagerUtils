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
   Named( name ),
   _event_ptr( NULL )
{
}

SampleMgr::SampleMgr( const string& name, const string& file_name ) :
   Named( name ),
   _event_ptr( NULL )
{
   InitFromFile( file_name );
}

SampleMgr::SampleMgr( const string& name, const ConfigReader& cfg ) :
   Named( name ),
   _event_ptr( NULL )
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
   _file_list = cfg.GetStringList( Name(), "EDM Files"     );

   ForceNewEvent();// Creating the event files

   // Try to read configuration file first, otherwise try and lod from file
   if( cfg.HasTag( Name(), "Selection Efficiency" ) ){
      _selection_eff = cfg.GetParameter( Name(), "Selection Efficiency" );
   }
}


SampleMgr::~SampleMgr()
{
   if( _event_ptr != NULL ){ delete _event_ptr; }
}

// ------------------------------------------------------------------------------
//   Globbed File List
// ------------------------------------------------------------------------------
vector<string>
SampleMgr::GlobbedFileList() const
{
   vector<string> full_file_list;

   for( const auto& file_name : FileList() ){
      for( const auto& file : Glob( FilePrefix() + file_name ) ){
         full_file_list.push_back( file );
      }
   }

   return full_file_list;
}

// ------------------------------------------------------------------------------
//   ChainEvent construction
// ------------------------------------------------------------------------------
fwlite::ChainEvent&
SampleMgr::Event()
{
   if( _event_ptr == NULL ){ ForceNewEvent(); }
   return *_event_ptr;
}

fwlite::ChainEvent&
SampleMgr::Event() const
{
   if( _event_ptr == NULL ){ ForceNewEvent(); }
   return *_event_ptr;
}

void
SampleMgr::ForceNewEvent() const
{
   if( _event_ptr != NULL ){ delete _event_ptr; }

   _event_ptr = new fwlite::ChainEvent( GlobbedFileList() );
}

// ------------------------------------------------------------------------------
//   Computation results
// ------------------------------------------------------------------------------
bool
SampleMgr::IsRealData() const
{
   if( Event().size() ){
      return Event().isRealData();
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
      return Parameter( _event_ptr->size(), 0, 0 );
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
