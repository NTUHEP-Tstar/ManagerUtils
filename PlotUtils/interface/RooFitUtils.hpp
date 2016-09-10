/*******************************************************************************
 *
 *  Filename    : RooFitUtils.hpp
 *  Description : Utility functions for better RooFit interaction
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_ROOFITUTILS_HPP
#define MANAGERUTILS_PLOTUTILS_ROOFITUTILS_HPP

#include "TGraph.h"
#include "RooPlot.h"
#include "RooAbsPdf.h"
#include "RooAbsData.h"

//------------------------------------------------------------------------------
//   ** PlotOn
//   Wrapper class for a RooFit Object plotOn function. Returns the generated
//   TGraph instance to allow for advance styling.
//------------------------------------------------------------------------------
template <class T>
TGraph* PlotOn( RooPlot* frame , T* rooobj,
   const RooCmdArg& arg1= RooCmdArg::none(),
   const RooCmdArg& arg2= RooCmdArg::none(),
   const RooCmdArg& arg3= RooCmdArg::none(),
   const RooCmdArg& arg4= RooCmdArg::none(),
   const RooCmdArg& arg5= RooCmdArg::none() )
{
   rooobj->plotOn( frame, arg1, arg2, arg3, arg4, arg5 );
   return (TGraph*)frame->getObject( frame->numItems() -1 );
}

//------------------------------------------------------------------------------
//   ** SetFrame
//   Setting RooPlot to common setting with the common settings in Common.hpp
//   with additional RooPlot specializations.
//------------------------------------------------------------------------------
extern void SetFrame(RooPlot*); // Setting common frame options

#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_ROOFITUTILS_HPP */
