/*******************************************************************************
*
*  Filename    : Hist2DMgr.hpp
*  Description : Manager for TH2D collections
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_HIST2DMGR_HPP
#define MANAGERUTILS_ROOTMGR_HIST2DMGR_HPP

#include "ManagerUtils/BaseClass/interface/Named.hpp"
#include "ManagerUtils/RootMgr/interface/RootObjMgr.hpp"

#include "TH2D.h"
#include <vector>
#include <string>

namespace mgr {

class Hist2DMgr : public virtual Named
{
public:
   Hist2DMgr( const std::string& );// Must have unique name
   virtual
   ~Hist2DMgr ();

   // Explicitly removing copy constructor
   Hist2DMgr( const Hist2DMgr& )            = delete;
   Hist2DMgr& operator=( const Hist2DMgr& ) = delete;

   TH2D*       Hist2D( const std::string& );
   const TH2D* Hist2D( const std::string& ) const;

   std::vector<std::string> AvailableHist2DList() const;

protected:
   void AddHist2D(
      const std::string& histname,
      const std::string& xtitle,
      const std::string& ytitle,
      const unsigned xbin,
      const double   xmin,
      const double   xmax,
      const unsigned ybin,
      const double   ymin,
      const double   ymax
   );

private:
   RootObjMgr<TH2D>  _histmgr;
};


};

#endif/* end of include guard: MANAGERUTILS_ROOTMGR_HIST2DMGR_HPP */
