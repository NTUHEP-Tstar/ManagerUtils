/*******************************************************************************
 *
 *  Filename    : ConfigReader.hpp
 *  Description : Property Tree Configuration reader class powered by boost
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  This class takes Generic Property Tree files (json/xml) and Helps load it
 *  into class formats, with help function to translate tree entries into
 *  various data types
 *
*******************************************************************************/
#ifndef MANAGERUTILS_BASECLASS_CONFIGREADER_HPP
#define MANAGERUTILS_BASECLASS_CONFIGREADER_HPP

#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <string>

#include "ManagerUtils/Maths/interface/Parameter.hpp"

namespace mgr
{

class ConfigReader
{

public:
   ConfigReader( const std::string& file_name );
   ConfigReader( const boost::property_tree::ptree& tree );
   virtual ~ConfigReader();


   // Static Variable Access
   std::string  GetStaticString( const std::string& tag ) const ;
   double       GetStaticDouble( const std::string& tag ) const ;
   Parameter    GetStaticParameter( const std::string& tag ) const;
   std::vector<std::string> GetStaticStringList( const std::string& tag ) const;
   std::vector<double>      GetStaticDoubleList( const std::string& tag ) const;

   // Instance variable Access
   Parameter   GetParameter( const std::string& inst_tag, const std::string& tag ) const;
   std::string GetString( const std::string& inst_tag, const std::string& tag ) const;
   double      GetDouble( const std::string& inst_tag, const std::string& tag ) const;
   std::vector<std::string> GetStringList( const std::string& inst_tag, const std::string& tag ) const;
   std::vector<double>      GetDoubleList( const std::string& inst_tag, const std::string& tag ) const;

   // Debugging methods
   void DumpTree() const;

private:
   boost::property_tree::ptree _ptree;

   // Helper member functions
   static void print_sub_tree( const boost::property_tree::ptree& tree, unsigned print_level );
   static std::string get_string( const boost::property_tree::ptree& tree, const std::string& tag );
   static double      get_double( const boost::property_tree::ptree& tree, const std::string& tag );
   static Parameter   get_parameter( const boost::property_tree::ptree& tree, const std::string& tag );
   static std::vector<std::string> get_string_list( const boost::property_tree::ptree& tree, const std::string& tag );
   static std::vector<double>      get_double_list( const boost::property_tree::ptree& tree, const std::string& tag );

};

}

#endif /* end of include guard: MANAGERUTILS_BASECLASS_CONFIGREADER_HPP */
