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

//------------------------------------------------------------------------------
//   Constructor/Destructor
//------------------------------------------------------------------------------
Named::Named( const string& x ): _name(x)
{
   _latex_name = "";
}
Named::~Named()
{

}

//------------------------------------------------------------------------------
//   Extended Access funcionts
//------------------------------------------------------------------------------
string Named::RootTitle() const
{
   return ConvertToRootFlavour(_latex_name);
}

void Named::SetLatexName( const string& x )
{
   _latex_name = ConvertToLatexFlavour( x );
}

//------------------------------------------------------------------------------
//   Protected Member functions
//------------------------------------------------------------------------------
string Named::ConvertToLatexFlavour( const string& x )
{
   string ans = x ;
   for( auto& c : ans ){
      if( c == '#' ){
         c = '\\';
      }
   }
   return ans;
}
string Named::ConvertToRootFlavour( const string& x )
{
   string ans = x;
   for( auto& c : ans ){
      if( c == '\\' ){
         c = '#';
      }
   }
   return ans;
}
