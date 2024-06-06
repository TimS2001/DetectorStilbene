#ifndef PARAMETERS_HH
#define PARAMETERS_HH

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


class MySecondaryParticlesData{
    public:
    MySecondaryParticlesData(G4double Energy,G4double BornTime, G4String Name){
        fEnergy = Energy;
        fBornTime = BornTime;
        fName = Name;
    }

    G4double GetEnergy(){
        return fEnergy;
    }

    G4double GetBornTime(){
        return fBornTime;
    }

    G4String GetName(){
        return fName;
    }

    private:
    G4double fEnergy = 0;
    G4double fBornTime = 0;
    G4String fName = "";
};



class MyMainData{
    public:
    MyMainData(G4String Name, G4double BornTime){
        fName = Name;
        fBornTime = BornTime;
        particles = new std::vector<MySecondaryParticlesData*>();
    }
    ~MyMainData(){
        if(particles != nullptr){
            particles->clear();
        }
    }
    void Add(MySecondaryParticlesData* partData){
        particles->push_back(partData);
    }
    G4double GetBornTime(){
        return fBornTime;
    }
    std::vector<MySecondaryParticlesData*>* GetParticles(){
        return particles;
    }

    private:
    std::vector<MySecondaryParticlesData*>* particles= nullptr;
    G4double fBornTime = 0;
    G4String fName = "";
};

#endif