/*******************************************************************************
*
*  Filename    : SaveUtils.hpp
*  Description : Saving utils to combat ROOT's sub-par PDF outputs
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_PLOTUTILS_SAVEUTILS
#define MANAGERUTILS_PLOTUTILS_SAVEUTILS

#include "TCanvas.h"

namespace plt{
/*******************************************************************************
*   SaveToPDF - saving TCanvas to PDF file, invokes PDF correction ghostscript
*******************************************************************************/
void SaveToPDF( TCanvas* , const std::string& );

/*******************************************************************************
*   SaveToRoot - saving TCanvas to ROOT File
*******************************************************************************/
void SaveToROOT( TCanvas*, const std::string& filename, const std::string& objname );

}


#endif /* end of include guard: MANAGERUTILS_PLOTUTILS_SAVEUTILS */
