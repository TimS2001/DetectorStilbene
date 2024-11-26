#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


class MyEventAction : public G4UserEventAction{
public:
  MyEventAction() = default;
  ~MyEventAction() = default;

  void BeginOfEventAction(const G4Event* event) override;
  void EndOfEventAction(const G4Event* event) override;
private:
  int fPercentNow = 1;
};

#endif


