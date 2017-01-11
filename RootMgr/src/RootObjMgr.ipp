/*******************************************************************************
*
*  Filename    : RootObjMgr.ipp
*  Description : Implementation of RootObjMgr template class
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_RootObjMgr_IPP
#define MANAGERUTILS_ROOTMGR_RootObjMgr_IPP

#include "boost/algorithm/string.hpp"

/*******************************************************************************
*   Constructor and destructor
*******************************************************************************/
template<typename T>
mgr::RootObjMgr<T>::RootObjMgr( const std::string& x ) :
   mgr::Named( x )
{
}

/******************************************************************************/

template<typename T>
mgr::RootObjMgr<T>::~RootObjMgr()
{

}

/*******************************************************************************
*   Addition and removal functions
*******************************************************************************/
template<typename T>
void
mgr::RootObjMgr<T>::AddObj( T* obj )
{
   const std::string newsetname = MakeStoreName( obj->GetName() );
   const std::string alias      = MakeAliasName( obj->GetName() );

   _objmap.erase( alias );// deleting existing instance if already exist

   obj->SetName( newsetname.c_str() );
   _objmap[alias] = std::unique_ptr<T>( obj );
}

/******************************************************************************/

template<typename T>
void
mgr::RootObjMgr<T>::RemoveObj( const std::string& name )
{
   if( _objmap.count( name ) ){
      _objmap.erase( name );
   } else {

   }
}

/*******************************************************************************
*   Object access functions
*******************************************************************************/
template<typename T>
T*
mgr::RootObjMgr<T>::GetObj( const std::string& name )
{
   if( _objmap.count( name ) ){
      return _objmap.at( name ).get();
   } else {
      return NULL;
   }
}

/******************************************************************************/

template<typename T>
const T*
mgr::RootObjMgr<T>::GetObj( const std::string& name ) const
{
   if( _objmap.count( name ) ){
      return _objmap.at( name ).get();
   } else {
      return NULL;
   }
}

/*******************************************************************************
*   Object listing functions
*******************************************************************************/
template<typename T>
std::vector<std::string>
mgr::RootObjMgr<T>::ObjNameList() const
{
   std::vector<std::string> ans;

   for( const auto& mypair : _objmap ){
      ans.push_back( mypair.first );
   }

   return ans;
}

/******************************************************************************/

template<typename T>
std::vector<T*>
mgr::RootObjMgr<T>::GetObjContains( const std::string& substring )
{
   std::vector<T*> ans;

   for( auto& mypair : _objmap ){
      if( mypair.first.find( substring ) != std::string::npos ){
         ans.push_back( mypair.second.get() );
      }
   }

   return ans;
}

/*******************************************************************************
*   Naming convention functions
*******************************************************************************/
template<typename T>
std::string
mgr::RootObjMgr<T>::MakeStoreName( const std::string& objname ) const
{
   if( boost::algorithm::starts_with( objname, Name() ) ){
      return objname;
   } else {
      return Name() + objname;
   }
}

/******************************************************************************/

template<typename T>
std::string
mgr::RootObjMgr<T>::MakeAliasName( const std::string& objname ) const
{
   if( boost::algorithm::starts_with( objname, Name() ) ){
      std::string newname = objname;
      newname.erase( 0, Name().length() );
      return newname;
   } else {
      return objname;
   }
}


#endif/* end of include guard: MANAGERUTILS_ROOTMGR_RootObjMgr_IPP */
