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
   plt::SetAxis( frame );
   frame->GetXaxis()->SetTitleOffset( 1.2 );
   frame->SetTitle("");
}
