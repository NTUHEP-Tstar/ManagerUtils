/*******************************************************************************
*
*  Filename    : OptsNamer.cc
*  Description : Implementations for OptsNamer class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/OptsNamer.hpp"

#include <boost/exception/diagnostic_information.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

using namespace std;
namespace pt  = boost::property_tree;
namespace opt = boost::program_options;

namespace mgr {
/*******************************************************************************
*   Constructor/destructor
*******************************************************************************/
OptsNamer::OptsNamer(){}
OptsNamer::~OptsNamer(){}

/*******************************************************************************
*  Loading functions
*******************************************************************************/
void
OptsNamer::LoadJsonFile( const string& filename )
{
   read_json( filename, _tree );
}

/******************************************************************************/

int
OptsNamer::LoadOptions( const opt::options_description& desc, int argc, char* argv[] )
{
   try {
      opt::store( opt::parse_command_line( argc, argv, desc ), _map );
      opt::notify( _map );
   } catch( boost::exception& e ){
      cerr << "Error parsing command!" << endl;
      cerr << desc << endl;
      cerr << boost::diagnostic_information( e );
      return PARSE_ERROR;
   }

   if( _map.count( "help" ) ){
      cerr << desc << endl;
      return PARSE_HELP;
   }

   return PARSE_SUCESS;
}

/*******************************************************************************
*   Input access functions
*******************************************************************************/
bool
OptsNamer::HasOption( const std::string& opt ) const
{
   return _map.count( opt );
}

/******************************************************************************/

string
OptsNamer::InputStr( const std::string& opt ) const
{
   string ans;// Specialization that forces conversion
   try {
      return _map[opt].as<string>();
   } catch( std::exception e ){
   }
   try {
      return boost::lexical_cast<string>( _map[opt].as<int>() );
   } catch( std::exception e ){
   }
   try {
      return boost::lexical_cast<string>( _map[opt].as<double>() );
   } catch( std::exception e ){
   }
   throw std::invalid_argument( "Cannot convert options!" );
   return ans;
}

/******************************************************************************/

double
OptsNamer::InputDou( const std::string& opt ) const
{
   return _map[opt].as<double>();
}

/******************************************************************************/

int
OptsNamer::InputInt( const std::string& opt ) const
{
   return _map[opt].as<int>();
}


/*******************************************************************************
*   Translation functions for extended options
*******************************************************************************/
string
OptsNamer::GetInput( const string& category ) const
{
   return _map[category].as<string>();
}

/******************************************************************************/

string
OptsNamer::GetExtName( const string& category, const string& exttag ) const
{
   const string instance = GetInput( category );
   return query_tree( category, instance, exttag );
}


/******************************************************************************/
double
OptsNamer::GetExtDouble( const string& category, const string& exttag ) const
{
   const string instance = GetInput( category );
   const string query    = category + "." + instance + "." + exttag ;
   return _tree.get<double>( query );
}

/******************************************************************************/

string
OptsNamer::query_tree(
   const std::string& category,
   const std::string& instance,
   const std::string& tag
   ) const
{
   const string querystring = category + "." + instance + "." + tag;
   return _tree.get<string>( querystring );
}

} /* mgr */
