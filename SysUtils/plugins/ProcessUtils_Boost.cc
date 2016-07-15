/*******************************************************************************
 *
 *  Filename    : ProcessUtils_Boost.cc
 *  Description : Exposing Process utility functions to python
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"
#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(pluginProcessUtils)
{
   def( "NumOfThreads" , NumOfThreads);
   def( "HasProcess"   , HasProcess  );
   def( "WaitProcess"  , WaitProcess ); 
}
