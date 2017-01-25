/*******************************************************************************
*
*  Filename    : ConfigReader.cc
*  Description : Implementations for ConfigReader class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/Common/interface/ConfigReader.hpp"

#include <boost/foreach.hpp>// For looping ptree
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <string>

using namespace std;
using boost::property_tree::ptree;

namespace mgr {
/*******************************************************************************
*   Helper functions
*******************************************************************************/
void
PrintPTree( const ptree& tree, unsigned print_level )
{
  for( const auto& it : tree ){
    for( unsigned i = 0; i < print_level; ++i ){
      cout << "\t" << flush;
    }

    std::cout << it.first << ": " << it.second.get_value<std::string>() << std::endl;
    PrintPTree( it.second, print_level + 1 );
  }
}

/*******************************************************************************
*   Constructor/Destructor
*******************************************************************************/
ConfigReader::ConfigReader( const string& file_name )
{
  read_json( file_name, _ptree );// Try to read to json file
}

/******************************************************************************/

ConfigReader::ConfigReader( const ptree& tree )
{
  _ptree = tree;
}

/******************************************************************************/

ConfigReader::~ConfigReader(){}


/*******************************************************************************
*   Debugging functions
*******************************************************************************/
void
ConfigReader::DumpTree() const
{
  PrintPTree( _ptree, 0 );
}

/*******************************************************************************
*   Static variable access functions
*******************************************************************************/
bool
ConfigReader::GetStaticBool( const string& tag ) const
{
  return get_bool( _ptree, tag );
}

string
ConfigReader::GetStaticString( const string& tag ) const
{
  return get_string( _ptree, tag );
}

/******************************************************************************/

double
ConfigReader::GetStaticDouble( const string& tag ) const
{
  return get_double( _ptree, tag );
}

/******************************************************************************/

Parameter
ConfigReader::GetStaticParameter( const string& tag ) const
{
  return get_parameter( _ptree, tag );
}

/******************************************************************************/

vector<string>
ConfigReader::GetStaticStringList( const string& tag ) const
{
  return get_string_list( _ptree, tag );
}

/******************************************************************************/

vector<double>
ConfigReader::GetStaticDoubleList( const string& tag ) const
{
  return get_double_list( _ptree, tag );
}

/******************************************************************************/

bool
ConfigReader::HasStaticTag( const string& tag ) const
{
  return has_tag( _ptree, tag );
}


/*******************************************************************************
*   Instance variable access
*******************************************************************************/
bool
ConfigReader::GetBool( const string& inst_tag, const string& tag ) const
{
  return get_bool( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

string
ConfigReader::GetString( const string& inst_tag, const string& tag ) const
{
  return get_string( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

double
ConfigReader::GetDouble( const string& inst_tag, const string& tag ) const
{
  return get_double( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

Parameter
ConfigReader::GetParameter( const string& inst_tag, const string& tag ) const
{
  return get_parameter( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

vector<string>
ConfigReader::GetStringList( const string& inst_tag, const string& tag ) const
{
  return get_string_list( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

vector<double>
ConfigReader::GetDoubleList( const string& inst_tag, const string& tag ) const
{
  return get_double_list( _ptree.get_child( inst_tag ), tag );
}

/******************************************************************************/

bool
ConfigReader::HasTag( const string& inst_tag, const string& tag ) const
{
  return has_tag( _ptree.get_child( inst_tag ), tag );
}


/*******************************************************************************
*   Instance detection functions
*******************************************************************************/
bool
ConfigReader::HasInstance( const string& inst_tag ) const
{
  return HasStaticTag( inst_tag );
}

/******************************************************************************/

vector<string>
ConfigReader::GetInstanceList() const
{
  vector<string> ans;

  for( const auto& it : _ptree ){
    string tag = it.first;
    if( tag.front() != '_' ){
      ans.push_back( tag );
    }
  }

  return ans;
}


/*******************************************************************************
*   Helper private functions, PTREE structure crawlers
*******************************************************************************/
bool
ConfigReader::has_tag( const ptree& tree, const string& tag )
{
  return tree.find( tag ) != tree.not_found();
}

/******************************************************************************/
bool
ConfigReader::get_bool( const ptree& tree, const string& tag )
{
  return tree.get<bool>( tag );
}

/******************************************************************************/

string
ConfigReader::get_string( const ptree& tree, const string& tag )
{
  return tree.get<string>( tag );
}

/******************************************************************************/

double
ConfigReader::get_double( const ptree& tree, const string& tag )
{
  return tree.get<double>( tag );
}

/******************************************************************************/

vector<string>
ConfigReader::get_string_list( const ptree& tree, const string& tag )
{
  vector<string> ans;
  BOOST_FOREACH( const ptree::value_type &v, tree.get_child( tag ) ){
    if( !v.first.empty() ){
      cerr << "Warning! Skipping over illegal format at branch: (" << tag
           << ")  with index value: (" << v.first.data() << ")" << endl;
      continue;
    }
    // cout << v.second.data() << endl;
    ans.push_back( v.second.data() );
  }
  return ans;
}

/******************************************************************************/

vector<double>
ConfigReader::get_double_list( const ptree& tree, const string& tag  )
{
  vector<double> ans;
  BOOST_FOREACH( const ptree::value_type &v, tree.get_child( tag ) ){
    if( !v.first.empty() ){
      cerr << "Warning! Skipping over illegal format at branch: (" << tag
           << ")  with index value: (" << v.first.data() << ")" << endl;
      continue;
    }
    // cout << v.second.data() << endl;
    ans.push_back( stod( v.second.data() ) );
  }
  return ans;
}

/******************************************************************************/

Parameter
ConfigReader::get_parameter( const ptree& tree, const string& tag )
{
  vector<double> input = get_double_list( tree, tag );
  input.resize( 3, 0 );
  if( input[0] == 0 ){
    input[0] = 1;
  }
  if( input[1] != 0 && input[2] == 0 ){
    input[2] = input[1];
  }
  return Parameter( input[0], input[1], input[2] );
}

}/* mgr */
