/*******************************************************************************
 *
 *  Filename    : SampleGroup.hpp
 *  Description : Listing a group of samples for easier plotting commands
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP
#define MAMAGERUTILS_SAMPLEMGR_SAMPLEGROUP_HPP

#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include <vector>
#include <string>

namespace mgr
{

class SampleGroup : public Named {
public:
   SampleGroup( const std::string& ); // Init name only
   SampleGroup( const std::string&, const std::string& ); // Init from config file
   virtual ~SampleGroup();

   // Access single object
   SampleMgr*       Sample()       { return _samplelist.front(); }
   const SampleMgr* Sample() const { return _samplelist.front(); }

   // Access list
   std::vector<SampleMgr*>&       SampleList()      { return _samplelist; }
   const std::vector<SampleMgr*>& SampleList() const {return _samplelist; }

   unsigned  EventsInFile() const;
   Parameter ExpectedYield() const;

private:
   std::vector<SampleMgr*> _samplelist;
};

}
#endif /* end of include guard: __SAMPLEGROUP_H__ */
