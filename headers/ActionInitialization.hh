#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "construction.hh"
#include "RunAction.hh"
#include "Parameters.hh" 



class ActionInitialization : public G4VUserActionInitialization {
    public:
    ActionInitialization(MyDetectorConstruction* Detector_Volume);
    ~ActionInitialization(){
    }

    virtual void Build() const;
    virtual void BuildForMaster() const;
private:
    MyDetectorConstruction* fDetVolume = nullptr; //
};




#endif