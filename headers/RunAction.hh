#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <vector>
#include <ctime>
#include <fstream>

#include "Parameters.hh" 



class MyRunAction : public G4UserRunAction{
public:
    MyRunAction() = default;
    ~MyRunAction() = default;

    virtual G4Run* GenerateRun();

    void DisplayProgress(G4int);
    void PrintEventInform(MyMainData* data);
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

private:
    G4String fFileName = "../../data/detector_data";
    //G4String fFileName;
    G4String GlobalFileName = "../../data/detector_data";

    std::time_t current_time;

    ///Сюда будем записывать колическово смоделированных частиц
    G4int eventsNumber;
};

#endif

