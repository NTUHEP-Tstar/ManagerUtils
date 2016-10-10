/*******************************************************************************
*
*  Filename    : DrawCMS.cc
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/PlotUtils/interface/Constants.hpp"
#include "TLatex.h"

namespace plt {

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

/******************************************************************************/

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

}
