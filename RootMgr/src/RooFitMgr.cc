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
//------------------------------------------------------------------------------
//   Constructor and Destructor
//------------------------------------------------------------------------------
map<string,unique_ptr<RooRealVar>> RooFitMgr::_staticvarmap;

RooFitMgr::RooFitMgr( const string& name ):
   Named(name)
{
}

RooFitMgr::~RooFitMgr()
{
}

//------------------------------------------------------------------------------
//   Static RooRealVar Access functions
//------------------------------------------------------------------------------
RooRealVar* RooFitMgr::StaticNewVar(
   const string& varname,
   const string& title,
   const string& unit,
   const double min,
   const double max
)
{
   if( StaticVar(varname) ){
      RooRealVar* var = StaticVar(varname);
      var->setConstant(kFALSE);
      var->setMin(min);
      var->setMax(max);
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
      _staticvarmap[varname] = unique_ptr<RooRealVar>( newvar );
      return _staticvarmap[varname].get();
   }
}

RooRealVar* RooFitMgr::StaticVar( const string& varname )
{
   if( _staticvarmap.count(varname) ){
      return _staticvarmap.at(varname).get();
   } else {
      return NULL;
   }
}

vector<string> RooFitMgr::StaticVarNameList()
{
   vector<string> ans;
   for( const auto& mypair : _staticvarmap ){
      ans.push_back( mypair.first );
   }
   return ans;
}

//------------------------------------------------------------------------------
//   RooRealVar Access functions
//------------------------------------------------------------------------------
RooRealVar* RooFitMgr::NewVar( const string& varname, const double min, const double max )
{
   if( Var(varname) ){ // if already exists variable
      RooRealVar* var = Var(varname) ;
      var->setConstant( kFALSE );
      var->setMin( min );
      var->setMax( max );
      return var;
   } else {
      const string newvarname = boost::algorithm::starts_with( varname , Name() )?
         varname : Name() + varname;
      RooRealVar* newvar = new RooRealVar( newvarname.c_str(), "", min, max );
      _varmap[varname] = unique_ptr<RooRealVar>( newvar ) ;
      return _varmap[varname].get();
   }
}

RooRealVar* RooFitMgr::NewVar( const string& varname, const double cen, const double min, const double max )
{
   if( Var(varname) ){ // if already exists variable
      RooRealVar* var = Var(varname) ;
      var->setConstant( kFALSE );
      var->setMin( min );
      var->setMax( max );
      *var = cen;
      return var;
   } else {
      const string newvarname = boost::algorithm::starts_with( varname , Name() )?
         varname : Name() + varname;
      RooRealVar* newvar = new RooRealVar( newvarname.c_str(), "", cen, min, max );
      _varmap[varname] = unique_ptr<RooRealVar>( newvar ) ;
      return _varmap[varname].get();
   }
}

RooRealVar* RooFitMgr::Var( const string& name )
{
   if( _varmap.count(name) ){
      return _varmap.at(name).get();
   } else {
      return NULL;
   }
}

const RooRealVar* RooFitMgr::Var( const string& name ) const
{
   if( _varmap.count(name) ){
      return _varmap.at(name).get();
   } else {
      return NULL;
   }
}

vector<string>  RooFitMgr::VarNameList() const
{
   vector<string> ans;
   for( const auto& mypair : _varmap ){
      ans.push_back( mypair.first );
   }
   return ans;
}

vector<RooRealVar*> RooFitMgr::VarContains( const string& substring ) const
{
   vector<RooRealVar*> ans;
   for( auto& mypair : _varmap ) {
      if( mypair.first.find(substring)!= string::npos ){
         ans.push_back(mypair.second.get());
      }
   }
   return ans;
}

void RooFitMgr::SetConstant( const bool state )
{
   for( const auto& mypair : _varmap ){
      mypair.second->setConstant( state );
   }
}

//------------------------------------------------------------------------------
//   RooDataSet access functions
//------------------------------------------------------------------------------
RooDataSet*   RooFitMgr::DataSet( const std::string& name )
{
   if( _setmap.count(name) ){
      return _setmap.at(name).get();
   } else {
      return NULL;
   }
}

const RooDataSet*  RooFitMgr::DataSet( const std::string& name ) const
{
   if( _setmap.count(name) ){
      return _setmap.at(name).get();
   } else {
      return NULL;
   }
}

vector<std::string>  RooFitMgr::SetNameList() const
{
   vector<string> ans;
   for( const auto& mypair : _setmap ){
      ans.push_back( mypair.first );
   }
   return ans;
}

void RooFitMgr::AddDataSet( RooDataSet* set )
{
   const string newsetname = MakeStoreName( set->GetName() );
   const string alias      = MakeAliasName( set->GetName() );

   _setmap.erase(alias); // deleting existing instance of dataset

   set->SetName( newsetname.c_str() );
   _setmap[alias] = unique_ptr<RooDataSet>( set );
}

void RooFitMgr::RemoveDataSet( const std::string& name )
{
   _setmap.erase( name );
}

//------------------------------------------------------------------------------
//   RooAbsPdf access functions
//------------------------------------------------------------------------------
void  RooFitMgr::AddPdf( RooAbsPdf* pdf )
{
   const string newpdfname = MakeStoreName( pdf->GetName() );
   const string alias      = MakeAliasName( pdf->GetName() );

   _pdfmap.erase(alias); // deleting previous instance of pdf

   pdf->SetName( newpdfname.c_str() );
   _pdfmap[alias] = unique_ptr<RooAbsPdf>( pdf );
}

RooAbsPdf* RooFitMgr::Pdf( const std::string& name )
{
   if( _pdfmap.count(name) ){
      return _pdfmap.at(name).get();
   } else {
      return NULL;
   }
}

const RooAbsPdf* RooFitMgr::Pdf( const std::string& name ) const
{
   if( _pdfmap.count(name) ){
      return _pdfmap.at(name).get();
   } else {
      return NULL;
   }
}

vector<std::string> RooFitMgr::PdfNameList() const
{
   vector<string> ans;
   for( const auto& mypair : _pdfmap ){
      ans.push_back( mypair.first );
   }
   return ans;
}


//------------------------------------------------------------------------------
//   Helper functions = checking object naming
//------------------------------------------------------------------------------
string RooFitMgr::MakeStoreName( const string& objname ) const
{
   if( boost::algorithm::starts_with( objname, Name() ) ){
      return objname ;
   } else {
      return Name() + objname;
   }
}

string RooFitMgr::MakeAliasName( const string& objname ) const
{
   if( boost::algorithm::starts_with( objname, Name() ) ){
      string newname = objname;
      newname.erase( 0, Name().length() );
      return newname ;
   } else {
      return objname;
   }
}
