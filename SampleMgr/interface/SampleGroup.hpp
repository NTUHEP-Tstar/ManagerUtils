/*******************************************************************************
*
*  Filename    : SampleGroup.hpp
*  Description : Listing a group of samples for easier plotting commands
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP
#define MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP

#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"
#include "ManagerUtils/BaseClass/interface/Named.hpp"

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"

#include <memory>
#include <string>
#include <vector>

namespace mgr
{

class SampleGroup : public virtual Named
{
public:
   SampleGroup( const std::string& );// Init name only
   SampleGroup( const std::string&, const std::string& );// Initing from file
   SampleGroup( const std::string&, const ConfigReader& );
   virtual
   ~SampleGroup();

   // Static function
   static void
   SetSampleCfgPrefix( const std::string& x ){ _cfgprefix = x; }
   static const std::string&
   SampleCfgPrefix(){ return _cfgprefix; }

   // Initializing from file;
   void InitFromFile( const std::string& );
   void InitFromReader( const ConfigReader& );

   // Sample Access functions
   // * Sample() : return first element in list
   // * SampleList() : return reference to vector objects
   SampleMgr&       Sample()       { return SampleList().front(); }
   const SampleMgr& Sample() const { return SampleList().front(); }
   std::vector<SampleMgr>&       SampleList()       { return _samplelist; }
   const std::vector<SampleMgr>& SampleList() const { return _samplelist; }

   // Searching functions
   SampleMgr&       Sample( const std::string& );
   const SampleMgr& Sample( const std::string& ) const;

   // Extended variables
   double    ExpectedYield() const;
   Parameter TotalCrossSection() const;
   Parameter AvgSelectionEfficiency() const;

protected:
   // Helper functions for configureation file reading
   enum ConfigType
   {
      Undef      = 0,
      Standard   = 1,
      FileList   = 2,
      Single     = 3,
      ERROR      = 10,
   };
   ConfigType                      GetType( const mgr::ConfigReader& ) const ;
   mgr::ConfigReader               GetUndefConfig( const mgr::ConfigReader& ) const ;
   mgr::ConfigReader               GetSampleListConfig( const mgr::ConfigReader& ) const ;
   mgr::ConfigReader               GetSingleConfig( const mgr::ConfigReader& ) const ;
   std::vector<mgr::ConfigReader>  GetConfigList( const mgr::ConfigReader& ) const ;
   std::vector<std::string>        GetSampleList( const mgr::ConfigReader& ) const ;

private:
   static std::string _cfgprefix;

   std::vector<SampleMgr> _samplelist;
};

};
#endif/* end of include guard */
