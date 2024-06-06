#include "generator.hh"
#include "EnergyDistribution.hh"

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Randomize.hh"

#include "G4ParticleTable.hh"


#define PI 3.14159265



MyPrimaryGenerator::MyPrimaryGenerator(MyDetectorConstruction* DetConstruction) : fDetConstruction(DetConstruction){
    G4int am_particle = 1;
    nParticleGun  = new G4ParticleGun(am_particle);
    //////////////////////////////////

    //////////////////////////////////
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "neutron";//"neutron"; //"gamma";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    
    if(is_DT){
        sigma *= C_DT;
        Energy_neutron = Energy_DT;
    }else{
        sigma *= C_DD;
        Energy_neutron = Energy_DD;
    }
    //////////////////////////////////
    REnergy = new MyEnergyDistribution;

    //////////////////////////////////
    nParticleGun->SetParticleEnergy(Energy_neutron);
    nParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator(){
    delete nParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent){
    G4ThreeVector StartPos = StartPosition();
    nParticleGun->SetParticlePosition(StartPos);
    nParticleGun->SetParticleMomentumDirection(MomDirection(StartPos));

    if(is_MySpect){
        nParticleGun->SetParticleEnergy(REnergy->GetEnergyRand());
    }else{
        nParticleGun->SetParticleEnergy(RandEnergy());
    }
    
    nParticleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector MyPrimaryGenerator::StartPosition(){
    /*
    //Get scales of detector
    //(X,Y,Z)
    const G4ThreeVector DetectorPos = fDetConstruction->GetPositionDetector();

    //(R,Z,-)
    const G4ThreeVector DetectorSca = fDetConstruction->GetScalesDetector();


    G4double x0 = DetectorPos[0];
    G4double y0 = DetectorPos[1];
    G4double z0 = DetectorPos[2]-  DetectorSca[1] * 0.5 - distance;
    */
    const G4ThreeVector DetectorSca = fDetConstruction->GetScalesDetector();

    G4double size = 1.0;

    //randomize position at x and y
    G4double R0 = size * DetectorSca[0] * G4UniformRand();
    G4double phi = 2. * PI * G4UniformRand();
    G4double x0 = R0 * sin(phi);
    G4double y0 = R0 * cos(phi);
    G4double z0 = -10.* cm;
    return G4ThreeVector(x0, y0, z0);
    return G4ThreeVector(x0, y0, z0);
}

G4ThreeVector MyPrimaryGenerator::MomDirection(G4ThreeVector partPosition){
    /*
    //Get scales of detector
    //(X,Y,Z)
    const G4ThreeVector DetectorPos = fDetConstruction->GetPositionDetector();

    //(R,Z,-)
    const G4ThreeVector DetectorSca = fDetConstruction->GetScalesDetector();


    //Thetta angle
    G4double Thetta_max = asin(DetectorSca[0] / distance);
    //G4cout << DetectorSca[0];
    G4double Phi_max = 2. * PI;



    //randomize position at Thetta and Phu
    G4double phi = (G4UniformRand()) * Phi_max;
    G4double Thetta = (G4UniformRand()) * Thetta_max;

    G4double x0 = sin(Thetta) * cos(phi);
    G4double y0 = sin(Thetta) * sin(phi);
    G4double z0 = cos(Thetta);
    */
    return G4ThreeVector(0, 0, 1.);
    //return G4ThreeVector(x0, y0, z0);
}

G4double MyPrimaryGenerator::RandEnergy(){
    //G4UniformRand()
    return G4RandGauss::shoot() * sigma + Energy_neutron;
   
    //if(Energy_neutron > 14.501){
    //    G4cout << "err";
    //}
    //return Energy_neutron;
}