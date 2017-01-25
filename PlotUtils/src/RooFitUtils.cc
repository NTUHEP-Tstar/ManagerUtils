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

namespace mgr {

void
SetFrame( RooPlot* frame )
{
  // Must set
  SetSinglePad( gPad );  // Using global pad settings

  // Common Axis settings
  SetAxis( frame );  // see PlotObj.cc
  frame->SetTitle( "" );
}

};
