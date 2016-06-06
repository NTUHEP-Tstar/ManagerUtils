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

class Named // Only virtual for the sake of Inheritance Do not overload
{
public:

   Named( const std::string& );
   virtual ~Named ();

   // Basic access functions
   virtual const std::string& Name() const { return _name; }
   virtual const std::string& LatexName() const { return _latex_name; }
   virtual std::string RootTitle() const;

   // Setting functions
   virtual void SetLatexName( const std::string& x );

protected:
   static std::string ConvertToRootFlavour( const std::string& );
   static std::string ConvertToLatexFlavour( const std::string& );

private:
   const std::string _name;
   std::string _latex_name;
};

}

#endif /* end of include guard: MANAGERUTILS_BASECLASS_NAMED_HPP */
