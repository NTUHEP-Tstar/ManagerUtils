/*******************************************************************************
 *
 *  Filename    : path_test.cc
 *  Description : unit testing for path related utilities
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char const* argv[]) {

   vector<string> test_string_list = {
      "./",
      "./*",
      "./*.cc",
      "./*.json",
      "../*/*.cc",
      "../*/*.hpp"
   };

   for( const auto& test : test_string_list ){
      printf( "Testing [%s]:\n" , test.c_str() );
      for( const auto& output : Glob(test) ){
         printf("\t%s\n", output.c_str() );
      }
   }

   return 0;
}
