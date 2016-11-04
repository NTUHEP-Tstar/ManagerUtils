/*******************************************************************************
*
*  Filename    : PlotObj.hpp
*  Description : Function for delcaring plotting objects
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_PLOTOBJ_HPP
#define MANAGERUTILS_PLOTUTILS_PLOTOBJ_HPP

#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TPaveText.h"

namespace plt {
/*******************************************************************************
*   * New Pad - default settings for new padding in top and botom pads
*******************************************************************************/
extern TCanvas* NewCanvas();
extern TPad*    NewTopPad();
extern TPad*    NewBottomPad();

/*******************************************************************************
*   * New Legend
*   Create new Tlegend instance with all the font/size settings done.
*******************************************************************************/
extern TLegend* NewLegend(
   const float xmin,
   const float ymin,
   const float xmax = PLOT_X_MAX,
   const float ymax = PLOT_Y_MAX );

/*******************************************************************************
*   * NewTextBox
*   Creating a new TextBox instance with all the font/sizing settings done.
*******************************************************************************/
extern TPaveText* NewTextBox(
   const float xmin,
   const float ymin,
   const float xmax,
   const float ymax
);


};


#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_PLOTOBJ_HPP */
