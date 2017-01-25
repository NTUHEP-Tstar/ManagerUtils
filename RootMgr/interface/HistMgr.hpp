/*******************************************************************************
*
*  Filename    : HistMgr
*  Description : Class for Histogram management, uses Named class unque ID
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_HISTMGR_HPP
#define MANAGERUTILS_ROOTMGR_HISTMGR_HPP

#include "ManagerUtils/Common/interface/Named.hpp"
#include "ManagerUtils/RootMgr/interface/RootObjMgr.hpp"

#include "TH1D.h"
#include <string>

namespace mgr {

class HistMgr : public virtual Named
{
public:
  HistMgr( const std::string& );  // Must have unique name
  virtual
  ~HistMgr ();

  // Explicitly removing copy constructor
  HistMgr( const HistMgr& )            = delete;
  HistMgr& operator=( const HistMgr& ) = delete;

  TH1D*       Hist( const std::string& );
  const TH1D* Hist( const std::string& ) const;

  std::vector<std::string> AvailableHistList() const;
  void                     Scale( const double );
  void                     SetColor( const Color_t );
  void                     SetLineColor( const Color_t );
  void                     SetFillColor( const Color_t );
  void                     SetFillStyle( const Style_t );

  void LoadFromFile( const std::string& );
  void SaveToFile( const std::string& );

  // Static functions for helping with title creation
  static std::string MakeYTitle(
    const double       binwidth,
    const std::string& xunit,
    const unsigned     exponent );
  static std::string GetXUnit( const TH1D* );
  static unsigned    GetExponent( const double );

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
  RootObjMgr<TH1D> _histmgr;
};

};

#endif/* end of include guard: MANAGERUTILS_HISTMGR_HISTMGR_HPP */
