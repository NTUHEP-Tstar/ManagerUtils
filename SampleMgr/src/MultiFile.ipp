/*******************************************************************************
*
*  Filename    : Multifile.ipp
*  Description : Implementention of Template Class MultiFile
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*  Object TYPENAME must be explicitly declared, do not attempt to invoke
*  namespace keyword
*
*******************************************************************************/
#ifndef MANAGERUTILE_SAMPLEMGR_MULTIFILE_IPP
#define MANAGERUTILE_SAMPLEMGR_MULTIFILE_IPP

#include <iostream>
#include <exception>

#include "TFile.h"

/*******************************************************************************
*   Constructor, desctructor and assignment
*******************************************************************************/
template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>::MultiFile()
{
   _size = 0;
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>::MultiFile( const std::vector<std::string> & x )
{
   reset( x );
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>::~MultiFile()
{
   // FWlite object handled by unique_ptr object
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>::MultiFile( const mgr::MultiFile<STRUCTOBJ>& x )
{
   *this = x;
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>&
mgr::MultiFile<STRUCTOBJ>::operator=( const mgr::MultiFile<STRUCTOBJ>& x )
{
   return reset( x._filelist );
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>&
mgr::MultiFile<STRUCTOBJ>::reset( const std::vector<std::string>& x )
{
   // Error checking
   if( x.empty() ){
      throw std::invalid_argument("mgr::MultiFile cannot have blank vector as input");
   }

   _filelist = x;
   _size     = getsize();
   toBegin();
   return *this;
}


/*******************************************************************************
*   Base Object Casting
*******************************************************************************/
template<typename STRUCTOBJ>
STRUCTOBJ&
mgr::MultiFile<STRUCTOBJ>::Base()
{
   return *_structptr;
}

/******************************************************************************/

template<typename STRUCTOBJ>
const STRUCTOBJ&
mgr::MultiFile<STRUCTOBJ>::Base() const
{
   return *_structptr;
}


/*******************************************************************************
*   Operators ob struct objects to override
*******************************************************************************/
template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>&
mgr::MultiFile<STRUCTOBJ>::operator++()
{
   if( _currentfile == _filelist.end() ){ return *this; }

   ++( *_structptr );
   if( _structptr->atEnd() ){
      do {
         ++_currentfile;
         if( _currentfile != _filelist.end() && setfile() ){
            _structptr->toBegin();
         }
      } while( _structptr->size() == 0 && _currentfile != _filelist.end() );
   }
   return *this;
}

/******************************************************************************/

template<typename STRUCTOBJ>
mgr::MultiFile<STRUCTOBJ>&
mgr::MultiFile<STRUCTOBJ>::toBegin()
{
   _currentfile = _filelist.begin();
   if( setfile() ){
      _structptr->toBegin();
   } else {
      return ++(*this);
   }
   return *this;
}

/******************************************************************************/

template<typename STRUCTOBJ>
bool
mgr::MultiFile<STRUCTOBJ>::atEnd() const
{
   return _currentfile == _filelist.end();
}


/*******************************************************************************
*   Helper private functions
*******************************************************************************/
template<typename STRUCTOBJ>
unsigned
mgr::MultiFile<STRUCTOBJ>::getsize()
{
   unsigned ans = 0;

   for( _currentfile = _filelist.begin(); _currentfile != _filelist.end(); ++_currentfile ){
      if( setfile() ){
         ans += _structptr->size();
      } else {
         std::cerr << "Warning! Invalid file [" << *_currentfile << "] Skipped!" << std::endl;
      }
   }

   return ans;
}

/******************************************************************************/

template<typename STRUCTOBJ>
bool
mgr::MultiFile<STRUCTOBJ>::setfile()
{
   if( _currentfile != _filelist.end() ){
      TFile* newfile = TFile::Open( _currentfile->c_str() );
      if( newfile ){
         _structptr.reset( new STRUCTOBJ( newfile ) );
         return true;
      } else {
         return false;
      }
   } else {
      return false;
   }
}


#endif/* end of include guard: MANAGERUTILE_SAMPLEMGR_MULTIFILE_IPP */
