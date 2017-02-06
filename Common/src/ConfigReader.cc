/*******************************************************************************
*
*  Filename    : ConfigReader.cc
*  Description : Implementations for ConfigReader class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/ConfigReader.hpp"
#include "ManagerUtils/Common/interface/BoostUtils/PTreeUtils.hpp"
#include "ManagerUtils/Common/interface/STLUtils/StringUtils.hpp"

#include <boost/foreach.hpp>// For looping ptree
#include <iostream>
#include <string>

using namespace std;
using boost::property_tree::ptree;

namespace mgr {

/*******************************************************************************
*   Constructor/Destructor
*******************************************************************************/
ConfigReader::ConfigReader( const string& filename ):
  _ptree( FromJsonFile(filename ) )
{
}

/******************************************************************************/

ConfigReader::ConfigReader( const ptree& tree ):
  _ptree( tree )
{
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
  return mgr::GetSingle<bool>( _ptree, tag );
}

/******************************************************************************/

string
ConfigReader::GetStaticString( const string& tag ) const
{
  return mgr::GetSingle<string>( _ptree, tag );
}

/******************************************************************************/

double
ConfigReader::GetStaticDouble( const string& tag ) const
{
  return mgr::GetSingle<double>( _ptree, tag );
}

/******************************************************************************/

Parameter
ConfigReader::GetStaticParameter( const string& tag ) const
{
  return mgr::GetSingle<Parameter>( _ptree, tag );
}

/******************************************************************************/

vector<string>
ConfigReader::GetStaticStringList( const string& tag ) const
{
  return mgr::GetList<string>( _ptree, tag );
}

/******************************************************************************/

vector<double>
ConfigReader::GetStaticDoubleList( const string& tag ) const
{
  return mgr::GetList<double>( _ptree, tag );
}

/******************************************************************************/

bool
ConfigReader::HasStaticTag( const string& tag ) const
{
  return mgr::CheckQuery( _ptree, tag );
}


/*******************************************************************************
*   Instance variable access
*******************************************************************************/
bool
ConfigReader::GetBool( const string& inst_tag, const string& tag ) const
{
  return mgr::GetSingle<bool>( _ptree, inst_tag * tag );
}

/******************************************************************************/

string
ConfigReader::GetString( const string& inst_tag, const string& tag ) const
{
  return mgr::GetSingle<string>( _ptree, inst_tag * tag );
}

/******************************************************************************/

double
ConfigReader::GetDouble( const string& inst_tag, const string& tag ) const
{
  return mgr::GetSingle<double>( _ptree , inst_tag * tag );
}

/******************************************************************************/

Parameter
ConfigReader::GetParameter( const string& inst_tag, const string& tag ) const
{
  return mgr::GetSingle<Parameter>( _ptree,  inst_tag*tag );
}

/******************************************************************************/

vector<string>
ConfigReader::GetStringList( const string& inst_tag, const string& tag ) const
{
  return mgr::GetList<string>( _ptree, inst_tag * tag );
}

/******************************************************************************/

vector<double>
ConfigReader::GetDoubleList( const string& inst_tag, const string& tag ) const
{
  return mgr::GetList<double>( _ptree, inst_tag * tag );
}

/******************************************************************************/

bool
ConfigReader::HasTag( const string& inst_tag, const string& tag ) const
{
  return mgr::CheckQuery( _ptree.get_child(inst_tag),  tag );
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

}/* mgr */
