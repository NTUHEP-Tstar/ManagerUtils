/*******************************************************************************
*
*  Filename    : SampleMgrLoader.cc
*  Description : Implementation of loading and unloading functions
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/

#include "ManagerUtils/SampleMgr/interface/SampleMgr.hpp"
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

namespace mgr {

/*******************************************************************************
*   Simple flat all-public struct to store SampleMgr double Cache
*******************************************************************************/
struct FlatCache
{
   double              original;
   double              selected;
   map<string, double> cachemap;
};

/******************************************************************************/

FlatCache
MakeCache( const SampleMgr& x )
{
   FlatCache ans;
   ans.original = x.OriginalEventCount();
   ans.selected = x.SelectedEventCount();
   ans.cachemap = x.DoubleCache();
   return ans;
}

/******************************************************************************/

FlatCache
MakeCache( const std::string& filename )
{
   FlatCache ans;
   ifstream file( filename );
   if( file.is_open() ){
      file >> ans.original;
      file >> ans.selected;

      while( 1 ){
         string name;
         double value;
         file >> name >> value;
         if( file.eof() ){ break; }
         ans.cachemap[name] = value;
      }
   }
   return ans;
}

/******************************************************************************/

void
WriteCache( const FlatCache& x, const string& filename )
{
   ofstream file( filename );
   file << fixed << setprecision(10) ;
   file << x.original << endl;
   file << x.selected << endl;

   for( const auto& cachepair : x.cachemap ){
      file << cachepair.first << " " << cachepair.second << endl;
   }

   file.close();
}

/******************************************************************************/

void
MergeCache( FlatCache& x, const FlatCache& y )
{
   x.original = y.original;
   x.selected = y.selected;

   for( const auto cachepair : y.cachemap ){
      x.cachemap[cachepair.first] = cachepair.second;
   }
}

/******************************************************************************/

void
SaveCacheToFile( const SampleMgr& x, const std::string& filename )
{
   FlatCache mgrcache  = MakeCache( x );
   FlatCache filecache = MakeCache( filename );
   MergeCache( filecache, mgrcache );
   WriteCache( filecache, filename );
}

/******************************************************************************/

void
LoadCacheFromFile( SampleMgr& x, const std::string& filename )
{
   FlatCache filecache = MakeCache( filename );
   x.SetOriginalEventCount( filecache.original );
   x.SetSelectedEventCount( filecache.selected );

   for( const auto& cachepair : filecache.cachemap ){
      x.AddCacheDouble( cachepair.first, cachepair.second );
   }
}

}/* mgr namespace */
