/*******************************************************************************
 *
 *  Filename    : Constants.hpp
 *  Description : Plotting configuration constants
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_CONSTANTS_HPP
#define MANAGERUTILS_PLOTUTILS_CONSTANTS_HPP

//------------------------------------------------------------------------------
//   Default TCanvas settings
//------------------------------------------------------------------------------
#define DEFAULT_CANVAS_WIDTH   650
#define DEFAULT_CANVAS_HEIGHT  500

//------------------------------------------------------------------------------
//   Default pad settings
//------------------------------------------------------------------------------
#define PLOT_X_MIN 0.1
#define PLOT_Y_MIN 0.1
#define PLOT_X_MAX 0.9
#define PLOT_Y_MAX 0.9

//------------------------------------------------------------------------------
//   Default font settings
//------------------------------------------------------------------------------
#define FONT_TYPE 43               // Sans + absolute font size
#define AXIS_TITLE_FONT_SIZE 16
#define AXIS_LABEL_FONT_SIZE 14

//------------------------------------------------------------------------------
//   Alignment aliasing
//------------------------------------------------------------------------------
#define BOTTOM_LEFT   11
#define BOTTOM_RIGHT  31
#define TOP_LEFT      13
#define TOP_RIGHT     33

//------------------------------------------------------------------------------
//   Plotting tags for label
//------------------------------------------------------------------------------
#define PRELIMINARY 0
#define SIMULATION  1
#define PUBLISH     -1

#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_CONSTANTS_HPP */
