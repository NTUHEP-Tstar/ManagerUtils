/*******************************************************************************
 *
 *  Filename    : HistMgr
 *  Description : Class for Histogram management, uses Named class unque ID
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_HISTMGR_HISTMGR_HPP
#define MANAGERUTILS_HISTMGR_HISTMGR_HPP

#include "ManagerUtils/BaseClass/interface/Named.hpp"

#include "TH1D.h"

#include <vector>
#include <string>


namespace mgr {

class HistMgr : public virtual Named
{
public:
   HistMgr( const std::string& ); // Most have unique name
   virtual ~HistMgr ();

   // Explicitly removing copy constructor
   HistMgr( const HistMgr& )  = delete;
   HistMgr& operator=( const HistMgr& ) = delete;


   virtual TH1D* Hist( const std::string& );
   virtual const TH1D* Hist( const std::string& ) const ;
   virtual std::vector<std::string> AvailableHistList() const;
   virtual void Scale( const double );
   virtual void SetColor( const Color_t );
   virtual void SetLineColor( const Color_t );
   virtual void SetFillColor( const Color_t );
   virtual void SetFillStyle( const Style_t );

protected:
   virtual void AddHist(
      const std::string& name,
      const std::string& x_label,
      const std::string& x_unit,
      const int          bin_size,
      const double       x_min,
      const double       x_max
   );

private:
   std::vector<TH1D*>  _hist_list;
};

}

#endif /* end of include guard: MANAGERUTILS_HISTMGR_HISTMGR_HPP */
