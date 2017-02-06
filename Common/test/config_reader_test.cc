/*******************************************************************************
*
*  Filename    : config_reader_test.cc
*  Description : Unit testing for configuration file reader
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/ConfigReader.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  mgr::ConfigReader reader("test.json");

  for(const auto x :  reader.GetDoubleList("Instance1","var1") ){
    cout << x << endl;
  }

  cout << reader.HasTag("Instance1","var1") << endl;

  cout << (reader.ConfigTree().find("Instance1.var1") == reader.ConfigTree().not_found()) << endl;

  cout << reader.HasInstance("Instance1") << endl;
  return 0;
}
