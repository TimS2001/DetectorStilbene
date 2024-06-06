#include "generator.hh"


#include <cstdlib>
#include <ctime>

#include "Randomize.hh"

#include "G4ParticleTable.hh"


const G4double massD = 2.;
const G4double massT = 3.;
const G4double massAlfa = 4.;

//simple interection (only Kolumb)
//const G4double muD = 1. - 1./ 3. * (massD/massAlfa) * (massD/massAlfa);
const G4double muT = 0.5;//1. - 1./ 3. * (massT/massAlfa) * (massD/massAlfa);


MyPrimaryGenerator::MyPrimaryGenerator(MyDetectorConstruction* DetConstr) : fDetConstr(DetConstr){
    G4int am_particle = 1;
    nParticleGun  = new G4ParticleGun(am_particle);
    //////////////////////////////////

    //////////////////////////////////
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "neutron";
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    step = 0;
    //////////////////////////////////

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
    nParticleGun->SetParticleEnergy(RandEnergy());
    nParticleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector MyPrimaryGenerator::StartPosition(){
    //Get scales of detector
    const G4ThreeVector Detector = fDetConstr->GetScalesDetector();

    G4double size = 1.;

    //randomize position at x and y
    G4double x0 = size * Detector[0] * (G4UniformRand()-0.5);
    G4double y0 = size * Detector[1] * (G4UniformRand()-0.5);
    G4double z0 = 0.;
    return G4ThreeVector(x0, y0, z0);
}

G4ThreeVector MyPrimaryGenerator::MomDirection(G4ThreeVector partPosition){
   
    G4double x0 = 0.;
    G4double y0 = 0.;
    G4double z0 = 1.;
    return G4ThreeVector(x0, y0, z0);
}


G4double MyPrimaryGenerator::RandEnergy(){
    return G4RandGauss::shoot() * sigma_n + Energy_neutron;
}