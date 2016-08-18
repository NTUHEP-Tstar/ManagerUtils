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

class SampleMgr: public virtual Named
{

public:
   SampleMgr( const std::string& );
   SampleMgr( const std::string&, const std::string& );
   SampleMgr( const std::string&, const ConfigReader& );
   virtual ~SampleMgr ();
   SampleMgr( const SampleMgr& ) = delete ;
   SampleMgr& operator=(const SampleMgr&) = delete ;

   // Inititializing function
   static void InitStaticFromFile( const std::string& file );
   static void InitStaticFromReader( const ConfigReader& );
   void InitFromFile( const std::string& filename );
   void InitFromReader( const ConfigReader& );

   // Static Variables
   static double TotalLuminosity()        { return _luminocity ;  }
   static const std::string& FilePrefix() { return _file_prefix; }
   static const std::string& BeforeCutLabel() { return _before_cut_label; }
   static const std::string& AfterCutLabel()  { return _after_cut_label; }
   static void SetTotalLuminosity( const double x  ) { _luminocity = x; }
   static void SetFilePrefix( const std::string& x ) { _file_prefix = x; }
   static void SetBeforeCutLabel( const std::string& x ) { _before_cut_label = x; }
   static void SetAfterCutLabel( const std::string& x )  { _after_cut_label  = x; }

   // Access members
   virtual const Parameter&  CrossSection()           const { return _cross_section; }
   virtual const Parameter&  KFactor()                const { return _k_factor; }
   virtual const Parameter&  SelectionEfficiency()    const { return _selection_eff;}
   virtual const std::vector<std::string>& FileList() const { return _file_list; }

   // Manual setting function
   virtual void SetCrossSection       ( const Parameter& x ) { _cross_section = x; }
   virtual void SetKFactor            ( const Parameter& x ) { _k_factor      = x; }
   virtual void SetSelectionEfficiency( const Parameter& x ) { _selection_eff = x; }
   virtual std::vector<std::string>& FileList() { return _file_list; }

   // fwlite::interaction
   virtual fwlite::ChainEvent& Event();
   virtual fwlite::ChainEvent& Event() const ;
   virtual void      ForceNewEvent() const ; // Force refresh in case of new file

   // Extended Variables
   virtual bool      IsRealData()    const ;
   virtual size_t    EventsInFile()  const ;
   virtual Parameter ExpectedYield() const;
   virtual Parameter GetSampleWeight() ;
   virtual uint64_t  SelectedEventCount() const { return count_selected_events(); }
   virtual uint64_t  OriginalEventCount() const { return count_original_events(); }

private:
   static double       _luminocity;
   static std::string  _file_prefix;
   static std::string  _before_cut_label;
   static std::string  _after_cut_label;
   Parameter           _cross_section;
   Parameter           _k_factor;
   Parameter           _selection_eff;
   std::vector<std::string> _file_list;

   mutable fwlite::ChainEvent*  _event_ptr;

   virtual Parameter make_selecection_eff() const ;
   virtual uint64_t  count_original_events() const;
   virtual uint64_t  count_selected_events() const;
   virtual uint64_t  count_event( const std::string& ) const ;
};


}
#endif /* end of include guard: __SAMPLE_MGR_HH__ */
