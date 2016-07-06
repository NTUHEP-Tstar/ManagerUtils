/*******************************************************************************
 *
 *  Filename    : SampleGroup.hpp
 *  Description : Listing a group of samples for easier plotting commands
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP
#define MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP

#include "ManagerUtils/BaseClass/interface/Named.hpp"
#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"

#include <vector>
#include <string>

namespace mgr
{

class SampleGroup : public virtual Named {
public:
   SampleGroup( const std::string& ); // Init name only
   SampleGroup( const std::string&, const std::string& ); // Initing from file
   SampleGroup( const std::string&, const ConfigReader& );
   virtual ~SampleGroup();
   SampleGroup( const SampleGroup& ) = delete ;
   SampleGroup& operator=( const SampleGroup& ) = delete;

   // Static function
   static void SetSampleCfgPrefix( const std::string& x ) { _sample_cfg_prefix = x; }
   static const std::string& SampleCfgPrefix() { return _sample_cfg_prefix; }

   // Initializing from file;
   void InitFromFile( const std::string& );
   void InitFromReader( const ConfigReader& ); // Virtual so users could add more variables if wanted

   // Access single object
   SampleMgr*       Sample()       { return _samplelist.front(); }
   const SampleMgr* Sample() const { return _samplelist.front(); }

   // Access list
   std::vector<SampleMgr*>&       SampleList()      { return _samplelist; }
   const std::vector<SampleMgr*>& SampleList() const {return _samplelist; }

   // Summary objects
   unsigned  EventsInFile() const;
   Parameter ExpectedYield() const;
   Parameter TotalCrossSection() const;

private:
   std::vector<SampleMgr*>  _samplelist;
   static std::string       _sample_cfg_prefix;
};

}
#endif /* end of include guard: __SAMPLEGROUP_H__ */
