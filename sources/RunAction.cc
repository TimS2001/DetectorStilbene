#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <fstream>


#include "Run.hh"



G4double light(G4double x){
    G4double Light = 0.;
    //G4double B = 0.188883;
    
    //G4double E0 = 2.45;
    //G4double B = E0 / (pow(E0, 1.5) * exp(0.016 * pow(E0,-1.5) - 0.021 * pow(E0, 0.9)));
    //if(x > 0.1){
        //Light = B * pow(x, 1.5) * exp(0.016 * pow(x,-1.5) - 0.021 * pow(x, 0.9));
        //Light = 1./sqrt(2.45) * pow(x, 1.5);//DD
        //Light = 1./sqrt(14.1) * pow(x, 1.5);//DT

        //G4cout << Light << '\n';
    //}
    Light = pow(x, 1.5);
    return Light;
}

void MyRunAction::BeginOfRunAction(const G4Run*){
    if(IsMaster())
        time(&current_time);
}


void MyRunAction::EndOfRunAction(const G4Run*){


        //add data from threads to global data
        if(Ddata->size() != 0){
            fdata->push_back(Ddata);
        }

        if(IsMaster()){
            ////////////////////////////
            //write time of calculatrion
            std::time_t tmp_time = time(NULL);
            time(&tmp_time);
            tmp_time -= current_time;

            int hours = int(tmp_time / 3600);
            int minutes = int((tmp_time % 3600) / 60);
            int seconds = int((tmp_time % 3600) % 60);
            std::cout << '\n' << hours << " hours, " << minutes << " minutes, " << seconds << "seconds\n";   
            ////////////////////////////
            
            ////////////////////////////
            //write data to file
            std::ofstream file;
            file.open(fFileName);
            if(file.is_open() == 0){
                std::cout << "err to open file" << '\n';
            }    
            //file.open(fFileName);
            file << "Energy_MeV" << '\t' << "BornTime_ns" << '\t' << "MainTime_ns" << '\t' << "Type" << '\n';
            //Convertor = new MyLightConvertor;
            
            size_t threads = fdata->size();//number of threads
            G4double lastTime = 0.;//should change NeutronBornTime for Next thread
            for(int i = 0; i < threads; i++){
                
                const std::vector<MyMainData*>* MainParticles = fdata->at(i);//collection of neutrons in current thread
                size_t events = MainParticles->size();//size of neutrons in current thread
                
                for(int j = 0; j < events; j++){
                    
                    MyMainData* MainParticle = MainParticles->at(j);
                
                    G4double mainBornTime = MainParticle->GetBornTime();
                    
                    std::vector<MySecondaryParticlesData*>* Secondaries = MainParticle->GetParticles();
                    size_t SecondariesSize = Secondaries->size();
                    for(int m = int(SecondariesSize) - 1; m >= 0; m--){
                        MySecondaryParticlesData* Secondary = Secondaries->at(m);
                    
                        G4double energyDeposittion = Secondary->GetEnergy();
                        G4double secondaryBornTime = Secondary->GetBornTime();
                        G4String Name = Secondary->GetName();


                        file << round(energyDeposittion / MeV * 1000) / 1000. << '\t';
                        file << round(secondaryBornTime * 10. / ns) / 10. << '\t';
                        file << round(mainBornTime * 10. / ns) / 10. << '\t'; 
                        file << Name << '\n';
                        //file << light(tmp[j]) << "\n";
                    }
                
                }
                if(events != 0){
                    lastTime = MainParticles->at(events - 1)->GetBornTime();//write time of last event
                }
            }

            file.close();
    }
}

G4Run* MyRunAction::GenerateRun(){
    return new MyRun(Ddata);
}