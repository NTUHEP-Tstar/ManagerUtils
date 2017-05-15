/*******************************************************************************
*
*  Filename    : RooFitMgr.cc
*  Description : Implementation for RooFitMgr Class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/RootMgr/interface/RooFitMgr.hpp"
#include <boost/algorithm/string.hpp>

using namespace mgr;
using namespace std;

/*******************************************************************************
*   Static variable declaration
*******************************************************************************/
RootObjMgr<RooRealVar> RooFitMgr::_staticvarmgr( "" );// nameless container

/*******************************************************************************
*   Constructor and destructor
*******************************************************************************/
RooFitMgr::RooFitMgr( const string& name ) :
  Named( name ),
  _varmgr( name ),
  _setmgr( name ),
  _pdfmgr( name ),
  _funcmgr( name )
{
}

/******************************************************************************/

RooFitMgr::~RooFitMgr()
{
}

/*******************************************************************************
*   Static RooRealVar access functions
*******************************************************************************/
RooRealVar*
RooFitMgr::StaticNewVar(
  const string& varname,
  const string& title,
  const string& unit,
  const double  min,
  const double  max
  )
{
  if( StaticVar( varname ) ){
    RooRealVar* var = StaticVar( varname );
    var->setConstant( kFALSE );
    var->setMin( min );
    var->setMax( max );
    var->setUnit( unit.c_str() );
    var->SetTitle( title.c_str() );
    return var;
  } else {
    RooRealVar* newvar = new RooRealVar(
      varname.c_str(),
      title.c_str(),
      min,
      max,
      unit.c_str()
      );
    _staticvarmgr.AddObj( newvar );
    return _staticvarmgr.GetObj( varname );
  }
}

/******************************************************************************/

RooRealVar*
RooFitMgr::StaticVar( const string& name )
{
  return _staticvarmgr.GetObj( name );
}

/******************************************************************************/

vector<string>
RooFitMgr::StaticVarNameList()
{
  return _staticvarmgr.ObjNameList();
}



/*******************************************************************************
*   RooRealVar access functions
*******************************************************************************/
RooRealVar*
RooFitMgr::NewVar( const string& varname, const double min, const double max )
{
  if( Var( varname ) ){// if already exists variable
    RooRealVar* var = Var( varname );
    var->setConstant( kFALSE );
    var->setMin( min );
    var->setMax( max );
    return var;
  } else {
    RooRealVar* newvar = new RooRealVar( varname.c_str(), "", min, max );
    _varmgr.AddObj( newvar );
    return _varmgr.GetObj( varname );
  }
}

/******************************************************************************/

RooRealVar*
RooFitMgr::NewVar( const string& varname, const double cen, const double min, const double max )
{
  if( Var( varname ) ){// if already exists variable
    RooRealVar* var = Var( varname );
    var->setConstant( kFALSE );
    var->setMin( min );
    var->setMax( max );
    *var = cen;
    return var;
  } else {
    RooRealVar* newvar = new RooRealVar( varname.c_str(), "", cen, min, max );
    _varmgr.AddObj( newvar );
    return _varmgr.GetObj( varname );
  }
}

/******************************************************************************/

RooRealVar*
RooFitMgr::Var( const string& name )
{
  return _varmgr.GetObj( name );
}

/******************************************************************************/

const RooRealVar*
RooFitMgr::Var( const string& name ) const
{
  return _varmgr.GetObj( name );
}

/******************************************************************************/

vector<string>
RooFitMgr::VarNameList() const
{
  return _varmgr.ObjNameList();
}

/******************************************************************************/

vector<RooRealVar*>
RooFitMgr::VarContains( const string& substring )
{
  return _varmgr.GetObjContains( substring );
}

/******************************************************************************/

void
RooFitMgr::SetConstant( const bool state )
{
  for( const auto& name  : _varmgr.ObjNameList() ){
    _varmgr.GetObj( name )->setConstant( state );
  }
}

/******************************************************************************/

void RooFitMgr::RemoveVar( const std::string& name )
{
  _varmgr.RemoveObj(name);
}

/*******************************************************************************
*   RooAbsData access functions
*******************************************************************************/
RooAbsData*
RooFitMgr::DataSet( const std::string& name )
{
  return _setmgr.GetObj( name );
}

/******************************************************************************/

const RooAbsData*
RooFitMgr::DataSet( const std::string& name ) const
{
  return _setmgr.GetObj( name );
}

/******************************************************************************/

vector<std::string>
RooFitMgr::SetNameList() const
{
  return _setmgr.ObjNameList();
}

/******************************************************************************/

void
RooFitMgr::AddDataSet( RooAbsData* set )
{
  _setmgr.AddObj( set );
}

/******************************************************************************/

void
RooFitMgr::RemoveDataSet( const std::string& name )
{
  _setmgr.RemoveObj( name );
}

/*******************************************************************************
*   RooAbsPdf access functions
*******************************************************************************/
void
RooFitMgr::AddPdf( RooAbsPdf* pdf )
{
  _pdfmgr.AddObj( pdf );
}

/******************************************************************************/

RooAbsPdf*
RooFitMgr::Pdf( const std::string& name )
{
  return _pdfmgr.GetObj( name );
}

/******************************************************************************/

const RooAbsPdf*
RooFitMgr::Pdf( const std::string& name ) const
{
  return _pdfmgr.GetObj( name );
}

/******************************************************************************/

vector<std::string>
RooFitMgr::PdfNameList() const
{
  return _pdfmgr.ObjNameList();
}

/******************************************************************************/

void
RooFitMgr::RemovePdf( const std::string& name )
{
  _pdfmgr.RemoveObj(name);
}

/*******************************************************************************
*   RooAbsReal access functions
*******************************************************************************/
void
RooFitMgr::AddFunc( RooAbsReal* func )
{
  _funcmgr.AddObj( func );
}

RooAbsReal*
RooFitMgr::Func( const std::string& name )
{
  return _funcmgr.GetObj( name );
}

const RooAbsReal*
RooFitMgr::Func( const std::string& name ) const
{
  return _funcmgr.GetObj( name );
}

vector<std::string>
RooFitMgr::FuncNameList() const
{
  return _funcmgr.ObjNameList();
}
