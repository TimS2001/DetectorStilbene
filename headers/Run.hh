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
  MyRun(std::vector<MyMainData*> *data) : fdata{data} {}
  ~MyRun() = default;
  
  //add event to events data (protons data)
  int AddSecondary(G4double Energy, G4double SecondaryBornTime, G4String Name){
    G4double RealSecondaryBornTime = SecondaryBornTime - fZeroTimeInDet;
    
    if(MainParticle == nullptr){
      //std::cout << "error";
      return -1;
    }
    
    MySecondaryParticlesData* Secondary = new MySecondaryParticlesData(Energy, RealSecondaryBornTime, Name);
    MainParticle->Add(Secondary);
    return 0;
  }

  //add events to data file 
  void FillAndReset(){
    fZeroTimeInDet = 0.;
    
    if(MainParticle == nullptr){
      return;
    }
    size_t size = MainParticle->GetParticles()->size();
    if(size == 0){ 
        delete MainParticle;
        MainParticle = nullptr;
        return;
    }
    fdata->push_back(MainParticle);
    MainParticle = nullptr;
  }

  //localTime - event when neutron move on detector 
  void UpdateLocalTime(G4String Name, G4double ZeroTimeInDet){
    if(fZeroTimeInDet != 0){
      return;
    }
    MainParticle = new MyMainData(Name, fMainBornTime);
    fZeroTimeInDet = ZeroTimeInDet;
  }
  
  //global time - event when neutron was borned
  void UpdateGlobalTime(G4double neutronBornTime){
    fMainBornTime += neutronBornTime;
    if(fMainBornTime > MaxTime){
      fMainBornTime -= MaxTime;
    }
  }



private:
  G4double MaxTime = 50000. * ns;
  G4double fZeroTimeInDet = 0.;
  G4double fMainBornTime = 0.;
  MyMainData* MainParticle = nullptr;
  std::vector<MyMainData*>* fdata = nullptr;//data to write in file
};

#endif