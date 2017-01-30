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

#include <boost/format.hpp>
#include <iostream>
#include <string>

using namespace std;

/******************************************************************************/

namespace mgr {


/******************************************************************************/

void
SaveToPDF( TCanvas* c, const string& filename )
{
  // Saving to a temporary file /tmp/XXXXXX<filename>.pdf
  // Forcing postfix to be '.pdf'
  const string temppdf = "/tmp/" + RandomFileName( 6, "", false ) + "_" + Basename( filename ) + ".pdf";

  c->SaveAs( temppdf.c_str() );

  CheckPath( filename );

  // Command found at
  // http://tex.stackexchange.com/questions/66522/xelatex-rotating-my-figures-in-beamer
  const string cmd = boost::str( boost::format(
      "gs"
      "  -sDEVICE=pdfwrite"
      "  -dCompatibilityLevel=1.4"
      "  -dPDFSETTINGS=/screen"
      "  -dNOPAUSE"
      "  -dQUIET"
      "  -dBATCH"
      "  -sOutputFile=%s"
      "  %s"
      ) % filename % temppdf );

  system( cmd.c_str() );
  system( ( "rm "+ temppdf ).c_str() );

  cout << "Saving TCanvas " << c->GetName() << " to " << filename << endl;
}

/******************************************************************************/
void
SaveToROOT( TCanvas* c, const string& filename, const string& objname )
{
  CheckPath( filename );
  TFile* myfile = TFile::Open( filename.c_str(), "UPDATE" );
  c->Write( objname.c_str(), TFile::kOverwrite );
  delete myfile;
}

};
