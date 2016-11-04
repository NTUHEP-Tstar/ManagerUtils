/*******************************************************************************
 *
 *  Filename    : RooFitUtils.hh
 *  Description : Implementation of functions defined in RooFitUtils.hh
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/

#include "ManagerUtils/PlotUtils/interface/Common.hpp"
#include "RooPlot.h"
#include "TAxis.h"

void SetFrame( RooPlot* frame )
{
   // Must set
   gPad->SetLeftMargin( PLOT_X_MIN );
   gPad->SetRightMargin( 1 - PLOT_X_MAX );
   gPad->SetBottomMargin( PLOT_Y_MIN );
   gPad->SetTopMargin( 1 - PLOT_Y_MAX );

   // Common Axis settings
   plt::SetAxis( frame ); // see PlotObj.cc
   frame->GetXaxis()->SetTitleOffset( 1.2 );
   frame->SetTitle("");
}
