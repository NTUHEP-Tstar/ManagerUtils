/*******************************************************************************
 *
 *  Filename    : Common.cc
 *  Description : Parameters for setting up common plotting options
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "ManagerUtils/PlotUtils/interface/Common.hpp"
#include "ManagerUtils/PlotUtils/interface/Constants.hpp"

namespace plt
{

TPaveText* NewTextBox( const float x_min, const float y_min, const float x_max, const float y_max)
{
   TPaveText* ans = new TPaveText(x_min,y_min,x_max,y_max);

   ans->SetTextFont(FONT_TYPE);
   ans->SetTextSize(AXIS_TITLE_FONT_SIZE);
   ans->SetFillColor(kWhite);

   return ans;
}

TLegend* NewLegend( const float x_min, const float y_min, const float x_max, const float y_max )
{
   TLegend* ans = new TLegend( x_min, y_min, x_max, y_max );

   // Setting up default values
   ans->SetBorderSize(0);
   ans->SetTextFont(FONT_TYPE);
   ans->SetTextSize(AXIS_TITLE_FONT_SIZE);
   ans->SetFillColorAlpha(0,0);

   return ans;
}

void DrawCMSLabel( int tag )
{
   TLatex  tl;
   tl.SetNDC( kTRUE );
   tl.SetTextFont( FONT_TYPE );
   tl.SetTextSize( AXIS_TITLE_FONT_SIZE );

   tl.SetTextAlign( BOTTOM_LEFT );
   tl.DrawLatex( PLOT_X_MIN, PLOT_Y_MAX + 0.05 , "#bf{CMS}");
   if( tag == PRELIMINARY ){
      tl.DrawLatex( PLOT_X_MIN+0.06, PLOT_Y_MAX + 0.05 , "#it{Preliminary}");
   } else if ( tag == SIMULATION ){
      tl.DrawLatex( PLOT_X_MIN+0.06, PLOT_Y_MAX + 0.05 , "#it{Simulation}");
   }
}

void DrawLuminosity(double luminosity)
{
   TLatex tl;
   tl.SetNDC( kTRUE );
   tl.SetTextFont( FONT_TYPE );
   tl.SetTextSize( AXIS_TITLE_FONT_SIZE );

   char buffer[1024];
   sprintf( buffer, "%.2lffb^{-1} (%d TeV)" , luminosity/1000. , 13 );

   tl.SetTextAlign( BOTTOM_RIGHT );
   tl.DrawLatex( PLOT_X_MAX, PLOT_Y_MAX+0.05, buffer );
}


}
