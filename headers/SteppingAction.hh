#ifndef STEPPINGACTION_hh
#define STEPPINGACTION_hh

#include "G4UserSteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "construction.hh"

class MySteppingAction : public G4UserSteppingAction{
public:
    MySteppingAction(MyDetectorConstruction* detConstruction);
    ~MySteppingAction() = default;

    void UserSteppingAction(const G4Step* step);

private:
    MyDetectorConstruction* fDetConstruction = nullptr;
};

#endif