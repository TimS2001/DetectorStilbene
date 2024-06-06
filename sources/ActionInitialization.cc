#include "ActionInitialization.hh"

#include "generator.hh"

#include "EventAction.hh"
#include "SteppingAction.hh"



ActionInitialization::ActionInitialization(MyDetectorConstruction* Det, G4double tau)//, G4String fileName)
{
    fDetVolume = Det;
    fdata = new std::vector<std::vector<MyMainData*>*>();
    fTau = tau;
}


void ActionInitialization::Build() const {
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(fDetVolume);
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction(fdata);
    SetUserAction(runAction);

    MyEventAction *eventAction = new MyEventAction(fTau); 
    SetUserAction(eventAction);

    SetUserAction(new MySteppingAction(fDetVolume));

}

void ActionInitialization::BuildForMaster() const {	
    MyRunAction* runAction = new MyRunAction(fdata);
    SetUserAction(runAction);	
}	