#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "construction.hh"
#include "RunAction.hh"
#include "Parameters.hh" 



class ActionInitialization : public G4VUserActionInitialization {
    public:
    ActionInitialization(MyDetectorConstruction*, G4double);
    ~ActionInitialization(){
        size_t size = fdata->size();
        for(int i = 0; i < size; i++){
           fdata->at(i)->clear();
        }
        fdata->clear();
    }

    virtual void Build() const;
    virtual void BuildForMaster() const;
private:
    //vector cores[events[parameters]]
    //G4String fFileName;
    std::vector<std::vector<MyMainData*>*> *fdata = nullptr;
    MyDetectorConstruction* fDetVolume = nullptr;
    G4double fTau = 0.;
};




#endif