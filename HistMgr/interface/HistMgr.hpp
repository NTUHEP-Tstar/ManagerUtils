/*******************************************************************************
 *
 *  Filename    : HistMgr
 *  Description : Class for Histogram management, uses Named class unque ID
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#ifndef MANAGERUTILS_HISTMGR_HISTMGR_HPP
#define MANAGERUTILS_HISTMGR_HISTMGR_HPP

#include <string>

class HistMgr
{
public:
   HistMgr ( const std::string& );
   virtual ~HistMgr ();

private:
   /* data */

};

#endif /* end of include guard: MANAGERUTILS_HISTMGR_HISTMGR_HPP */
