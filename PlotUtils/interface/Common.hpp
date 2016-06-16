/*******************************************************************************
 *
 *  Filename    : Common.hpp
 *  Description : Typical helper setups for plotting objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Making it easier to comply with standards in
 *   https://ghm.web.cern.ch/ghm/plots/
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_COMMON_HPP
#define MANAGERUTILS_PLOTUTILS_COMMON_HPP

#include "ManagerUtils/PlotUtils/interface/Constants.hpp"

// Section including all common plotting libraries
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TColor.h"
#include "TLatex.h"
#include "TLine.h"
#include "TGraph.h"

namespace plt
{

//------------------------------------------------------------------------------
//   Class specific functions : see src/Common.cc for implementation
//------------------------------------------------------------------------------
TLegend* NewLegend( const float, const float, const float = PLOT_X_MAX , const float= PLOT_Y_MAX);
void DrawCMSLabel( int tag = PRELIMINARY );
void DrawLuminosity( double luminosity );



//------------------------------------------------------------------------------
//   Template functions for general plotting
//------------------------------------------------------------------------------
template<class T>
void DisableXAxis( T* plot )
{
   plot->GetXaxis()->SetLabelSize(0);
   plot->GetXaxis()->SetTitleSize(0);
}


template<class T>
void SetAxis( T* plot )
{
   plot->GetXaxis()->SetLabelFont(FONT_TYPE);
   plot->GetXaxis()->SetTitleFont(FONT_TYPE);
   plot->GetYaxis()->SetLabelFont(FONT_TYPE);
   plot->GetYaxis()->SetTitleFont(FONT_TYPE);
   plot->GetXaxis()->SetLabelSize(AXIS_LABEL_FONT_SIZE);
   plot->GetXaxis()->SetTitleSize(AXIS_TITLE_FONT_SIZE);
   plot->GetYaxis()->SetLabelSize(AXIS_LABEL_FONT_SIZE);
   plot->GetYaxis()->SetTitleSize(AXIS_TITLE_FONT_SIZE);
   plot->GetYaxis()->SetTitleOffset(1.2);
}

}

#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_COMMON_HPP */
