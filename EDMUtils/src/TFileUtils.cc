/*******************************************************************************
 *
 *  Filename    : TFileUtils.cc
 *  Description : Implementation of utility functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TFile.h"
#include <string>

using namespace std;

// Returing a clone of a object for safe use in edm plugis
TObject* GetCloneFromFile( const string& filename, const string& objname )
{
   TFile*  file = TFile::Open( filename.c_str() );
   TObject* ans = file->Get( objname.c_str() )->Clone();
   file->Close();
   return ans;
}
