#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"
#include "ManagerUtils/SysUtils/interface/TimeUtils.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
using namespace mgr;

int main(int argc, char* argv[]) {
   string result = GetCMDOutput( "ls" );
   cout << NumOfThreads() << endl;
   cout << result << endl;
   cout << getenv("PWD") << endl;
   cout << system("cd ../") << endl;
   cout << getenv("PWD") << endl;
   cout << GetCMDOutput( "ls" ) << endl;
   // WaitProcess("zsh");
   return -1;
}
