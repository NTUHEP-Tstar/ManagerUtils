/*******************************************************************************
 *
 *  Filename    : HistMgr.cc
 *  Description : Implementation for HistMgr.cc
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/HistMgr/interface/HistMgr.hpp"

#include <cstdlib>

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
   for( auto& hist : _hist_list ){ delete hist; }
}

//------------------------------------------------------------------------------
//   Getting Histograms
//------------------------------------------------------------------------------
TH1D* HistMgr::Hist( const string& hist_name )
{
   for( auto& hist : _hist_list ){
      if( Name()+hist_name == hist->GetName() ){
         return hist;
      }
   }
   return NULL;
}

const TH1D* HistMgr::Hist( const string& hist_name ) const
{
   for( auto& hist : _hist_list ){
      if( Name()+hist_name == hist->GetName() ){
         return hist;
      }
   }
   return NULL;
}

vector<string> HistMgr::AvailableHistList() const
{
   vector<string> ans;
   for( const auto& hist : _hist_list ){
      string name = hist->GetName();
      name.erase( 0 , Name().length() );
      ans.push_back( name );
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

   sprintf(
      y_title, "Yield [1/%.2lf %s]",
      (x_upper - x_lower)/bin_size,
      x_unit.c_str()
   );

   string x_title = x_label;
   if( x_unit != "" ){
      x_title += " [" + x_unit + "]" ;
   }
   const string hist_name = Name() + label ;
   const string hist_title = label +";" + x_title + ";" + y_title ;
   TH1D* hist = new TH1D( hist_name.c_str(), hist_title.c_str(), bin_size, x_lower, x_upper );
   hist->SetStats(0);

   _hist_list.push_back( hist );
}


//------------------------------------------------------------------------------
//   Setting Memebers
//------------------------------------------------------------------------------
void HistMgr::Scale( const double x )
{
   for( auto hist: _hist_list ){
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
   for( auto hist : _hist_list ){
      hist->SetLineColor( x );
   }
}

void HistMgr::SetFillColor( const Color_t x )
{
   for( auto hist : _hist_list ){
      hist->SetFillColor( x );
   }
}

void HistMgr::SetFillStyle( const Style_t x )
{
   for( auto hist : _hist_list ){
      hist->SetFillStyle( x );
   }
}
