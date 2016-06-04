/*******************************************************************************
 *
 *  Filename    : SampleMgr
 *  Description : Manager class for a Single Prcoess objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Note:
 *       * CrossSection units in pb
 *       * Lumimosity units in pb-1
 *
*******************************************************************************/
#ifndef MANAGERUTILS_SAMPLEMGR_SAMPLEMGR_HPP
#define MANAGERUTILS_SAMPLEMGR_SAMPLEMGR_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/BaseClass/interface/Named.hpp"
#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"

#include "DataFormats/FWLite/interface/ChainEvent.h"

#include <string>
#include <vector>

namespace mgr
{

class SampleMgr: public Named
{

public:
   SampleMgr( const std::string& ); // Declaring Name only
   SampleMgr( const std::string&, const std::string& file_name ); //Initialize from file
   virtual ~SampleMgr ();

   // Explicitly removing copy constructor
   SampleMgr( const SampleMgr& ) = delete ;
   SampleMgr& operator=(const SampleMgr&) = delete ;

   // Static Variables
   static double TotalLuminosity()        { return _luminocity ;  }
   static const std::string& FilePrefix() { return _file_prefix; }
   static const std::string& BeforeCutLabel() { return _before_cut_label; }
   static const std::string& AfterCutLabel()  { return _after_cut_label; }
   void SetTotalLuminosity( const double x  ) { _luminocity = x; }
   void SetFilePrefix( const std::string& x ) { _file_prefix = x; }
   void SetBeforeCutLabel( const std::string& x ) { _before_cut_label = x; }
   void SetAfterCutLabel( const std::string& x )  { _after_cut_label  = x; }

   // Access members
   const Parameter&  CrossSection()        const { return _cross_section; }
   const Parameter&  KFactor()             const { return _k_factor; }
   const Parameter&  SelectionEfficiency() const { return _selection_eff;}
   const std::vector<std::string>& FileList() const { return _file_list; }

   // Manual setting function
   void SetCrossSection       ( const Parameter& x ) { _cross_section = x; }
   void SetKFactor            ( const Parameter& x ) { _k_factor      = x; }
   void SetSelectionEfficiency( const Parameter& x ) { _selection_eff = x; }
   std::vector<std::string>& FileList() { return _file_list; }

   // fwlite::interaction
   fwlite::ChainEvent& Event();
   void      ForceNewEvent(); // Force refresh in case of new file

   // Extended Variables
   bool      IsRealData()    const ;
   size_t    EventsInFile()  const ;
   Parameter ExpectedYield() const;
   Parameter GetSampleWeight() ;

private:
   static double       _luminocity;
   static std::string  _file_prefix;
   static std::string  _before_cut_label;
   static std::string  _after_cut_label;
   Parameter           _cross_section;
   Parameter           _k_factor;
   Parameter           _selection_eff;
   std::vector<std::string> _file_list;

   fwlite::ChainEvent*  _event_ptr;

   Parameter make_selecection_eff() const ;
   uint64_t  count_original_events() const;
   uint64_t  count_selected_events() const;
   uint64_t  count_event( const std::string& ) const ;
};


}
#endif /* end of include guard: __SAMPLE_MGR_HH__ */
