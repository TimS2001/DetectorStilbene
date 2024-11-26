#include "ActionInitialization.hh"

#include "generator.hh"

#include "EventAction.hh"
#include "SteppingAction.hh"



ActionInitialization::ActionInitialization(MyDetectorConstruction* Det){
    //fN = N;
    fDetVolume = Det;
}


void ActionInitialization::Build() const {
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(fDetVolume);
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);

    MyEventAction *eventAction = new MyEventAction(); 
    SetUserAction(eventAction);

    SetUserAction(new MySteppingAction(fDetVolume));

}

void ActionInitialization::BuildForMaster() const {	
    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
}	
