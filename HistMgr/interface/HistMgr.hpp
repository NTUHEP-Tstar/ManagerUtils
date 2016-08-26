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

#include <map>
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

   TH1D* Hist( const std::string& );
   const TH1D* Hist( const std::string& ) const ;

   std::map<std::string, TH1D*>& HistMap()             { return _histmap ; }
   const std::map<std::string, TH1D*>& HistMap() const { return _histmap ; }

   std::vector<std::string> AvailableHistList() const;
   void Scale( const double );
   void SetColor( const Color_t );
   void SetLineColor( const Color_t );
   void SetFillColor( const Color_t );
   void SetFillStyle( const Style_t );

protected:
   void AddHist(
      const std::string& name,
      const std::string& x_label,
      const std::string& x_unit,
      const int          bin_size,
      const double       x_min,
      const double       x_max
   );

private:
   virtual void define_hist(){}  //Virtual function for overloading
   std::map<std::string, TH1D*>  _histmap;
};

}

#endif /* end of include guard: MANAGERUTILS_HISTMGR_HISTMGR_HPP */
