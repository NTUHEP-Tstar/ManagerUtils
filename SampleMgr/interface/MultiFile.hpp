/*******************************************************************************
*
*  Filename    : MultiFile.hpp
*  Description : Template class for multi-file EDM structure handlers
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_SAMPLEMGR_MULTIFILE_HPP
#define MANAGERUTILS_SAMPLEMGR_MULTIFILE_HPP

#include <memory>
#include <string>
#include <vector>

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/FWLite/interface/Run.h"

namespace mgr {

template<typename STRUCTOBJ>
class MultiFile
{
public:

   /*******************************************************************************
   *   Constructor destructor and assignment operator
   *******************************************************************************/
   MultiFile();
   MultiFile( const std::vector<std::string>& filelist );
   MultiFile( const MultiFile& );
   ~MultiFile() ;
   MultiFile& operator=( const MultiFile& );
   MultiFile& reset( const std::vector<std::string>& filelist );

   /*******************************************************************************
   *   Casting operation to original object
   *******************************************************************************/
   STRUCTOBJ& Base();
   const STRUCTOBJ& Base() const;

   /*******************************************************************************
   *   Structure navigation operators to ovveride
   *******************************************************************************/
   MultiFile& operator++() ;
   MultiFile& toBegin()    ;
   bool       atEnd() const ;

   /*******************************************************************************
   *   File information
   *******************************************************************************/
   inline unsigned size() { return _size; }
   inline unsigned Size() { return _size; }
   inline unsigned FileCount() { return _filelist.size(); }
   inline unsigned FileIdx()   { return _currentfile - _filelist.begin(); }
   inline std::string CurrentFile() { return *_currentfile; }

private:
   std::vector<std::string> _filelist;
   std::vector<std::string>::const_iterator _currentfile;
   std::unique_ptr<STRUCTOBJ> _structptr;
   unsigned _size;

   /*******************************************************************************
   *   Helper private functions
   *******************************************************************************/
   unsigned getsize();
   bool     setfile();
};


/*******************************************************************************
*   Common Object type
*******************************************************************************/
typedef MultiFile<fwlite::Event> MultiFileEvent;
typedef MultiFile<fwlite::Run>   MultiFileRun;


}/* mgr */

/*******************************************************************************
*   Implementaion file inclusion
*******************************************************************************/
#include "ManagerUtils/SampleMgr/src/MultiFile.ipp"


#endif/* end of include guard: MANAGERUTILS_SAMPLEMGR_MULTIFILE_HPP */
