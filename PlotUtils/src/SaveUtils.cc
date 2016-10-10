/*******************************************************************************
*
*  Filename    : SaveUtils.cc
*  Description : Plot saving utility functions  implementation
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include "TCanvas.h"
#include "TFile.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/******************************************************************************/

namespace plt {


/******************************************************************************/

void
SaveToPDF( TCanvas* c, const string& filename )
{
   // Command found at
   // http://tex.stackexchange.com/questions/66522/xelatex-rotating-my-figures-in-beamer
   const string temppdf = RandomFileName( 6, "pdf" ).c_str();
   char cmd[4096];

   c->SaveAs( temppdf.c_str() );

   sprintf(
      cmd,
      "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/screen -dNOPAUSE -dQUIET -dBATCH -sOutputFile=%s %s",
      filename.c_str(),
      temppdf.c_str()
      );

   system( cmd );
   system( ("rm "+ temppdf).c_str() );

   cout << "Saving Tcanvas " << c->GetName() << " to " << filename << endl;
}

/******************************************************************************/
void
SaveToROOT( TCanvas* c, const string& filename, const string& objname )
{
   TFile* myfile =  TFile::Open( filename.c_str(), "UPDATE" );
   c->Write( objname.c_str() , TFile::kOverwrite );
   delete myfile;
}

};
