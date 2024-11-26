
#include <iostream>


#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

////////////////////////
#include "Construction.hh"
#include "ActionInitialization.hh"

#include "G4VPhysicalVolume.hh"


////////////////////////
#include "QGSP_BIC_HP.hh"
////////////////////////



//Is visual working
int Vis = 0;

//new coments to git 
//1e9 - DT -1 
//2.5e8 - DT -2
//3.89e5
//1.11e5

G4double flux = 1e6 / s;
G4double tau = 0.1 * s;
G4int N = (G4int)(flux * tau);

int main(int argc,char** argv){
    //Random ivents
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(int(time(NULL)));
    //

    //
    //Construct	the	run	manager	
    #ifdef G4MULTITHREADED
        G4MTRunManager* runManager = new G4MTRunManager;
        runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores() - 1);
    #else
        G4RunManager* runManager = new G4RunManager;
    #endif

    
    //phys
    /////////////////////////////////////
    G4VModularPhysicsList* physicsList = new QGSP_BIC_HP;
    runManager->SetUserInitialization(physicsList);
    /////////////////////////////////////

    //detector
    /////////////////////////////////////
    MyDetectorConstruction* detConstruction = new MyDetectorConstruction();
    runManager->SetUserInitialization(detConstruction);
    /////////////////////////////////////

    //actionInit
    /////////////////////////////////////
    runManager->SetUserInitialization(new ActionInitialization(detConstruction));
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
    //UImanager->ApplyCommand("/process/had/particle_hp/use_NRESP71_model true");

    if(ui){
        UImanager->ApplyCommand("control/execute ../vis.mac");
        ui->SessionStart();
        
    }else{
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/run/beamOn " + std::to_string(N));
    }
    //////////////////////////
    delete runManager;
    
    return 0;
}
