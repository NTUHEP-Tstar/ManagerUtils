/*******************************************************************************
 *
 *  Filename    : HistMgr.cc
 *  Description : Implementation for HistMgr.cc
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/RootMgr/interface/HistMgr.hpp"

#include <cstdlib>
#include <iostream>
using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructor/Destructor
//------------------------------------------------------------------------------
HistMgr::HistMgr( const string& name ):
   Named(name)
{
}

HistMgr::~HistMgr()
{
}

//------------------------------------------------------------------------------
//   Getting Histograms
//------------------------------------------------------------------------------
TH1D* HistMgr::Hist( const string& name )
{
   if( _histmap.count(name) ){
      return _histmap.at(name).get();
   } else {
      return NULL;
   }
}

const TH1D* HistMgr::Hist( const string& name ) const
{
   if( _histmap.count(name) ){
      return _histmap.at(name).get();
   } else {
      return NULL;
   }
}

vector<string> HistMgr::AvailableHistList() const
{
   vector<string> ans;
   for( const auto& histpair : _histmap ){
      ans.push_back( histpair.first );
   }
   return ans;
}

//------------------------------------------------------------------------------
//   Histogram Adding functions
//------------------------------------------------------------------------------
void HistMgr::AddHist(
      const string&  label   ,
      const string&  x_label ,
      const string&  x_unit  ,
      const int      bin_size,
      const double   x_lower ,
      const double   x_upper
) {
   char y_title[1024];
   const double bin_width = (x_upper - x_lower) / bin_size ;
   if( fabs(bin_width - 1 ) < 0.005 ){
      if( x_unit != ""){
         sprintf(
            y_title, "Yield [1/(%s)]",
            x_unit.c_str()
         );
      } else {
         sprintf( y_title , "Yield");
      }

   } else {
      if( x_unit != "" ){
         sprintf(
            y_title, "Yield [1/%.2lf(%s)]",
            (x_upper - x_lower)/bin_size,
            x_unit.c_str()
         );
      } else{
         sprintf(
            y_title, "Yield [1/%.2lf]",
            (x_upper - x_lower)/bin_size
         );
      }
   }

   string x_title = x_label;
   if( x_unit != "" ){
      x_title += " [" + x_unit + "]" ;
   }
   const string histname = Name() + label ;
   const string histtitle = ";" + x_title + ";" + y_title ;
   TH1D* hist = new TH1D( histname.c_str(), histtitle.c_str(), bin_size, x_lower, x_upper );
   hist->SetStats(0);

   _histmap[label] = std::unique_ptr<TH1D>(hist) ;
}


//------------------------------------------------------------------------------
//   Setting Memebers
//------------------------------------------------------------------------------
void HistMgr::Scale( const double x )
{
   for( auto& histpair: _histmap ){
      auto& hist = histpair.second;
      for( int i = 0 ; i < hist->GetSize() ; ++i ){
         double bincontent = hist->GetBinContent(i);
         double binerror   = hist->GetBinError(i);
         bincontent *= x ;
         binerror   *= x ;
         hist->SetBinContent(i,bincontent);
         hist->SetBinError(i,binerror);
      }
   }
}

void HistMgr::SetColor( const Color_t x )
{
   SetLineColor( x );
   SetFillColor( x );
}

void HistMgr::SetLineColor( const Color_t x )
{
   for( auto& histpair : _histmap ){
      histpair.second->SetLineColor( x );
   }
}

void HistMgr::SetFillColor( const Color_t x )
{
   for( auto& histpair : _histmap ){
      histpair.second->SetFillColor( x );
   }
}

void HistMgr::SetFillStyle( const Style_t x )
{
   for( auto& histpair : _histmap ){
      histpair.second->SetFillStyle( x );
   }
}
