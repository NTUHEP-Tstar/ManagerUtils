/*******************************************************************************
*
*  Filename    : SetAxis.hpp
*  Description : Template functions for styling Axis, using template functiosn
*                for ROOT, ROOFIT object compatibility.
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_SETAXIS_HPP
#define MANAGERUTILS_PLOTUTILS_SETAXIS_HPP

#include "TGaxis.h"

namespace plt{

template<class T>
void
SetAxis( T* plot )
{
   // Global settings from TGaxis
   TGaxis::SetMaxDigits(4);
   TGaxis::SetExponentOffset(-1000,-1000); // Hide from view, alter y axis title instead

   plot->GetXaxis()->SetLabelFont( FONT_TYPE );
   plot->GetXaxis()->SetTitleFont( FONT_TYPE );
   plot->GetYaxis()->SetLabelFont( FONT_TYPE );
   plot->GetYaxis()->SetTitleFont( FONT_TYPE );
   plot->GetXaxis()->SetLabelSize( AXIS_LABEL_FONT_SIZE );
   plot->GetXaxis()->SetTitleSize( AXIS_TITLE_FONT_SIZE );
   plot->GetYaxis()->SetLabelSize( AXIS_LABEL_FONT_SIZE );
   plot->GetYaxis()->SetTitleSize( AXIS_TITLE_FONT_SIZE );
   plot->GetYaxis()->SetTitleOffset( 1.2 );
}

template<class T>
void
SetTopPlotAxis( T* plot )
{
   SetAxis( plot );
   plot->GetXaxis()->SetLabelSize( 0 );
   plot->GetXaxis()->SetTitleSize( 0 );
   plot->GetYaxis()->SetTitleOffset( 1.2 );
}

template<class T>
void
SetBottomPlotAxis( T* plot )
{
   SetAxis( plot );
   plot->GetYaxis()->SetNdivisions( 503 );
   plot->GetXaxis()->SetTitleOffset( 3.5 );
   plot->GetYaxis()->SetTitleOffset( 1.2 );
}

};

#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_SETAXIS_HPP */
