/***************************************************************************//**
*
*  \file ConfigReader.hpp
*  \author Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Property Tree Configuration reader class powered by boost
*
*  Helper class to initialize classes stored in json format:
*  {
*    "StaticVar1" : <somevalue1>,
*    "StaticVar2" : <somevalue2>,
*
*    "Instance label1" : {
*       "Var1" : <somevalue3>,
*       "Var2" : <somevalue4>
*    },
*    "Instance label2" : {
*       "Var1" : <somevalue5>,
*       "Var2" : <somevalue6>
*    },
*  }
*
*******************************************************************************/
#ifndef MANAGERUTILS_COMMON_CONFIGREADER_HPP
#define MANAGERUTILS_COMMON_CONFIGREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

#include "ManagerUtils/Maths/interface/Parameter.hpp"


namespace mgr
{

extern void PrintPTree( const boost::property_tree::ptree&, unsigned level = 0 );

class ConfigReader
{

public:
  ConfigReader( const std::string& file_name );
  ConfigReader( const boost::property_tree::ptree& tree );
  virtual
  ~ConfigReader();


  // Static Variable Access
  bool                     GetStaticBool( const std::string& tag ) const;
  std::string              GetStaticString( const std::string& tag ) const;
  double                   GetStaticDouble( const std::string& tag ) const;
  Parameter                GetStaticParameter( const std::string& tag ) const;
  std::vector<std::string> GetStaticStringList( const std::string& tag ) const;
  std::vector<double>      GetStaticDoubleList( const std::string& tag ) const;
  bool                     HasStaticTag( const std::string& tag ) const;

  // Instance variable Access
  bool                     GetBool( const std::string& inst_tag, const std::string& tag ) const;
  Parameter                GetParameter( const std::string& inst_tag, const std::string& tag ) const;
  std::string              GetString( const std::string& inst_tag, const std::string& tag ) const;
  double                   GetDouble( const std::string& inst_tag, const std::string& tag ) const;
  std::vector<std::string> GetStringList( const std::string& inst_tag, const std::string& tag ) const;
  std::vector<double>      GetDoubleList( const std::string& inst_tag, const std::string& tag ) const;
  bool                     HasTag( const std::string& inst_tag, const std::string& tag ) const;

  // Instance detection functions
  bool                     HasInstance( const std::string& ) const;
  std::vector<std::string> GetInstanceList() const;

  // Debugging methods
  void DumpTree() const;

  // Generic return
  const boost::property_tree::ptree&
  ConfigTree() const { return _ptree; }

private:
  boost::property_tree::ptree _ptree;

  // Helper member functions
  static bool                     has_tag( const boost::property_tree::ptree& tree, const std::string& tag );
  static bool                     get_bool( const boost::property_tree::ptree& tree, const std::string& tag );
  static std::string              get_string( const boost::property_tree::ptree& tree, const std::string& tag );
  static double                   get_double( const boost::property_tree::ptree& tree, const std::string& tag );
  static Parameter                get_parameter( const boost::property_tree::ptree& tree, const std::string& tag );
  static std::vector<std::string> get_string_list( const boost::property_tree::ptree& tree, const std::string& tag );
  static std::vector<double>      get_double_list( const boost::property_tree::ptree& tree, const std::string& tag );

};

};

#endif/* end of include guard: MANAGERUTILS_COMMON_CONFIGREADER_HPP */
