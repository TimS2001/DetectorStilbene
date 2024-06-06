#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"


#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>

#include "construction.hh"


class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction{
    public:
    MyPrimaryGenerator(MyDetectorConstruction*);
    ~MyPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event*);

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return nParticleGun; }

    private:
    G4double RandEnergy();
    G4ThreeVector StartPosition();
    G4ThreeVector MomDirection(G4ThreeVector);

    
    
    //for thermal ions
    const G4double Energy_neutron = (14.1 * MeV);
    //const G4double Energy_alfa = 3.54; // * MeV;
    const G4double C_DT_n = 75.1; // sqrt(kEv)
    //const G4double C_DT_alf = 75.3; // sqrt(kEv)
    /////////////////////////////////

    const G4double E0 = 40.; // keV
    const G4double sigma_n = sqrt(E0)*C_DT_n / 1000. * MeV;
   
    
    /////////////////////////////////


    MyDetectorConstruction* fDetConstr;
    G4ParticleGun* nParticleGun = nullptr;
    G4int step;
};

#endif