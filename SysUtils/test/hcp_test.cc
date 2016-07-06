/*******************************************************************************
 *
 *  Filename    : hcp_test.cc
 *  Description : Unit testing for higgs combine package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/HiggsCombineSubmitter.hpp"

using namespace std;
using namespace mgr;

int main(int argc, char const *argv[])
{

   HiggsCombineSubmitter test("hcp_test.json");
   CombineRequest req(
      "hcp_test.txt",
      "store.root",
      1000,
      "Asymptotic",
      "",
      "stdout"
   );

   test.SubmitDataCard( req );

   return 0;
}
