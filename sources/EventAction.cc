#include "EventAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "Run.hh"

#include "RunAction.hh"
#include "Parameters.hh" 

//Event means that one neutron has been created and interacted

void MyEventAction::BeginOfEventAction(const G4Event*){
    //reset energy to calc to new neutron
    MyRun* runData = static_cast<MyRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    runData->UpdateEvent();

}


void MyEventAction::EndOfEventAction(const G4Event* event){
    //record data in end of neutron`s interection
    MyRun* runData = static_cast<MyRun*> (G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    MyMainData* data = runData->GetData();

    

    MyRunAction* runAction = (MyRunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
    int eventID = event->GetEventID();
    if (eventID > 99){
        runAction->DisplayProgress(eventID + 1);
    }

    if(data != nullptr){
        runAction->PrintEventInform(data);
    }
    
    runData->Reset();
}
