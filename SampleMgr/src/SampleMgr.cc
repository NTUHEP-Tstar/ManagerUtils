/*******************************************************************************
 *
 *  Filename    : SampleMgr.cc
 *  Description : Implementation for sample Manager
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"

#include "DataFormats/FWLite/interface/Run.h"
#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

#include "TFile.h"
#include <iostream>
#include <string>

using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructor/destructor and Initializers
//------------------------------------------------------------------------------
double SampleMgr::_luminocity = 0 ;
string SampleMgr::_file_prefix = "./";
string SampleMgr::_before_cut_label = "";
string SampleMgr::_after_cut_label  = "";

SampleMgr::SampleMgr( const string& name ):
   Named( name ),
   _event_ptr(NULL)
{
}

SampleMgr::SampleMgr( const string& name, const string& file_name ):
   Named( name ),
   _event_ptr(NULL)
{
   InitFromFile( file_name );
}

SampleMgr::SampleMgr( const string& name, const ConfigReader& cfg ):
   Named(name),
   _event_ptr(NULL)
{
   InitFromReader(cfg);
}

void SampleMgr::InitStaticFromFile( const string& file_name )
{
   InitStaticFromReader( ConfigReader(file_name) );
}

void SampleMgr::InitStaticFromReader( const ConfigReader& cfg )
{
   SetTotalLuminosity( cfg.GetStaticDouble("Total Luminosity") );
   SetFilePrefix(      cfg.GetStaticString("File Prefix") );
   SetBeforeCutLabel(  cfg.GetStaticString("Before Cut Label") );
   SetAfterCutLabel(   cfg.GetStaticString("After Cut Label") );
}

void SampleMgr::InitFromFile( const string& file_name )
{
   InitFromReader( ConfigReader(file_name) );
}

void SampleMgr::InitFromReader( const ConfigReader& cfg )
{
   SetLatexName(    cfg.GetString(     Name(), "Latex Name"    ) );
   _cross_section = cfg.GetParameter(  Name(), "Cross Section" );
   _k_factor      = cfg.GetParameter(  Name(), "K Factor"      );
   _file_list     = cfg.GetStringList( Name(), "EDM Files"     );

   ForceNewEvent();
   _selection_eff = make_selecection_eff();
}


SampleMgr::~SampleMgr()
{
   if( _event_ptr != NULL ){ delete _event_ptr; }
}

//------------------------------------------------------------------------------
//   ChainEvent construction
//------------------------------------------------------------------------------
fwlite::ChainEvent& SampleMgr::Event()
{
   if( _event_ptr == NULL ) { ForceNewEvent(); }
   return *_event_ptr;
}

void SampleMgr::ForceNewEvent()
{
   if( _event_ptr != NULL )  { delete _event_ptr; }
   vector<string> full_file_list ;
   for( const auto& file_name : _file_list ){
      full_file_list.push_back( FilePrefix() + file_name );
   }
   _event_ptr = new fwlite::ChainEvent( full_file_list );
}

//------------------------------------------------------------------------------
//   Computation results
//------------------------------------------------------------------------------
bool SampleMgr::IsRealData() const
{
   if( _event_ptr ) { return _event_ptr->isRealData(); }
   return false;
}

size_t SampleMgr::EventsInFile() const
{
   if( _event_ptr ) { return _event_ptr->size(); }
   return 0;
}

Parameter SampleMgr::ExpectedYield() const
{
   if( IsRealData() ){
      return Parameter(_event_ptr->size() ,0,0);
   } else {
      return TotalLuminosity() * CrossSection() * SelectionEfficiency() * KFactor();
   }
}

Parameter SampleMgr::GetSampleWeight()
{
   return ExpectedYield() * (1/(double)count_selected_events()) ;
}

uint64_t SampleMgr::count_original_events() const
{
   return count_event( _before_cut_label );
}

uint64_t SampleMgr::count_selected_events() const
{
   return count_event( _after_cut_label );
}

Parameter SampleMgr::make_selecection_eff() const
{
   double before = count_original_events();
   double after  = count_selected_events();
   double eff = after/before;
   double err = sqrt(eff*(1-eff)/before);
   return Parameter( eff, err, err );
}

uint64_t SampleMgr::count_event( const string& name ) const
{
   fwlite::Handle<edm::MergeableCounter> positive_count;
   fwlite::Handle<edm::MergeableCounter> negative_count;
   uint64_t count = 0 ;

   for( const auto& file_name : _file_list ){
      const string file_path = _file_prefix + file_name;
      fwlite::Run run( TFile::Open(file_path.c_str()) );
      positive_count.getByLabel( run , name.c_str() , "positiveEvents" );
      negative_count.getByLabel( run , name.c_str() , "negativeEvents" );
      count += positive_count->value;
      count -= negative_count->value;
   }
   return count;
}
