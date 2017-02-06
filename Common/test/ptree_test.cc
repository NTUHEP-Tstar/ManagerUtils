/*******************************************************************************
*
*  Filename    : ptree_test.cc
*  Description : Unit testing for ptree utility functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/BoostUtils/PTreeUtils.hpp"
#include "ManagerUtils/Common/interface/STLUtils.hpp"

#include <iostream>

using namespace std;
namespace pt = boost::property_tree;


/******************************************************************************/

int
main( int argc, char const* argv[] )
{
  pt::ptree tree = mgr::FromJsonFile( "test.json" );

  mgr::PrintPTree( tree );

  cout << mgr::seperator() << endl;

  cout << mgr::GetSingle<string>( tree, "Static1" ) << endl;

  cout << mgr::seperator() << endl;

  for( const auto x : mgr::GetList<int>(tree, "Instance1.var1" ) ){
    cout << x << endl;
  }

  cout << mgr::seperator() << endl;

  return 0;
}
