#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "Run.hh"
#include "Parameters.hh"
#include "G4ParticleTable.hh"


MySteppingAction::MySteppingAction(MyDetectorConstruction* detConstruction)  : fDetConstruction(detConstruction){
}

// Collect energy and track length step by step
void MySteppingAction::UserSteppingAction(const G4Step* step){
    G4String name = step->GetTrack()->GetDefinition()->GetParticleName();
    G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
    //collect inform
    if(name == "proton"){
        
        // get volume of the current step
        const G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
        const G4VPhysicalVolume* fDetVolume = fDetConstruction->GetDetector();
    
        //check detector volume
        if (volume != fDetVolume){
            return;
        }

        //parameters
        G4double bornTime = step->GetPreStepPoint()->GetGlobalTime();
        G4double FulEnergy =step->GetPreStepPoint()->GetKineticEnergy(); //step->GetTotalEnergyDeposit();
        G4int FulEnergy = step->GetTrack()->GetTrackID(); //step->GetTotalEnergyDeposit();
        
        //step->GetTrack()->SetTrackStatus(fStopAndKill);
        
        //if(energy <= 0.1){
        //    return;
        //}
        MyRun* runData = static_cast<MyRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());

        runData->AddSecondary(FulEnergy, name, bornTime);//записываем энергию оставленную в чувствительной части  
        
        //kill
    }
}
