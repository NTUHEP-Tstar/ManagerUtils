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

//------------------------------------------------------------------------------
//   Inclusion of common header files to be used
//------------------------------------------------------------------------------
#include "ManagerUtils/PlotUtils/interface/Constants.hpp"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TColor.h"
#include "TLatex.h"
#include "TLine.h"
#include "TGraph.h"
#include "TPaveText.h"

//------------------------------------------------------------------------------
//   NOTE! Namespace plt!
//------------------------------------------------------------------------------

namespace plt
{

//------------------------------------------------------------------------------
//   * NewLegend
//   Create new Tlegend instance with all the font/size settings done.
//------------------------------------------------------------------------------
TLegend*   NewLegend ( const float, const float, const float = PLOT_X_MAX , const float= PLOT_Y_MAX);

//------------------------------------------------------------------------------
//   ** NewTextBox
//   Creating a new TextBox instance with all the font/sizing settings done.
//------------------------------------------------------------------------------
TPaveText* NewTextBox( const float, const float, const float, const float );

//------------------------------------------------------------------------------
//   ** DrawCMSLabel
//   Drawing the CMS Preliminary/Simulation label on top left of canvas
//------------------------------------------------------------------------------
void DrawCMSLabel( int tag = PRELIMINARY );

//------------------------------------------------------------------------------
//   ** DrawLuminosity
//   Drawing the energy scale and luminosity information on top right of canvas
//------------------------------------------------------------------------------
void DrawLuminosity( double luminosity );


//------------------------------------------------------------------------------
//   ** DisableXAxis
//   Remove X axis labels and title from a Plotting objects
//------------------------------------------------------------------------------
template<class T>
void DisableXAxis( T* plot )
{
   plot->GetXaxis()->SetLabelSize(0);
   plot->GetXaxis()->SetTitleSize(0);
}


//------------------------------------------------------------------------------
//   ** SetAxis
//   Setting the axis of a plotting object to the defualt settings found in
//   Common.hpp
//------------------------------------------------------------------------------
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
