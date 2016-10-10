/*******************************************************************************
 *
 *  Filename    : OptsNamer.cc
 *  Description : Implementations for OptsNamer class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/OptsNamer.hpp"
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace mgr;
namespace pt  = boost::property_tree;
namespace opt = boost::program_options;

//------------------------------------------------------------------------------
//   Constructor and destructor
//------------------------------------------------------------------------------
OptsNamer::OptsNamer() {}
OptsNamer::~OptsNamer(){}

//------------------------------------------------------------------------------
//   Loading functions
//------------------------------------------------------------------------------
void
OptsNamer::LoadJsonFile( const string& filename )
{
   read_json( filename, _tree );
}

void
OptsNamer::LoadOptions( const variables_map& map )
{
   _map = map;
}

//------------------------------------------------------------------------------
//   Translation functions
//------------------------------------------------------------------------------
string OptsNamer::GetInput( const std::string& category )
{
   return _map["category"].as<string>();
}

string OptsNamer::GetExtName( const std::string& category, const std::string& exttag )
{
   const string instance    = GetInput(category);
   const string querystring = category + "." + instance + "." exttag;
   return _tree.get<string>(querystring);
}
