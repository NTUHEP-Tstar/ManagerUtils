/*******************************************************************************
*
*  Filename    : RooFitUtils.ipp
*  Description : Implementation for template functions for RooFitUtils conversion
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_ROOTMGR_ROOFITUTILS_IPP
#define MANAGERUTILS_ROOTMGR_ROOFITUTILS_IPP

template<typename T>
std::vector<T*>
mgr::FromRooArgSet( RooArgSet* argset )
{
  std::vector<T*> ans( argset->getSize() );
  TIterator* citer = argset->createIterator();
  RooAbsArg* arg;

  while( ( arg = (RooAbsArg*)citer->Next() ) ){
    T* casted = dynamic_cast<T*>( arg );
    if( casted != 0 ){
      ans.push_back( casted );
    }
  }

  delete citer;
  return ans;
}


#endif/* end of include guard: MANAGERUTILS_ROOTMGR_ROOFITUTILS_IPP */
