#include "ActionInitialization.hh"

#include "generator.hh"

#include "EventAction.hh"
#include "SteppingAction.hh"



ActionInitialization::ActionInitialization(MyDetectorConstruction* Det, G4String fileName)
{
    fDetVolume = Det;
    fdata = new std::vector<std::vector<MyMainData*>*>();
    fFileName = fileName;
}

ActionInitialization::~ActionInitialization(){
    size_t size = fdata->size();
    for(int i = 0; i < size; i++){
        fdata->at(i)->clear();
    }
    fdata->clear();
}

void ActionInitialization::Build() const {
    MyPrimaryGenerator *generator = new MyPrimaryGenerator(fDetVolume);
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction(fdata);
    SetUserAction(runAction);

    MyEventAction *eventAction = new MyEventAction(); 
    SetUserAction(eventAction);

    SetUserAction(new MySteppingAction(fDetVolume));

}

void ActionInitialization::BuildForMaster() const {	
    MyRunAction* runAction = new MyRunAction(fdata);
    SetUserAction(runAction);	
}	
