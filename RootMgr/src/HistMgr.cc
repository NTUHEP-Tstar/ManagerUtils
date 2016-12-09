/*******************************************************************************
*
*  Filename    : HistMgr.cc
*  Description : Implementation for HistMgr.cc
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/RootMgr/interface/HistMgr.hpp"

#include "TFile.h"
#include "TGaxis.h"

#include <boost/format.hpp>
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;
using namespace mgr;

/*******************************************************************************
*   Constructor/Destructor
*******************************************************************************/
HistMgr::HistMgr( const string& name ) :
   Named( name ),
   _histmgr( name )
{
}

/******************************************************************************/

HistMgr::~HistMgr()
{
}

/*******************************************************************************
*   Histogram access functions
*******************************************************************************/
TH1D*
HistMgr::Hist( const string& name )
{
   return _histmgr.GetObj( name );
}

/******************************************************************************/

const TH1D*
HistMgr::Hist( const string& name ) const
{
   return _histmgr.GetObj( name );
}

/******************************************************************************/

vector<string>
HistMgr::AvailableHistList() const
{
   return _histmgr.ObjNameList();
}

/*******************************************************************************
*   Histogram addition functions
*******************************************************************************/
void
HistMgr::AddHist(
   const string& label,
   const string& x_label,
   const string& x_unit,
   const int     bin_size,
   const double  x_lower,
   const double  x_upper
   )
{
   // Making Y axis title without exponent
   const string y_title = MakeYTitle(
      ( x_upper - x_lower )/bin_size,
      x_unit,
      0// Disabling exponent for time being
      );

   // Make X axis title
   const string x_title = ( x_unit != "" ) ?
                          x_label+" ["+x_unit +"]" : x_label;
   const string histtitle = ";" + x_title + ";" + y_title;

   TH1D* hist = new TH1D( label.c_str(), histtitle.c_str(), bin_size, x_lower, x_upper );
   hist->SetStats( 0 );

   _histmgr.AddObj( hist );
}

/*******************************************************************************
*   Styling memeber functions
*******************************************************************************/
void
HistMgr::Scale( const double x )
{
   for( auto hist : _histmgr ){
      for( int i = 0; i < hist->GetSize(); ++i ){
         double bincontent = hist->GetBinContent( i );
         double binerror   = hist->GetBinError( i );
         bincontent *= x;
         binerror   *= x;
         hist->SetBinContent( i, bincontent );
         hist->SetBinError( i, binerror );
      }
   }
}

/******************************************************************************/

void
HistMgr::SetColor( const Color_t x )
{
   SetLineColor( x );
   SetFillColor( x );
}

/******************************************************************************/

void
HistMgr::SetLineColor( const Color_t x )
{
   for( auto hist : _histmgr ){
      hist->SetLineColor( x );
   }
}

/******************************************************************************/

void
HistMgr::SetFillColor( const Color_t x )
{
   for( auto hist : _histmgr ){
      hist->SetFillColor( x );
   }
}

/******************************************************************************/

void
HistMgr::SetFillStyle( const Style_t x )
{
   for( auto hist : _histmgr ){
      hist->SetFillStyle( x );
   }
}

/*******************************************************************************
*   File Loading and saving functions
*******************************************************************************/
void
HistMgr::LoadFromFile( const std::string& filename )
{
   TFile* histfile = TFile::Open( filename.c_str(), "READ" );

   for( auto hist : _histmgr ){
      const string histrootname = hist->GetName();
      TH1D* histptr             = (TH1D*)( histfile->Get( histrootname.c_str() )->Clone() );
      _histmgr.AddObj( histptr );
   }

   // Do not delete file for reading! Even if you have declared a new object!
   // delete histfile ;
}

/******************************************************************************/

void
HistMgr::SaveToFile( const std::string& filename )
{
   TFile* histfile = TFile::Open( filename.c_str(), "UPDATE" );

   for( const auto hist : _histmgr ){
      hist->Write();
   }

   delete histfile;
}

/*******************************************************************************
*   Axis title formatting functions
*******************************************************************************/
string
HistMgr::MakeYTitle(
   const double   binwidth,
   const string&  xunit,
   const unsigned exponent )
{
   static const double epsilon = 0.005;
   boost::format expstr( " #times 10^{%u}" );
   boost::format unitform( "/(%s)" );
   boost::format intunitform( "/%.0lf(%s)" );
   boost::format fltunitform( "/%.2lf(%s)" );
   boost::format intform( "/%.0lf" );
   boost::format fltform( "/%.2lf" );

   // Building answer using stringstream object
   stringstream ans;

   ans << "Yield";

   // Geting exponent part
   if( exponent ){
      ans << expstr % exponent;
   }

   // Checking xunit
   if( xunit != "" ){
      if( fabs( binwidth-1 ) < epsilon ){
         ans << unitform % xunit;
      } else if( fabs( binwidth-floor( binwidth ) ) < epsilon || fabs( binwidth-ceil( binwidth ) ) < epsilon ){
         ans << intunitform % binwidth % xunit;
      } else {
         ans << fltunitform % binwidth % xunit;
      }
   } else {
      if( fabs( binwidth-1 ) < epsilon ){
         // Do nothing
      } else if( fabs( binwidth-floor( binwidth ) ) < epsilon || fabs( binwidth-ceil( binwidth ) ) < epsilon ){
         ans << intform % binwidth;
      } else {
         ans << fltform % binwidth;
      }
   }
   return ans.str();
}

/******************************************************************************/

string
HistMgr::GetXUnit( const TH1D* x )
{
   static const std::regex re( ".*\\ \\[(.*)\\]" );

   const string title = x->GetXaxis()->GetTitle();
   std::smatch matchresults;

   std::regex_match( title, matchresults, re );
   if( matchresults.size() != 2 ){
      return "";
   } else {
      return matchresults[1];
   }
}

/******************************************************************************/

unsigned
HistMgr::GetExponent( const double x )
{
   unsigned ans      = 0;
   double poweroften = 10;

   while( poweroften < 10000000000 ){
      if( fabs( x ) > poweroften && fabs( x ) < poweroften * 1000 ){
         return ans;
      }
      ans        += 3;
      poweroften *= 1000;
   }

   return ans;
}
