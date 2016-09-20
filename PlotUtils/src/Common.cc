/*******************************************************************************
*
*  Filename    : Common.cc
*  Description : Parameters for setting up common plotting options
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/PlotUtils/interface/Common.hpp"
#include "ManagerUtils/PlotUtils/interface/Constants.hpp"

#include <algorithm>
#include <float.h>
#include <vector>

namespace plt
{

/*******************************************************************************
*   Pad settings functiosn
*******************************************************************************/
extern const float TOP_BOTTOM_SEP = 0.3;

TPad*
NewTopPad()
{
   TPad* pad = new TPad( "toppad", "", 0, TOP_BOTTOM_SEP, 1., 1.0 );
   pad->SetBottomMargin( 0.050 );
   return pad;
}

TPad*
NewBottomPad()
{
   TPad* pad = new TPad( "botpad", "", 0, 0.10, 1, TOP_BOTTOM_SEP );
   pad->SetTopMargin( 0.025 );
   pad->SetBottomMargin( 0.010 );
   return pad;
}

/*******************************************************************************
*   Getting histogram graphically maximum point
*******************************************************************************/
double
GetYmax( const TH1* hist )
{
   double ans = 0;
   for( int i = 1 ; i <= hist->GetNcells() ; ++i ){
      const double bincont = hist->GetBinContent(i);
      const double binerr  = hist->GetBinError(i);
      ans = std::max( ans, bincont + binerr );
   }
   return ans;
}

double
GetYmax( const std::vector<TH1*>& histlist )
{
   double ans = 0 ;
   for( const auto& hist : histlist ){
      ans = std::max( ans , GetYmax(hist) );
   }
   return ans;
}

/*******************************************************************************
*   New Legend settings
*******************************************************************************/
TLegend*
NewLegend( const float x_min,
           const float y_min,
           const float x_max,
           const float y_max )
{
   TLegend* ans = new TLegend( x_min, y_min, x_max, y_max );

   // Setting up default values
   ans->SetBorderSize( 0 );
   ans->SetTextFont( FONT_TYPE );
   ans->SetTextSize( AXIS_TITLE_FONT_SIZE );
   ans->SetFillColorAlpha( 0, 0 );

   return ans;
}

TPaveText*
NewTextBox( const float x_min,
            const float y_min,
            const float x_max,
            const float y_max )
{
   TPaveText* ans = new TPaveText( x_min, y_min, x_max, y_max );

   ans->SetTextFont( FONT_TYPE );
   ans->SetTextSize( AXIS_TITLE_FONT_SIZE );
   ans->SetFillColor( kWhite );

   return ans;
}


/******************************************************************************/


void
DrawCMSLabel( int tag )
{
   TLatex tl;
   tl.SetNDC( kTRUE );
   tl.SetTextFont( FONT_TYPE );
   tl.SetTextSize( AXIS_TITLE_FONT_SIZE );

   tl.SetTextAlign( BOTTOM_LEFT );
   tl.DrawLatex( PLOT_X_MIN, PLOT_Y_MAX + 0.05, "#bf{CMS}" );
   if( tag == PRELIMINARY ){
      tl.DrawLatex( PLOT_X_MIN+0.06, PLOT_Y_MAX + 0.05, "#it{Preliminary}" );
   } else
   if( tag == SIMULATION ){
      tl.DrawLatex( PLOT_X_MIN+0.06, PLOT_Y_MAX + 0.05, "#it{Simulation}" );
   }
}

void
DrawLuminosity( double luminosity )
{
   TLatex tl;
   tl.SetNDC( kTRUE );
   tl.SetTextFont( FONT_TYPE );
   tl.SetTextSize( AXIS_TITLE_FONT_SIZE );

   char buffer[1024];
   sprintf( buffer, "%.1lffb^{-1} (%d TeV)", luminosity/1000., 13 );

   tl.SetTextAlign( BOTTOM_RIGHT );
   tl.DrawLatex( PLOT_X_MAX, PLOT_Y_MAX+0.05, buffer );
}


/*******************************************************************************
*   TGraph Max and min calculations
*******************************************************************************/
double GetYmax( const TGraph* x )
{
   double ans = - DBL_MAX;
   for( int i = 0 ; i < x->GetN() ; ++i ){
      const double bin = x->GetY()[i] + x->GetErrorYhigh(i);
      ans = std::max( ans, bin );
   }
   return ans;
}

double GetYmin( const TGraph* x )
{
   double ans = DBL_MAX ;
   for( int i = 0 ; i < x->GetN() ; ++i ){
      const double bin = x->GetY()[i] - x->GetErrorYlow(i);
      ans = std::min( ans, bin );
   }
   return ans;

}

double GetYmax( const std::vector<const TGraph*>& list )
{
   double ans = - DBL_MAX;
   for( const auto& graph : list ){
      ans = std::max( ans, GetYmax(graph) );
   }
   return ans;
}

double GetYmin( const std::vector<const TGraph*>& list )
{
   double ans = DBL_MAX;
   for( const auto& graph : list ){
      ans = std::min( ans, GetYmin(graph) );
   }
   return ans;
}

}
