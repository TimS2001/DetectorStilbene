
#include <iostream>


#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

////////////////////////
#include "construction.hh"
#include "ActionInitialization.hh"

#include "G4VPhysicalVolume.hh"


////////////////////////
#include "QGSP_BERT_HP.hh"
////////////////////////



//Is visual working
int Vis = 1;

//new coments to git 


int main(int argc,char** argv){
    //Random ivents
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));
    //

    //
    //Construct	the	run	manager	
    #ifdef G4MULTITHREADED
        G4MTRunManager* runManager = new G4MTRunManager;
        runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores()-1);
    #else
        G4RunManager* runManager = new G4RunManager;
    #endif

    
    //phys
    /////////////////////////////////////
    G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
    runManager->SetUserInitialization(physicsList);
    /////////////////////////////////////

    //detector
    /////////////////////////////////////
    MyDetectorConstruction* detConstruction = new MyDetectorConstruction();
    runManager->SetUserInitialization(detConstruction);
    /////////////////////////////////////

    //actionInit
    /////////////////////////////////////
    runManager->SetUserInitialization(new ActionInitialization(detConstruction, 0.1));
    /////////////////////////////////////


    
    
    
    
    /////////////////////////////////////
    G4UIExecutive* ui = 0;
    if(Vis == 1){
        ui = new G4UIExecutive(argc, argv);
    }

    //visMan
    /////////////////////////////////////
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    /////////////////////////////////////

    
    
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    runManager->Initialize();
    UImanager->ApplyCommand("/process/had/particle_hp/use_NRESP71_model true");

    if(ui){
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        
    }else{
        /*
        UImanager->ApplyCommand("/control/execute run.mac");
        */
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/run/beamOn 100000");
    }
    //////////////////////////
    delete runManager;
    
    return 0;
}
