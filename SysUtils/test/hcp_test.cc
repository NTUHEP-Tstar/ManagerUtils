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

   const std::string testmethod = "Asymptotic";

   CombineRequest req(
      "hcp_test.txt",
      "store1000.root",
      1000,
      testmethod,
      "",
      "test1000.txt"
   );
   CombineRequest req1(
      "hcp_test.txt",
      "store1200.root",
      1200,
      testmethod,
      "",
      "test1200.txt"
   );
   CombineRequest req2(
      "hcp_test.txt",
      "store1400.root",
      1400,
      testmethod,
      "",
      "/dev/null"
   );
   CombineRequest req3(
      "hcp_test.txt",
      "store1600.root",
      1600,
      testmethod,
      "",
      "/dev/null"
   );
   CombineRequest req4(
      "hcp_test.txt",
      "store1800.root",
      1800,
      testmethod,
      "",
      "/dev/null"
   );
   CombineRequest req5(
      "hcp_test.txt",
      "store2000.root",
      2000,
      testmethod,
      "",
      "/dev/null"
   );

   test.SubmitParallel( {req,req1,req2,req3,req4,req5} );

   return 0;
}
