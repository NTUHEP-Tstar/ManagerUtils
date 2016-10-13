/*******************************************************************************
 *
 *  Filename    : HiggsCombineSubmitter.hpp
 *  Description : Helper class to submit settings to Higgs combine
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_SYSUTILS_HIGGSCOMBINESUBMITTER_HPP
#define MANAGERUTILS_SYSUTILS_HIGGSCOMBINESUBMITTER_HPP

#include <string>
#include <vector>

namespace mgr {

class CombineRequest; //see below for details

class HiggsCombineSubmitter {
public:
   HiggsCombineSubmitter( const std::string& config_file );
   virtual ~HiggsCombineSubmitter();

   int              SubmitDataCard( const CombineRequest& ) const ;
   std::string      MakeScripts( const CombineRequest& ) const ;
   std::vector<int> SubmitParallel( const std::vector<CombineRequest>& ) const ;

private:
   std::string _scram_arch;
   std::string _store_path;
   std::string _cmssw_version;
   std::string _higg_combine_version;

   // Helper functions
   void        init_higgs_dir()  const ;
   bool        check_higgs_dir() const ;
   std::string higgs_cmssw_dir() const ;
   std::string temp_script_name(
      const int masspoint,
      const std::string& combine_method
   ) const;
};

class CombineRequest { // Pure data class for submission management
public:
   CombineRequest(
      const std::string& _card_file,
      const std::string& _output_file,
      const int          _mass_point,
      const std::string& _combine_method,
      const std::string& _additional_options = "",
      const std::string& _log_file = "/dev/null"
   ); // Constructor with default arguments
   ~CombineRequest();

   std::string card_file ;
   std::string output_file;
   int         mass_point;
   std::string combine_method;
   std::string additional_options;
   std::string log_file;
};

}

#endif /* end of include guard: MANAGERUTILS_SYSUTILS_HIGGSCOMBINESUBMITTER_HPP */
