#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"
#include "globals.hh"
#include <fstream>

#include <vector>
#include "Parameters.hh" 

/// The data are collected step by step in SteppingAction, and
/// the accumulated values are filled in file
/// event by event in EventAction.



class MyRun : public G4Run{
public:
  MyRun() = default;
  ~MyRun(){
    assert(fMainParticleData != NULL);
    delete fMainParticleData;
  };
  

  //add event to events data (secondary particles data)
  void AddSecondary(G4double Energy, G4String Name, G4double Time){   
    MyParticleData* Secondary = new MyParticleData(Energy, Name, Time);
    fMainParticleData->Add(Secondary);
    return;
  }

  MyMainData* GetData(){
    return fMainParticleData;
  }
  
  void Reset(){
    if(fMainParticleData != nullptr){
      G4MUTEXLOCK(&mutex );  
      fMainParticleData->~MyMainData();  
      fMainParticleData = nullptr;
      G4MUTEXUNLOCK(&mutex );
    }
  }

  //global time - event when neutron was borned
  void UpdateEvent(){
    fTimes += 1;
    if(fTimes > MaxTime){
      fTimes -= MaxTime;
    }
    if(fMainParticleData != nullptr){
      Reset();
    }
    fMainParticleData = new MyMainData(fTimes);
  }


private:
  G4double MaxTime = 10000; //constant just to good writing
  G4int fTimes = 0.;
  G4Mutex mutex = G4MUTEX_INITIALIZER;
  MyMainData* fMainParticleData = nullptr;
};

#endif
