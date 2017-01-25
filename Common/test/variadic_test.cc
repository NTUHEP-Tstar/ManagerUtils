/*******************************************************************************
*
*  Filename    : variadic_test.cc
*  Description : Testing variadic template functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/Variadic.hpp"

#include <vector>
#include <iostream>

using namespace std;

int
main( int argc, char const* argv[] )
{
  vector<int> test = mgr::MakeVector<int>(1,2,3,4,5);
  //vector<int> test = mgr::MakeVector<int>();

  cout << test.size() << endl;
  for( auto x : test ){
    cout << x << endl;
  }


  return 0;
}
