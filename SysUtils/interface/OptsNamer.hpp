/*******************************************************************************
 *
 *  Filename    : OptsNamer.hpp
 *  Description : Return strings based on boost program_options input
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Given the json in the format of :
      Catetory :
         Instance_1:
            name_type_1: "ABC"
            name_type_2: "DEF"
         Instance_2:
            name_type_1: "GHI"
            name_type_2: "JKL"
 *  We could define a the boost program options with <Category>
 *  and use member functions to obtain "name_type_x". This class will assume all
 *  std::string type inputs
 *
 *  Powered by boost::program_options and boost::property tree
 *
*******************************************************************************/
#ifndef MANAGERUTILS_SYSUTILS_OPTSNAMER_HPP
#define MANAGERUTILS_SYSUTILS_OPTSNAMER_HPP

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>

namespace mgr
{

class OptsNamer {

public:
   OptsNamer();
   virtual ~OptsNamer ();

   enum PARSE_RESULTS {
      PARSE_SUCESS = 0,
      PARSE_HELP   = 1,
      PARSE_ERROR  = 2
   };

   void LoadJsonFile( const std::string& filename );
   int  LoadOptions( const boost::program_options::options_description& optdesc, int argc, char* argv[] );

   // Basic access functions to option input
   bool        HasOption( const std::string& opt ) const ;
   std::string InputStr ( const std::string& opt ) const ;
   double      InputDou ( const std::string& opt ) const ;
   int         InputInt ( const std::string& opt ) const ;

   std::string GetInput( const std::string& category ) const ;
   std::string GetExtName( const std::string& category,  const std::string& exttag ) const;
   double      GetExtDouble( const std::string& category, const std::string& exttag ) const;

   std::string query_tree(
      const std::string& category,
      const std::string& instance,
      const std::string& tag ) const ;

   const boost::program_options::variables_map& GetMap() const { return _map;  }
   const boost::property_tree::ptree&           GetTree()const { return _tree; }

private:
   boost::property_tree::ptree              _tree;
   boost::program_options::variables_map    _map;
};

}

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_OPTSNAMER_HPP */
