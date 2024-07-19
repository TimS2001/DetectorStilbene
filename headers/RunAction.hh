
#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"

#include <vector>
#include <ctime>
#include "Parameters.hh" 



class MyRunAction : public G4UserRunAction{
public:
    MyRunAction(std::vector<std::vector<MyMainData*>*>* data) : fdata(data){
        //fFileName = fileName;
    }
    ~MyRunAction() = default;

    virtual G4Run* GenerateRun();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

private:
    //G4string fFileName ="C:/Users/Working/Desktop/Detectors/DetectorStilbene/data/detector_data.txt";
    G4String fFileName = "../../data/detector_data.txt";
    
    //[cores][events][parameters]
    std::vector<std::vector<MyMainData*>*> *fdata = nullptr;

    //[events][parameters]
    std::vector<MyMainData*> *Ddata = new std::vector<MyMainData*>();
    
    std::time_t current_time;
    
    //MyLightConvertor* Convertor = nullptr;
};

#endif

