#include "EventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "Run.hh"

//Event means that one neutron was created and interacts with diaomd


void MyEventAction::BeginOfEventAction(const G4Event*){

    //reset energy to calc for new neutron
    MyRun* runData = static_cast<MyRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    runData->UpdateGlobalTime(fTau);
}


void MyEventAction::EndOfEventAction(const G4Event*){

    //record energy if chared particles were created
    MyRun* runData = static_cast<MyRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    runData->FillAndReset();

    
}
