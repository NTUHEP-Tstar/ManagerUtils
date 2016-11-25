/*******************************************************************************
*
*  Filename    : MCHelper.hpp
*  Description : Helper functions and variables for MC truth matching
*  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
*
*******************************************************************************/
#ifndef MANAGERUTILS_PHYSUTILS_MCHELPER_HPP
#define MANAGERUTILS_PHYSUTILS_MCHELPER_HPP

/*******************************************************************************
*   PDG ID definitions:
*   https://twiki.cern.ch/twiki/bin/view/Main/PdgId
*******************************************************************************/
#define DOWN_QUARK_ID     1
#define UP_QUARK_ID       2
#define STRANGE_QUARK_ID  3
#define CHARM_QUARK_ID    4
#define BOTTOM_QUARK_ID   5
#define TOP_QUARK_ID      6

#define ELEC_ID      11
#define ELECNU_ID    12
#define MUON_ID      13
#define MUONNEU_ID   14
#define TAU_ID       15
#define TAUNEU_ID    16

#define GLUON_ID       21
#define GAMMA_ID       22
#define Z_BOSON_ID     23
#define W_BOSON_ID     24
#define HIGGS_BOSON_ID 25

/*******************************************************************************
*   Gen level topology transvering helper functions
*******************************************************************************/
#include "DataFormats/Candidate/interface/Candidate.h"

/*******************************************************************************
*   * GetDirectMother( x , F ),
*   For an input particle x, it will trasverse the topology towards the parent
*   side, until
*     1. the parent particle has the target flavour F, in which case it returns
*        the pointer to the parent particle. Note that the absolue value will
*        be taken for the for the flavour.
*     2. The parent particle has a flavour different to x, in which case a null
*        pointer is return.
*   This function help find direct parent of a particle while avoid the
*   possibility of final state radiations,
*
*   Ex: for the topology
*   F->(x+g)->(x'+gg)->(x''+ggg)
*   The three function calls
*     - GetDirectMother( x, F )
*     - GetDirectMother( x', F )
*     - GetDirectMother( x'', F )
*   should all return the same pointer.
*
*   Topologies in MiniAOD also have some times have the strange topologies like:
*   x -> x' -> x'' which could be avoided by this function.
*******************************************************************************/
const reco::Candidate* GetDirectMother( const reco::Candidate*, int );

/*******************************************************************************
*   * GetDaughter( x, F)
*   Return the pointer to the daughter particle of x whose flavour is F.
*
*   For the decay x->F , and the strange single object decay F->F'->F'' ...
*   this function will return the last of the decay chain (F'') in our case.
*******************************************************************************/
const reco::Candidate* GetDaughter( const reco::Candidate*, int );




#endif /* end of include guard: MANAGERUTILS_PHYSUTILS_MCHELPER_HPP */
