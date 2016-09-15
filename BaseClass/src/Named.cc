/*******************************************************************************
*
*  Filename    : Named.cc
*  Description : Implmentation to convertion functions in Named class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/BaseClass/interface/Named.hpp"

using namespace std;
using namespace mgr;

// ------------------------------------------------------------------------------
//   Constructor/Destructor
// ------------------------------------------------------------------------------
Named::Named( const string& x ) :
   _name( x ),
   _latexname( "" ),
   _rootname( "" )
{
}
Named::~Named()
{

}

void
Named::SetLatexName( const string& x )
{
   _latexname = x;
}

void
Named::SetRootName( const string& x )
{
   _rootname = x;
}
