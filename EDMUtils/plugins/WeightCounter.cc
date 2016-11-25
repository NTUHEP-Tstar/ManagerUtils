/*******************************************************************************
 *
 *  Filename    : WeightCounter.cc
 *  Description : This stores information per event
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
 *  Reference:
 *       CMSSW EventCountProducer Class
 *
*******************************************************************************/
// system include files
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "ManagerUtils/EDMUtils/interface/Counter.hpp"

//------------------------------------------------------------------------------
//   Class Definition
//------------------------------------------------------------------------------
class WeightCounter : public edm::one::EDProducer<edm::one::WatchRuns,edm::EndRunProducer>
{
public:
   explicit WeightCounter(const edm::ParameterSet&);
   ~WeightCounter();

private:
   virtual void produce(edm::Event &, const edm::EventSetup&) override;
   virtual void beginRun( const edm::Run&,const edm::EventSetup&) override;
   virtual void endRun  ( const edm::Run&,const edm::EventSetup&) override;
   virtual void endRunProduce(edm::Run& , const edm::EventSetup&) override;

   const edm::EDGetToken  _lhesrc;
   edm::Handle<LHEEventProduct> _lheHandle;
   double                       _eventCount;
};
using namespace edm;
using namespace std;

//------------------------------------------------------------------------------
//   Constructor and destructor
//------------------------------------------------------------------------------
WeightCounter::WeightCounter(const edm::ParameterSet& iConfig):
   _lhesrc( consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("lhesrc")) )
{
   produces<mgr::Counter, edm::InRun>("EventsCount");
}

WeightCounter::~WeightCounter(){}

//------------------------------------------------------------------------------
//   Main Control flow
//------------------------------------------------------------------------------
void WeightCounter::beginRun( const edm::Run& , const edm::EventSetup& )
{
   _eventCount = 0;
}

void WeightCounter::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   iEvent.getByToken( _lhesrc , _lheHandle );
   if( _lheHandle.isValid() ){
      _eventCount += _lheHandle->hepeup().XWGTUP ;
   } else {
      _eventCount += 1;
   }
}

void WeightCounter::endRun( const edm::Run&, const edm::EventSetup& )
{}

void WeightCounter::endRunProduce( edm::Run& iRun , const EventSetup& iSetup)
{
   auto_ptr<mgr::Counter> ptr( new mgr::Counter(_eventCount) );
   iRun.put( ptr, "" );
}



DEFINE_FWK_MODULE(WeightCounter);
