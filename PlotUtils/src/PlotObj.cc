/*******************************************************************************
*
*  Filename    : PlotObj.cc
*  Description : Plotting Object declaration
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/PlotUtils/interface/Constants.hpp"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPad.h"
#include "TPaveText.h"

namespace mgr
{

/*******************************************************************************
*   Pad settings functions
*******************************************************************************/
static const float TOP_BOTTOM_SEP = 0.3;

TCanvas*
NewCanvas()
{
  TCanvas* c = new TCanvas( "c", "c", DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT );
  c->SetTicks( 1, 1 );
  return c;
}

/******************************************************************************/

TPad*
NewTopPad()
{
  TPad* pad = new TPad( "toppad", "", 0, TOP_BOTTOM_SEP, 1., 1.0 );
  pad->SetTicks( 1, 1 );
  pad->SetBottomMargin( 0.05 );
  pad->SetLeftMargin( PLOT_X_MIN );
  pad->SetRightMargin( 1-PLOT_X_MAX );
  pad->SetTopMargin( ( 1-PLOT_Y_MAX )/( 1-TOP_BOTTOM_SEP ) );
  return pad;
}

/******************************************************************************/

TPad*
NewBottomPad()
{
  TPad* pad = new TPad( "botpad", "", 0, 0.00, 1, TOP_BOTTOM_SEP );
  pad->SetTicks( 1, 1 );
  pad->SetTopMargin( 0.025 );
  pad->SetLeftMargin( PLOT_X_MIN );
  pad->SetRightMargin( 1-PLOT_X_MAX );
  pad->SetBottomMargin( ( PLOT_Y_MIN )/( TOP_BOTTOM_SEP ) );
  return pad;
}

/******************************************************************************/

void
SetSinglePad( TVirtualPad* pad )
{
  pad->SetLeftMargin( PLOT_X_MIN );
  pad->SetRightMargin( 1 - PLOT_X_MAX );
  pad->SetBottomMargin( PLOT_Y_MIN );
  pad->SetTopMargin( 1 - PLOT_Y_MAX );
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
  ans->SetTextSize( TEXT_FONT_SIZE );
  ans->SetFillColorAlpha( 0, 0 );

  return ans;
}

/******************************************************************************/

TPaveText*
NewTextBox( const float x_min,
            const float y_min,
            const float x_max,
            const float y_max )
{
  TPaveText* ans = new TPaveText( x_min, y_min, x_max, y_max );

  ans->SetTextFont( FONT_TYPE );
  ans->SetTextSize( TEXT_FONT_SIZE );
  ans->SetFillColor( kWhite );

  return ans;
}









}
