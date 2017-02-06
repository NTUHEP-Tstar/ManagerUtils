/*******************************************************************************
*
*  Filename    : OptNamer.cc
*  Description : Implementations for OptNamer class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/OptNamer.hpp"

#include <boost/exception/diagnostic_information.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace std;
namespace pt  = boost::property_tree;
namespace opt = boost::program_options;

namespace mgr {
/*******************************************************************************
*   Constructor/destructor
*******************************************************************************/
OptNamer::OptNamer( const string& filename ) :
  _exttree( FromJsonFile(filename) )
{
  _optdesc.add_options()
    ( "help,h", "print help options and exit program" )
  ;
}

/******************************************************************************/

OptNamer::~OptNamer(){}

/*******************************************************************************
*  Loading functions
*******************************************************************************/
OptNamer& OptNamer::AddOptions( const opt::options_description& desc )
{
  Description().add( desc );
  return *this;
}

/******************************************************************************/

int
OptNamer::ParseOptions( int argc, char** argv )
{
  try {
    opt::store( opt::parse_command_line( argc, argv, Description() ), Args() );
    opt::notify( Args() );
  } catch( boost::exception& e ){
    cerr << "Error parsing command!" << endl;
    cerr << boost::diagnostic_information( e );
    cerr << Description() << endl;
    return PARSE_ERROR;
  }

  if( Args().count( "help" ) ){
    cerr << Description() << endl;
    return PARSE_HELP;
  }

  return PARSE_SUCESS;
}

/*******************************************************************************
*   Input access functions
*******************************************************************************/
bool
OptNamer::CheckInput( const std::string& opt ) const
{
  return Args().count( opt );
}

}/* mgr */
