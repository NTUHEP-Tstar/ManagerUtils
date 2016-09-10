/*******************************************************************************
 *
 *  Filename    : parameter_format.cc
 *  Description : Unit testing for parameter formatting functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/Maths/interface/Parameter.hpp"
#include "ManagerUtils/Maths/interface/ParameterFormat.hpp"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
   Parameter x(123,23,0.01);

   cout << FloatingPoint( 0.01 , -1 ) << endl;

   cout << FloatingPoint( x , -1 ) << endl;
   cout << FloatingPoint( x , 2 ) << endl;
   cout << FloatingPoint( x , 10 ) << endl;
   cout << Scientific( x , 0  ) << endl;
   cout << Scientific( x , 2  ) << endl;
   cout << Scientific( x , 10 ) << endl;

   return 0;
}
