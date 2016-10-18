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

#include "ManagerUtils/SampleMgr/interface/MultiFile.hpp"

#include <map>
#include <string>
#include <vector>
#include <memory>

namespace mgr
{

class SampleMgr: public virtual Named
{

public:
   SampleMgr( const std::string& );
   SampleMgr( const std::string&, const std::string& );
   SampleMgr( const std::string&, const ConfigReader& );
   virtual ~SampleMgr ();

   // Inititializing function
   static void InitStaticFromFile  ( const std::string& filename );
   static void InitStaticFromReader( const ConfigReader& reader  );
   void InitFromFile  ( const std::string&  filename );
   void InitFromReader( const ConfigReader& reader   );

   // Static Variables
   static double TotalLuminosity()            { return _luminocity ; }
   static const std::string& FilePrefix()     { return _file_prefix; }
   static void SetTotalLuminosity( const double       x ) { _luminocity       = x; }
   static void SetFilePrefix     ( const std::string& x ) { _file_prefix      = x; }

   // Access members
   virtual const Parameter&  CrossSection()           const { return _cross_section; }
   virtual const Parameter&  KFactor()                const { return _k_factor;      }
   virtual const Parameter&  SelectionEfficiency()    const { return _selection_eff; }
   virtual const std::vector<std::string>& FileList() const { return _filelist;     }
   virtual std::vector<std::string> GlobbedFileList() const ;

   // Manual setting function
   virtual void SetCrossSection       ( const Parameter& x ) { _cross_section = x; }
   virtual void SetKFactor            ( const Parameter& x ) { _k_factor      = x; }
   virtual void SetSelectionEfficiency( const Parameter& x ) { _selection_eff = x; }
   virtual std::vector<std::string>& FileList() { return _filelist; }

   // sample wide variable caching
   virtual bool HasCacheDouble( const std::string& ) const ;
   virtual void AddCacheDouble( const std::string&, const double );
   virtual double GetCacheDouble( const std::string& ) const ;
   virtual bool HasCacheString( const std::string& ) const ;
   virtual void AddCacheString( const std::string&, const std::string& );
   virtual std::string GetCacheString( const std::string& ) const ;

   // fwlite::interaction
   virtual MultiFileEvent& Event();
   virtual MultiFileEvent& Event() const ;
   virtual void  ForceNewEvent() const ; // Force refresh in case of new file

   // Extended Variables
   virtual bool      IsRealData()    const ;
   virtual size_t    EventsInFile()  const ;
   virtual Parameter ExpectedYield() const ;

private:
   static double       _luminocity;
   static std::string  _file_prefix;

   Parameter           _cross_section;
   Parameter           _k_factor;
   Parameter           _selection_eff;
   std::vector<std::string> _filelist;

   // Userdefined storage
   std::map<std::string, double>      _cachemap;
   std::map<std::string, std::string> _stringcache;

   // FWLite interaction
   mutable MultiFileEvent  _event;
};


}
#endif /* end of include guard */
