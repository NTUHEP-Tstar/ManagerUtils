/*******************************************************************************
*
*  Filename    : Hist2DMgr.cc
*  Description : Implementation for 2D Histrogram manager
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/RootMgr/interface/Hist2DMgr.hpp"

using namespace std;
using namespace mgr;

/*******************************************************************************
*   Constructor and destructor
*******************************************************************************/
Hist2DMgr::Hist2DMgr( const string& name ) :
  Named( name ),
  _histmgr( name )
{

}

Hist2DMgr::~Hist2DMgr()
{}

/*******************************************************************************
*  Histogram access functions
*******************************************************************************/
TH2D*
Hist2DMgr::Hist2D( const string& name )
{
  return _histmgr.GetObj( name );
}

/******************************************************************************/

const TH2D*
Hist2DMgr::Hist2D( const string& name ) const
{
  return _histmgr.GetObj( name );
}

/******************************************************************************/

vector<string>
Hist2DMgr::AvailableHist2DList() const
{
  return _histmgr.ObjNameList();
}


/*******************************************************************************
*   TH2D declaration functions
*******************************************************************************/
void
Hist2DMgr::AddHist2D(
  const std::string& histname,
  const std::string& xtitle,
  const std::string& ytitle,
  const unsigned     xbin,
  const double       xmin,
  const double       xmax,
  const unsigned     ybin,
  const double       ymin,
  const double       ymax
  )
{
  const string histtitle = ";"+xtitle + ";" + ytitle;
  TH2D* newhist          = new TH2D(
    histname.c_str(),
    histtitle.c_str(),
    xbin, xmin, xmax,
    ybin, ymin, ymax
    );
  newhist->SetStats( 0 );
  _histmgr.AddObj( newhist );
}
