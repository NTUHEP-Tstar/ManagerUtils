/*******************************************************************************
*
*  Filename    : OptNamer.hpp
*  Description : Class for managing input options, and handling extended naming
*                using a external json configuration file.
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw
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
*  and use member functions to obtain the value "ABC" stored ad "name_type_1".
*
*******************************************************************************/
#ifndef MANAGERUTILS_COMMON_OPTNAMER_HPP
#define MANAGERUTILS_COMMON_OPTNAMER_HPP

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>

namespace mgr
{

class OptNamer
{

public:
  OptNamer( const std::string& filename ); // Must initialize with option naming json file
  virtual ~OptNamer ();

  enum PARSE_RESULTS
  {
    PARSE_SUCESS = 0,
    PARSE_HELP   = 1,
    PARSE_ERROR  = 2
  };

  OptNamer&  AddOptions( const boost::program_options::options_description& optdesc );
  int        ParseOptions( int argc, char** argv );

  // Basic access functions to option input
  bool    CheckInput( const std::string& opt ) const ;

  // Template functions for getting raw input values
  template<typename T>
  T GetInput( const std::string& opt ) const ;

  template<typename T>
  std::vector<T> GetInputList( const std::string& opt ) const ;

  // Template functions for getting extended values from json file
  template<typename T>
  T GetExt( const std::string& opt, const std::string& extag ) const;

  // template functions for general PTree query
  template<typename T>
  T ExtQuery(
    const std::string& option,
    const std::string& optioninput,
    const std::string& tag ) const;

  // Container access functions
  const boost::property_tree::ptree&           GetTree() const              { return _exttree; }
  const boost::program_options::options_description& GetDescription() const { return _optdesc; }
  const boost::program_options::variables_map& GetArgs() const              { return _argmap;  }

protected:
  const boost::property_tree::ptree&           Tree() const              { return _exttree; }
  const boost::program_options::options_description& Description() const { return _optdesc; }
  const boost::program_options::variables_map& Args() const              { return _argmap;  }
  boost::property_tree::ptree&                 Tree()       { return _exttree; }
  boost::program_options::options_description& Description(){ return _optdesc; }
  boost::program_options::variables_map&       Args()       { return _argmap;  }

private:
  boost::property_tree::ptree _exttree;
  boost::program_options::options_description _optdesc;
  boost::program_options::variables_map _argmap;
};

}

#include "ManagerUtils/Common/src/OptNamer.ipp"

#endif/* end of include guard: MANAGERUTILS_COMMON_OPTSNAMER_HPP */
