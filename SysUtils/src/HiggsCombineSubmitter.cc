/*******************************************************************************
 *
 *  Filename    : HiggsCombineSubmitter.cc
 *  Description : Helper class for submitting higgs combine data cards
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "ManagerUtils/SysUtils/interface/HiggsCombineSubmitter.hpp"
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"
#include "ManagerUtils/BaseClass/interface/ConfigReader.hpp"

#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;
using namespace mgr;

//------------------------------------------------------------------------------
//   Constructor and Destructor
//------------------------------------------------------------------------------
HiggsCombineSubmitter::HiggsCombineSubmitter( const string& config_file )
{
   const ConfigReader config( config_file );
   _scram_arch = config.GetStaticString("Scram Arch");
   _store_path = config.GetStaticString("Store Path");
   _cmssw_version = config.GetStaticString("CMSSW Version");
   _higg_combine_version = config.GetStaticString("Higgs Combine Version");

   if( !check_higgs_dir() ){ // throwing error message for now
      throw std::invalid_argument("Higgs Combine package doesn't exists!");
      // init_higgs_dir();
   }
}

HiggsCombineSubmitter::~HiggsCombineSubmitter()
{
}


//------------------------------------------------------------------------------
//   Main control flows
//------------------------------------------------------------------------------
static const string higgs_subdir   = "HiggsAnalysis/CombinedLimit";

int HiggsCombineSubmitter::SubmitDataCard( const CombineRequest& x ) const
{
   const string script_file = temp_script_name(x.mass_point,x.combine_method);
   MakeScripts(x);
   cout << "Running script " << script_file << endl;
   const int result =  system( script_file.c_str() );
   system( ("rm "+script_file).c_str() );
   return result;
}

string HiggsCombineSubmitter::MakeScripts( const CombineRequest& x )  const
{
   const string script_name     = temp_script_name(x.mass_point,x.combine_method);
   FILE* script_file = fopen( script_name.c_str() , "w" );
   fprintf( script_file , "#!/bin/bash\n" );
   fprintf( script_file , "cd %s\n" , higgs_cmssw_dir().c_str() );
   fprintf( script_file , "eval `scramv1 runtime -sh` &> /dev/null\n" );
   fprintf(
      script_file , "combine -M %s -m %d %s %s",
      x.combine_method.c_str(),
      x.mass_point,
      x.card_file.c_str(),
      x.additional_options.c_str()
   );
   if( x.log_file != "stdout" ){
      fprintf( script_file , "  &> %s" , x.log_file.c_str() );
   }
   fprintf( script_file ,"\n");
   fprintf( script_file , "result=$?\n" );
   fprintf(
      script_file , "mv %s/higgsCombineTest.%s.mH%d.root %s\n",
      higgs_cmssw_dir().c_str(),
      x.combine_method.c_str(),
      x.mass_point,
      x.output_file.c_str()
   );
   fprintf( script_file, "exit $result\n");
   fclose( script_file );
   system( "sleep 1" );
   system( ("chmod +x "+script_name).c_str() );
   return script_name;
}

vector<int> HiggsCombineSubmitter::SubmitParallel( const vector<CombineRequest>& list ) const
{
   vector<int>    ans(0,list.size());
   vector<thread> thread_list;
   for( const auto& req : list ){ // Naively generating new thread for all processes
      cout << "Creating thread for" << req.card_file << "..."  << endl;
      thread_list.push_back( thread( &HiggsCombineSubmitter::SubmitDataCard, this, req ));
   }
   for( auto& thd : thread_list ){ thd.join(); }
   return ans; // Indiviual run results are not availiable.. yet
}

//------------------------------------------------------------------------------
//    Helper private functions
//------------------------------------------------------------------------------
static const string git_repo       = "https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git";
static const string install_script = "./._higgs_install_script.sh" ;

bool HiggsCombineSubmitter::check_higgs_dir() const
{
   using namespace boost::filesystem;
   if( !exists(_store_path + "/" + _cmssw_version + "/src/" + higgs_subdir ) ){ return false; }
   // TODO: Make sure to correct version tag.. 2016-07-04
   return true;
}

void HiggsCombineSubmitter::init_higgs_dir() const
{// Script for automatically installing Higgs Combine package...
}

string HiggsCombineSubmitter::higgs_cmssw_dir() const
{
   return  _store_path + "/" + _cmssw_version + "/src/" ;
}

string HiggsCombineSubmitter::temp_script_name(const int mass_point, const string& combine_method) const
{
   char ans[1024];
   sprintf(
      ans , "%s/.temp_script_m%d_M%s.sh",
      getenv("PWD"),
      mass_point,
      combine_method.c_str()
   );
   return ans;
}

//------------------------------------------------------------------------------
//   CombineRequest class
//------------------------------------------------------------------------------

CombineRequest::CombineRequest(
   const std::string& _card_file,
   const std::string& _output_file,
   const int          _mass_point,
   const std::string& _combine_method,
   const std::string& _additional_options,
   const std::string& _log_file
):
   card_file( ConvertToAbsPath(_card_file)),
   output_file( ConvertToAbsPath(_output_file)),
   mass_point(_mass_point),
   combine_method(_combine_method),
   additional_options(_additional_options)
{
   if( _log_file != "stdout" ){
      log_file = ConvertToAbsPath(_log_file);
   } else {
      log_file = _log_file;
   }
}

CombineRequest::~CombineRequest()
{
}
