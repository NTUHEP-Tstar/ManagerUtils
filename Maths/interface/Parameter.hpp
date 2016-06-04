/*******************************************************************************
 *
 *  Filename    : Parameter.hh
 *  Description : Storage class for handling parameters
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Includes support for systematic and statistical uncertainties
 *
*******************************************************************************/
#ifndef MANAGERUTILS_MATHS_PARAMETER_HPP
#define MANAGERUTILS_MATHS_PARAMETER_HPP

#include <string>

class Parameter {
public:

   // Constructor, Desctructor and conversion :: See Parameter.cc
   Parameter();
   Parameter(
      const double central ,
      const double error_up ,
      const double error_down );
   Parameter( const Parameter& );

   virtual ~Parameter ();

   Parameter& operator=( const Parameter& );

   inline operator double() const{ return _centralValue; }

   // Basic access functions
   inline double CentralValue() const { return _centralValue; }
   inline double AbsUpperError() const { return _error_up; }
   inline double AbsLowerError() const { return _error_down; }
   inline double RelUpperError() const { return _error_up/_centralValue; }
   inline double RelLowerError() const { return _error_down/_centralValue; }
   inline double RelAvgError()   const { return (RelUpperError()+RelLowerError()) /2.; }

   // Error arithmatics :: See src/Parameter_Arithmatics.cc
   Parameter& operator+=( const Parameter& );
   Parameter& operator*=( const Parameter& );
   Parameter& operator*=( const double );
   Parameter operator+( const Parameter& ) const ;
   Parameter operator*( const Parameter& ) const ;
   Parameter operator*( const double )     const ;
   friend Parameter operator*( const double, const Parameter& );

   // Outputting :: See src.Parameter_Formatting.cc
   std::string LatexFormat( int = -1 ) const;
   std::string DataCardFormat() const;

private:
   double _centralValue;
   double _error_up;
   double _error_down;
};

#endif /* end of include guard: __PARAMETER_HH__ */
