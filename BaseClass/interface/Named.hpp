/*******************************************************************************
*
*  Filename    : Named.hpp
*  Description : Base Class with std::string as ID and latex title
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_BASECLASS_NAMED_HPP
#define MANAGERUTILS_BASECLASS_NAMED_HPP

#include <string>

namespace mgr
{

class Named// Only virtual for the sake of Inheritance Do not overload
{
public:
   Named( const std::string& );
   virtual ~Named ();

   // Basic access functions
   virtual const std::string& Name() const { return _name; }

   virtual const std::string& LatexName() const { return _latexname; }
   virtual const std::string& RootName() const { return _rootname; }

   // Setting functions
   virtual void SetLatexName( const std::string& x );
   virtual void SetRootName( const std::string& x );

private:
   const std::string _name;
   std::string _latexname;
   std::string _rootname;
};

}

#endif/* end of include guard: MANAGERUTILS_BASECLASS_NAMED_HPP */
