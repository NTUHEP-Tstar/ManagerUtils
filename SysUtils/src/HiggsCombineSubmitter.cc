/*******************************************************************************
*
*  Filename    : HiggsCombineSubmitter.cc
*  Description : Helper class for submitting higgs combine data cards
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#include "ManagerUtils/Common/interface/ConfigReader.hpp"
#include "ManagerUtils/Common/interface/STLUtils.hpp"
#include "ManagerUtils/Common/interface/Random.hpp"
#include "ManagerUtils/SysUtils/interface/HiggsCombineSubmitter.hpp"
#include "ManagerUtils/SysUtils/interface/PathUtils.hpp"
#include "ManagerUtils/SysUtils/interface/ProcessUtils.hpp"
#include "ManagerUtils/SysUtils/interface/TimeUtils.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;
namespace mgr {

/*******************************************************************************
*   Static member variables
*******************************************************************************/
const std::string HiggsCombineSubmitter::git_repo     = "https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git";
const std::string HiggsCombineSubmitter::higgs_subdir = "HiggsAnalysis/CombinedLimit/";

/*******************************************************************************
*   Constructor and destructor
*******************************************************************************/
HiggsCombineSubmitter::HiggsCombineSubmitter( const string& config_file )
{
  const ConfigReader config( config_file );
  _scram_arch           = config.GetStaticString( "Scram Arch" );
  _store_path           = config.GetStaticString( "Store Path" );
  _cmssw_version        = config.GetStaticString( "CMSSW Version" );
  _higg_combine_version = config.GetStaticString( "Higgs Combine Version" );

  if( !check_higgs_dir() ){// throwing error message for now
    init_higgs_dir();// print error message for how to install with current config
    throw std::invalid_argument( "Higgs Combine package doesn't exists!" );
  }
}

/******************************************************************************/

HiggsCombineSubmitter::~HiggsCombineSubmitter()
{
}


/*******************************************************************************
*   Main control flow
*******************************************************************************/
int
HiggsCombineSubmitter::SubmitDataCard( const CombineRequest& x ) const
{
  const string scriptfile = MakeScripts( x );
  const string cmd        = scriptfile + " &";// make it run in background
  cout << "Running script " << scriptfile << endl;
  const int result = system( cmd.c_str() );
  // system( ( "rm "+scriptfile ).c_str() );
  return result;
}

/******************************************************************************/

string
HiggsCombineSubmitter::MakeScripts( const CombineRequest& x )  const
{
  if( x.combine_method == "Asymptotic" ){
    return MakeAsymptoticScript( x );
  } else if( x.combine_method == "HybridNew" ){
    return MakeHybridNewScript( x );
  } else {
    throw std::invalid_argument( "Un-recongnized method!" );
  }
}

/******************************************************************************/

vector<int>
HiggsCombineSubmitter::SubmitParallel( const vector<CombineRequest>& list ) const
{
  static const string clearline =
    "\r                                                                               \r";
  boost::format waitmsg( "\r[%s] %d proceses alreading running, waiting to submit..." );
  unsigned running;

  for( const auto request : list ){
    running = HasProcess( "combine" );

    while( running >= NumOfThreads()/2 ){
      cout << waitmsg % CurrentDateTime() % running << flush;
      SleepMillSec( 100 );
      running = HasProcess( "combine" );
    }

    cout << clearline << flush;// clearing line
    SubmitDataCard( request );
    SleepMillSec( 1000 );// Wait one second before attempting to send next one
  }

  // Waiting for all scripts to finish
  WaitProcess( "combine" );
  WaitProcess(      "mv" );

  // Waiting for additional 3 seconds for all file transfer to complete
  SleepMillSec( 3000 );

  vector<int> ans( 0, list.size() );
  return ans;// Indiviual run results are not availiable.. yet
}

/*******************************************************************************
*   Helper private functions
*******************************************************************************/
bool
HiggsCombineSubmitter::check_higgs_dir() const
{
  if( !boost::filesystem::exists( higgs_cmssw_dir() ) ){
    cerr << "Designated CMSSW install path: [" << higgs_cmssw_dir() << "] not found!" << endl;
    return false;
  }

  const string higgspath = higgs_cmssw_dir() / higgs_subdir;
  if( !boost::filesystem::exists( higgspath ) ){
    cerr << "Higgs combine install path: [" << higgspath << "] not found!" << endl;
    return false;
  }

  // Git command for checking branch name
  // http://stackoverflow.com/questions/6245570/how-to-get-the-current-branch-name-in-git
  boost::format gitcheck_fmt( "cd %s && git branch | grep ^\\* | awk '{print $2}'" );
  const string gitcheck = str( gitcheck_fmt % higgspath );

  // Checking if error code is returned
  string output = GetCMDERROutput( gitcheck );
  if( output != "" ){
    cerr << "Error running command [" << gitcheck << "], check you installation directory!" << endl;
    return false;
  }

  // Checking output validity
  output = GetCMDSTDOutput( gitcheck );
  if( boost::trim_copy( output ) != _higg_combine_version ){
    cerr << boost::format( "Different version of higgs combined detected! Installed [%s], required [%s]" )
      % GetCMDSTDOutput( gitcheck )
      % _higg_combine_version
         << endl;
    cerr << gitcheck << endl;
    cerr << boost::format( "Try command [git checkout -b %s] in install directory [%s]" )
      % _higg_combine_version
      % higgspath
         << endl;
    return false;
  }
  return true;
}

/******************************************************************************/

void
HiggsCombineSubmitter::init_higgs_dir() const
{
  boost::format cmdformat(
    "export SCRAM_ARCH=%1%\n"
    "cd %2%\n"
    "cmsrel %3%\n"
    "cd %3%/src\n"
    "cmsenv\n"
    "git clone %4% %5%\n"
    "cd %5%\n"
    "git checkout -b %6%\n"
    );
  cout << "Try running the following commands" << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
  cout << cmdformat
    % _scram_arch
    % _store_path
    % _cmssw_version
    % git_repo
    % higgs_subdir
    % _higg_combine_version
       << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;

  // Script for automatically installing Higgs Combine package...
}

/******************************************************************************/

string
HiggsCombineSubmitter::higgs_cmssw_dir() const
{
  return _store_path /  _cmssw_version / "src";
}

/******************************************************************************/

string
HiggsCombineSubmitter::temp_scriptname( const int masspoint, const string& combine_method ) const
{
  boost::format scriptfmt( "/tmp/.temp_script_m%d_M%s_%s.sh" );
  string ans = str( scriptfmt % masspoint % combine_method % mgr::RandomString(6) );
  return ans;
}

/*******************************************************************************
*   Script generation for different methods
*******************************************************************************/
static boost::format bashheader( "#!/bin/bash\n" );
static boost::format chdirfmt( "cd %s\n" );
static boost::format cmsenv( "eval $(scramv1 runtime -sh 2> /dev/null) &> /dev/null\n" );
static boost::format dumptofile( "  &> %s" );

std::string
HiggsCombineSubmitter::MakeAsymptoticScript( const CombineRequest& x ) const
{
  static boost::format combinecommand( "combine -M Asymptotic -m %d %s %s" );
  static boost::format combinefilename( "%s/higgsCombineTest.Asymptotic.mH%s.root" );

  const string scriptname = temp_scriptname( x.masspoint, x.combine_method );

  ofstream scriptfile( scriptname, ofstream::out );

  scriptfile << bashheader << endl;
  scriptfile << chdirfmt % higgs_cmssw_dir() << endl;
  scriptfile << cmsenv << endl;

  scriptfile << combinecommand % x.masspoint % x.cardfile % x.additional_options;
  if( x.logfile != "stdout" ){
    scriptfile <<  dumptofile % x.logfile;
  }
  scriptfile << endl;
  scriptfile << "mv " << combinefilename % higgs_cmssw_dir() % x.masspoint << " " << x.storefile << endl;
  scriptfile.close();

  system( "sleep 1" );
  system( ( "chmod +x "+scriptname ).c_str() );
  return scriptname;
}

/******************************************************************************/

std::string
HiggsCombineSubmitter::MakeHybridNewScript( const CombineRequest& x ) const
{
  // Listing the common quantpoints;
  static const vector<double> quantpoints = {0.025, 0.16, 0.5, 0.84, 0.975};
  static boost::format obslimcmd( "combine -M HybridNew -H Asymptotic -m %d %s %s" );
  static boost::format obslimout( "%s/higgsCombineTest.HybridNew.mH%d.root" );
  static boost::format explimcmd( "combine -M HybridNew -m %d --expectedFromGrid=%lf %s %s" );
  static boost::format explimout( "%s/higgsCombineTest.HybridNew.mH%d.quant%.3lf.root" );

  const string scriptname = temp_scriptname( x.masspoint, x.combine_method );

  ofstream scriptfile( scriptname, ofstream::out );
  scriptfile << bashheader << endl;
  scriptfile << chdirfmt % higgs_cmssw_dir() << endl;
  scriptfile << cmsenv << endl;

  // Print command for observed limit
  scriptfile << obslimcmd % x.masspoint % x.cardfile % x.additional_options;
  if( x.logfile != "stdout" ){
    scriptfile << dumptofile % x.logfile;
  }
  scriptfile << endl;

  // Printing command for expected limit
  for( const auto& quant : quantpoints ){
    scriptfile << explimcmd % x.masspoint % quant % x.cardfile % x.additional_options;
    if( x.logfile != "stdout" ){
      scriptfile << dumptofile % x.logfile;
    }
    scriptfile << endl;
  }

  // Combining the the output root files
  // Adding -f flag to overide existing files
  scriptfile << "hadd -f " << x.storefile << " ";

  for( const auto& quant : quantpoints ){
    scriptfile << " " << explimout % higgs_cmssw_dir() % x.masspoint % quant;
  }

  scriptfile << " " << obslimout % higgs_cmssw_dir() % x.masspoint;
  scriptfile << " &> /dev/null" << endl;

  // Deleting the separate files
  for( const auto& quant : quantpoints ){
    scriptfile << "rm " << explimout % higgs_cmssw_dir() % x.masspoint % quant  << endl;
  }

  scriptfile << "rm  " << obslimout % higgs_cmssw_dir() % x.masspoint;

  // Closing file and tidying output
  scriptfile.close();
  system( "sleep 1" );// must wait for system to proces file
  system(         ( "chmod +x "+scriptname ).c_str() );
  return scriptname;

}


/*******************************************************************************
*   Combine request class
*******************************************************************************/
CombineRequest::CombineRequest(
  const std::string& _cardfile,
  const std::string& _storefile,
  const int          _masspoint,
  const std::string& _combine_method,
  const std::string& _additional_options,
  const std::string& _logfile
  ) :
  cardfile( ConvertToAbsPath( _cardfile ) ),
  storefile( ConvertToAbsPath( _storefile ) ),
  masspoint( _masspoint ),
  combine_method( _combine_method ),
  additional_options( _additional_options )
{
  if( _logfile != "stdout" ){
    logfile = ConvertToAbsPath( _logfile );
  } else {
    logfile = _logfile;
  }
}

CombineRequest::~CombineRequest()
{
}

}/* mgr */
