/*******************************************************************************
*
*  Filename    : SampleMgr.cc
*  Description : Implementation for sample Manager
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"

#include <iostream>
#include <string>

using namespace std;

namespace mgr {
/*******************************************************************************
*   Static Variable
*******************************************************************************/
double SampleMgr::_luminocity = 0;
string SampleMgr::_fileprefix = "./";


/*******************************************************************************
*   Constructor/Destructor and initializers
*******************************************************************************/
SampleMgr::SampleMgr( const string& name ) :
  Named( name )
{
}

/******************************************************************************/

SampleMgr::SampleMgr( const string& name, const string& file_name ) :
  Named( name )
{
  InitFromFile( file_name );
}

/******************************************************************************/

SampleMgr::SampleMgr( const string& name, const ConfigReader& cfg ) :
  Named( name )
{
  InitFromReader( cfg );
}

/******************************************************************************/

void
SampleMgr::InitStaticFromFile( const string& file_name )
{
  InitStaticFromReader( ConfigReader( file_name ) );
}

/******************************************************************************/

void
SampleMgr::InitStaticFromReader( const ConfigReader& cfg )
{
  if( cfg.HasStaticTag( "Total Luminosity" ) ){
    SetTotalLuminosity( cfg.GetStaticDouble( "Total Luminosity" ) );
  }

  if( cfg.HasStaticTag( "File Prefix" ) ){
    SetFilePrefix( cfg.GetStaticString( "File Prefix" ) );
  }
}

/******************************************************************************/

void
SampleMgr::InitFromFile( const string& file_name )
{
  InitFromReader( ConfigReader( file_name ) );
}

/******************************************************************************/

void
SampleMgr::InitFromReader( const ConfigReader& cfg )
{
  SetLatexName( cfg.GetString(  Name(), "Latex Name"    ) );
  SetRootName( cfg.GetString( Name(), "Root Name" ) );
  _filelist = cfg.GetStringList( Name(), "EDM Files"     );
  SetIsRealData( cfg.GetBool( Name(), "Is Data" ) );

  if( !IsRealData() ){
    SetCrossSection( cfg.GetParameter(  Name(), "Cross Section" ) );
    SetKFactor( cfg.GetDouble(  Name(), "K Factor"      ) );

    const Parameter pdfunc = cfg.HasTag( Name(), "PDF Uncertainty" ) ?
                             cfg.GetParameter( Name(), "PDF Uncertainty" ) :
                               Parameter( 1, 0, 0 );

    const Parameter scaleunc = cfg.HasTag( Name(), "QCD Uncertainty" ) ?
                               cfg.GetParameter( Name(), "QCD Uncertainty" ) :
                               Parameter( 1, 0, 0 );

    SetPDFUncertainty( pdfunc );
    SetQCDScaleUncertainty( scaleunc );
  } else {
    SetCrossSection( Parameter( 0, 0, 0 ) );
    SetKFactor( 0 );
    SetQCDScaleUncertainty( Parameter( 1, 0, 0 ) );
    SetPDFUncertainty( Parameter( 1, 0, 0 ) );
  }

}

/******************************************************************************/

SampleMgr::~SampleMgr()
{
}

/*******************************************************************************
*   Basic object access
*******************************************************************************/
bool
SampleMgr::IsRealData()          const { return _isdata; }

double
SampleMgr::OriginalEventCount()  const { return _originaleventcount; }

double
SampleMgr::SelectedEventCount()  const { return _selectedeventcount; }

double
SampleMgr::KFactor()             const { return _kfactor; }

Parameter
SampleMgr::CrossSection()        const { return _xsection; }

Parameter
SampleMgr::PDFUncertainty()      const { return _pdfunc; }

Parameter
SampleMgr::QCDScaleUncertainty() const { return _qcdunc; }

const vector<string>&
SampleMgr::FileList()            const { return _filelist; }

/*******************************************************************************
*   Manual setting functions
*******************************************************************************/
void
SampleMgr::SetIsRealData( const bool x ){ _isdata = x; }

void
SampleMgr::SetOriginalEventCount( const double x ){ _originaleventcount = x; }

void
SampleMgr::SetSelectedEventCount( const double x ){ _selectedeventcount = x; }

void
SampleMgr::SetKFactor( const double x ){ _kfactor = x; }

void
SampleMgr::SetCrossSection( const Parameter& x ){ _xsection = x;  }

void
SampleMgr::SetPDFUncertainty( const Parameter& x ) { _pdfunc = x ; }

void
SampleMgr::SetQCDScaleUncertainty( const Parameter& x ) { _qcdunc = x ; }

void
SampleMgr::SetFileList( const vector<string>& x ){ _filelist = x; }

/*******************************************************************************
*   Extended variable calulcations
*******************************************************************************/
double
SampleMgr::EffectiveLuminosity() const
{
  return OriginalEventCount() / CrossSection().CentralValue() / KFactor();
}

/******************************************************************************/

Parameter
SampleMgr::SelectionEfficiency() const
{
  return Efficiency::Minos( SelectedEventCount(), OriginalEventCount() );
}

/******************************************************************************/
double
SampleMgr::ExpectedYield() const
{
  if( IsRealData() ){
    return SelectedEventCount();
  } else {
    return TotalLuminosity()
           * CrossSection().CentralValue()
           * SelectionEfficiency().CentralValue()
           * KFactor();
  }
}

/******************************************************************************/

vector<string>
SampleMgr::GlobbedFileList() const
{
  vector<string> ans;

  for( const auto& filename : FileList() ){
    const auto globq = FilePrefix().back() == '/' ? FilePrefix() + filename :
                       FilePrefix() + "/" + filename;

    for( const auto& file : Glob( globq ) ){
      ans.push_back( file );
    }
  }

  return ans;
}


/*******************************************************************************
*   Sample Cache varaible
*******************************************************************************/
bool
SampleMgr::HasCacheDouble( const string& x ) const
{
  return _cachemap.count( x );
}

/******************************************************************************/

void
SampleMgr::AddCacheDouble( const string& key, const double x )
{
  _cachemap[key] = x;
}

/******************************************************************************/

double
SampleMgr::GetCacheDouble( const string& key ) const
{
  return _cachemap.at( key );
}

/******************************************************************************/

bool
SampleMgr::HasCacheString( const string& x ) const
{
  return _stringcache.count( x );
}

/******************************************************************************/

void
SampleMgr::AddCacheString( const string& key, const string& x )
{
  _stringcache[key] = x;
}

/******************************************************************************/

string
SampleMgr::GetCacheString( const string& key ) const
{
  return _stringcache.at( key );
}


/******************************************************************************/

const map<string, double>&
SampleMgr::DoubleCache() const
{
  return _cachemap;
}

const map<string, string>&
SampleMgr::StringCache() const
{
  return _stringcache;
}

}/* mgr */
