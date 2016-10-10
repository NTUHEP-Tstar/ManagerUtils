/*******************************************************************************
*
*  Filename    : DrawCMS.hpp
*  Description : Function for drawing CMS figure headers
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_DRAWCMS_HPP
#define MANAGERUTILS_PLOTUTILS_DRAWCMS_HPP

namespace plt{
/*******************************************************************************
*   ** DrawCMSLabel
*   Drawing the CMS Preliminary/Simulation label on top left of canvas
*******************************************************************************/
extern void DrawCMSLabel( int tag = PRELIMINARY );

/*******************************************************************************
   ** DrawLuminosity
   Drawing the energy scale and luminosity information on top right of canvas
*******************************************************************************/
extern void DrawLuminosity( double luminosity );

};

#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_DRAWCMS_HPP */
