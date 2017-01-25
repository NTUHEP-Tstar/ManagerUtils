/*******************************************************************************
*
*  Filename    : path_test.cc
*  Description : unit testing for path related utilities
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace mgr;

int
main( int argc, char const* argv[] )
{
  // Local globbing test
  vector<string> test_string_list = {
    "./",
    "./*",
    "./*.cc",
    "./*.json",
    "../*/*.cc",
    "../*/*.hpp"
  };

  for( const auto& test : test_string_list ){
    printf( "Testing [%s]:\n", test.c_str() );

    for( const auto& output : Glob( test ) ){
      printf( "\t%s\n", output.c_str() );
    }
  }

  // Remote testing
  vector<string> remotetestlist = {
    "root://eoscms.cern.ch//store/*",
    "root://eoscms.cern.ch//store/*/yichen",
    "root://eoscms.cern.ch//store/user/yichen/*/*/*/*/*.root"
  };

  cout << "Remote globbing test" << endl;

  for( const auto& remotetest : remotetestlist ){
    cout << ">>>  " << GetServerURL( remotetest ) << endl;
    cout << ">>>  " << GetRemotePath( remotetest ) << endl;

    for( const auto& path : Glob( remotetest ) ){
      cout << path << endl;
    }

    cout << "=====" << endl;
  }


  return 0;
}
