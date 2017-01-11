/*******************************************************************************
*
*  Filename    : Format.cc
*  Description : Implementation for boost::format wrapper function
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Main reference:
*  http://www.boost.org/doc/libs/1_63_0/libs/format/doc/format.html#exceptions
*******************************************************************************/
#include <boost/format.hpp>
#include <string>

namespace mgr{

boost::format format( const std::string& fmt_string )
{
   boost::format ans(fmt_string);
   ans.exceptions( boost::io::no_error_bits ) ; // disabling all error bits
   return ans;
}

}
