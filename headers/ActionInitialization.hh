#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "construction.hh"
#include "RunAction.hh"
#include "Parameters.hh" 



class ActionInitialization : public G4VUserActionInitialization {
    public:
    ActionInitialization(MyDetectorConstruction* DetectorVolume, G4String fileName);
    ~ActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;

private:
    G4String fFileName;
    std::vector<std::vector<MyMainData*>*> *fdata = nullptr;
    MyDetectorConstruction* fDetVolume = nullptr;
};




#endif