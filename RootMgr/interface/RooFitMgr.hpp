/*******************************************************************************
 *
 *  Filename    : RooFitMgr.hpp
 *  Description : Class for manager RooFit object across multiple class instances
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_ROOFITMGR_HPP
#define MANAGERUTILS_ROOTMGR_ROOFITMGR_HPP

#include "ManagerUtils/BaseClass/interface/Named.hpp"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace mgr{

class RooFitMgr : virtual public mgr::Named {
public:
   RooFitMgr( const std::string& name );
   virtual ~RooFitMgr ();

   RooFitMgr( const RooFitMgr& )                 = delete;
   const RooFitMgr& operator=( const RooFitMgr&) = delete;

   // Static methods only exists for RooRealVar
   static RooRealVar* StaticNewVar(
      const std::string& name,
      const std::string& title,
      const std::string& unit,
      const double min,
      const double max
   );
   static RooRealVar* StaticVar( const std::string& );
   static std::vector<std::string> StaticVarNameList() ;

   // RooRealVar Access member functions
   RooRealVar*  NewVar( const std::string&, const double, const double );
   RooRealVar*  NewVar( const std::string&, const double, const double, const double );
   RooRealVar*        Var( const std::string& );
   const RooRealVar*  Var( const std::string& ) const;
   std::vector<std::string> VarNameList() const;
   std::vector<RooRealVar*> VarContains( const std::string& ) const ;
   void SetConstant( const bool set=kTRUE);

   // DataSet access list
   RooDataSet*       DataSet( const std::string& ); // Should contain a default dataset
   const RooDataSet* DataSet( const std::string& ) const ;
   std::vector<std::string>  SetNameList() const;
   void  AddDataSet( RooDataSet* );
   void  RemoveDataSet( const std::string& );

   // PDF making functions
   void          AddPdf( RooAbsPdf* );
   RooAbsPdf*       Pdf( const std::string& );
   const RooAbsPdf* Pdf( const std::string& ) const ;
   std::vector<std::string> PdfNameList() const;

private:
   static std::map< std::string , std::unique_ptr<RooRealVar> >  _staticvarmap;

   std::map< std::string , std::unique_ptr<RooRealVar> > _varmap;
   std::map< std::string , std::unique_ptr<RooDataSet> > _setmap;
   std::map< std::string , std::unique_ptr<RooAbsPdf > > _pdfmap;

   // Helper functions
   std::string MakeStoreName( const std::string& ) const ;
   std::string MakeAliasName( const std::string& ) const ;
};

}


#endif /* end of include guard: MANAGERUTILS_ROOTMGR_ROOFITMGR_HPP */
