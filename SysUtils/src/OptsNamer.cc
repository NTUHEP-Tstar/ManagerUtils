/*******************************************************************************
 *
 *  Filename    : OptsNamer.cc
 *  Description : Implementations for OptsNamer class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/OptsNamer.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/diagnostic_information.hpp>

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
void OptsNamer::LoadJsonFile( const string& filename )
{
   read_json( filename, _tree );
}

int  OptsNamer::LoadOptions( const opt::options_description& desc, int argc, char* argv[] )
{
   try{
      opt::store(opt::parse_command_line(argc, argv, desc), _map);
      opt::notify(_map);
   } catch( boost::exception& e ){
      cerr << "Error parsing command!" << endl;
      cerr << desc << endl;
      cerr << boost::diagnostic_information(e);
      return PARSE_ERROR;
   }

   if( _map.count("help") ){
      cerr << desc << endl;
      return PARSE_HELP;
   }
   return PARSE_SUCESS;
}

//------------------------------------------------------------------------------
//   Translation functions
//------------------------------------------------------------------------------
string OptsNamer::GetInput( const string& category ) const
{
   return _map[category].as<string>();
}

string OptsNamer::GetExtName( const string& category, const string& exttag ) const
{
   const string instance    = GetInput(category);
   return query_tree( category, instance, exttag );
}

string OptsNamer::query_tree(
   const std::string& category,
   const std::string& instance,
   const std::string& tag
) const
{
   const string querystring = category + "." + instance + "." + tag;
   return _tree.get<string>(querystring);
}
