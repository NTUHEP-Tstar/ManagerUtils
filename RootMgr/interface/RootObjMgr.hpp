/*******************************************************************************
*
*  Filename    : RootObjMgr.hpp
*  Description : General RooFit object manager for using templates
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_ROOTOBJMGR_HPP
#define MANAGERUTILS_ROOTMGR_ROOTOBJMGR_HPP

#include "ManagerUtils/Common/interface/Named.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mgr
{

template<typename T>
class RootObjMgr : virtual public Named
{

public:
  RootObjMgr ( const std::string& );
  virtual
  ~RootObjMgr ();

  RootObjMgr( const RootObjMgr& )            = delete;
  RootObjMgr& operator=( const RootObjMgr& ) = delete;

  // Common objects for single object accessing
  void                     AddObj( T* );
  void                     RemoveObj( const std::string& );
  T*                       GetObj( const std::string& );
  const T*                 GetObj( const std::string& ) const;
  std::vector<std::string> ObjNameList() const;
  std::vector<T*>          GetObjContains( const std::string& );


  // C++ style iterators for looping objects (independent of the leading string)easiler
  // Notice that the dereferencing of the iterator will return an instance of  T*
  // so use loops only like : "for( const auto obj : objmgr )" (not the lack of referencing)
  typedef std::map<std::string, std::unique_ptr<T> > ObjContainer;
  class iterator;
  class const_iterator;

  inline iterator begin(){ return _objmap.begin(); }
  inline iterator end()  { return _objmap.end();   }
  inline const_iterator begin() const { return _objmap.begin();}
  inline const_iterator end()   const { return _objmap.end();  }

protected:
  std::string MakeStoreName( const std::string& ) const;
  std::string MakeAliasName( const std::string& ) const;

private:
  ObjContainer _objmap;
};

}/* mgr */

/*******************************************************************************
*   Including template class implementation
*******************************************************************************/
#include "ManagerUtils/RootMgr/src/RootObjMgr.ipp"

/*******************************************************************************
*   Including template interator classes
*******************************************************************************/
#include "ManagerUtils/RootMgr/src/RootObjIter.ipp"


#endif/* end of include guard: MANAGERUTILS_ROOTMGR_RootObjMgr_HPP */
