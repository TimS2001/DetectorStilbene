#ifndef PARAMETERS_HH
#define PARAMETERS_HH

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


class MyParticleData{ // data at one particle
    public:
    MyParticleData(G4double Energy, G4String Name, G4double Time){
        fEnergy = Energy;
        fName = Name;
        fTime = Time;
    }

    G4double GetEnergy(){
        return fEnergy;
    }

    G4String GetName(){
        return fName;
    }

    G4double GetTime(){
        return fTime;
    }

    private:
    G4double fTime = 0;
    G4double fEnergy = 0;
    G4String fName = "";
};



class MyMainData{ // class that have data about all particles at one event (by one neutron)
    public:
    MyMainData(G4int numberOfEvent){
        fnumberOfEvent = numberOfEvent;
        particles = new std::vector<MyParticleData*>();
    }
    ~MyMainData(){
        if(particles != nullptr){
            particles->clear();
            delete particles;
            particles = nullptr;
            fnumberOfEvent = 0;
        }
    }
    void Add(MyParticleData* partData){
        particles->push_back(partData);
    }
    G4int GetNumberOfEvent(){
        return fnumberOfEvent;
    }
    std::vector<MyParticleData*>* GetParticles(){
        return particles;
    }

    private:
    std::vector<MyParticleData*>* particles= nullptr;
    G4int fnumberOfEvent = 0;
};

#endif