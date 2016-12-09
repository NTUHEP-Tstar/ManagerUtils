/*******************************************************************************
*
*  Filename    : SampleMgr
*  Description : Manager class for a Single Prcoess objects
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Unit convention:
*     * CrossSection units in pb
*     * Lumimosity units in pb-1
*
*  Variables that independent of analysis and are expected to be defined in
*  any analysis must be present when initializing by json file. In the format:
*
*  "<Name>" : {
*     "Is Data": True/False,
*     "Cross Section" : [ <central>, <uperr>, <downerr> ],
*     "K Factor": value,
*     "EDM FileList" : [
*        "file1.root", "file2.root"
*     ]
*  }
*
*  Cross section and K factor could be omitted if IsData is set to false, and the
*  stored value will be set to zero.
*
*  User defined variable, and the analysis dependent variables OriginalEventCount()
*  and SelectedEventCount() will require user intervention to initialized.
*
*******************************************************************************/
#ifndef MANAGERUTILS_SAMPLEMGR_SAMPLEMGR_HPP
#define MANAGERUTILS_SAMPLEMGR_SAMPLEMGR_HPP

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"
#include "ManagerUtils/BaseClass/interface/Named.hpp"
#include "ManagerUtils/Maths/interface/Parameter.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mgr
{

class SampleMgr : public virtual Named
{

public:
   SampleMgr( const std::string& );
   SampleMgr( const std::string&, const std::string& );
   SampleMgr( const std::string&, const ConfigReader& );
   virtual
   ~SampleMgr ();

   // Inititializing function
   static void InitStaticFromFile( const std::string& filename );
   static void InitStaticFromReader( const ConfigReader& reader  );
   void        InitFromFile  ( const std::string& filename );
   void        InitFromReader( const ConfigReader& reader  );

   // Static Variables Access
   static double        TotalLuminosity(){ return _luminocity; }
   static const std::string& FilePrefix(){ return _fileprefix; }
   static void SetTotalLuminosity( const double x       ){ _luminocity = x; }
   static void SetFilePrefix     ( const std::string& x ){ _fileprefix = x; }

   // simple access funtions
   bool      IsRealData()               const;
   double    OriginalEventCount()       const;
   double    SelectedEventCount()       const;
   double    KFactor()                  const;
   Parameter CrossSection()             const;
   const std::vector<std::string>& FileList() const;

   // Manual setting function
   void SetIsRealData         ( const bool   );
   void SetOriginalEventCount ( const double );
   void SetSelectedEventCount ( const double );
   void SetKFactor            ( const double );
   void SetCrossSection       ( const Parameter& );
   void SetFileList           ( const std::vector<std::string>& );

   // Variable caching functions
   bool        HasCacheDouble( const std::string& ) const;
   void        AddCacheDouble( const std::string&, const double );
   double      GetCacheDouble( const std::string& ) const;
   bool        HasCacheString( const std::string& ) const;
   void        AddCacheString( const std::string&, const std::string& );
   std::string GetCacheString( const std::string& ) const;
   // Access Full Cache
   const std::map<std::string, double>& DoubleCache() const;
   const std::map<std::string, std::string>& StringCache() const;

   // Extended variable computation
   double    EffectiveLuminosity() const;
   Parameter SelectionEfficiency() const;
   double    ExpectedYield()       const;
   std::vector<std::string> GlobbedFileList() const;

private:
   // All static data-members are independent of analysis details
   static double _luminocity;
   static std::string _fileprefix;

   // Data-members independent of analysis details
   bool      _isdata;
   double    _kfactor;
   Parameter _xsection;
   std::vector<std::string> _filelist;

   // Data-members that are dependent on analysis details
   // but are expected to exists regardless of user
   double   _originaleventcount ;
   double   _selectedeventcount ;

   // User-defined storage
   std::map<std::string, double> _cachemap;
   std::map<std::string, std::string> _stringcache;
};

};
#endif/* end of include guard */
