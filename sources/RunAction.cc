#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


#include <string>     // для std::getline

#include "Run.hh"
#include "Print.hh"

void MyRunAction::BeginOfRunAction(const G4Run* aRun){
    //Сообщаем G4RunManager-у сохранить зерно для генератора случайных чисел
    //G4RunManager::GetRunManager()->SetRandomNumberStore(false);
    eventsNumber = aRun->GetNumberOfEventToBeProcessed();
    
    if(IsMaster()){
        time(&current_time);//fix null of calculation time
        //fFileName = GlobalFileName;// + std::to_string(aRun->GetRunID());
        
        // создание и открытие текстового файла
        G4int cores = G4Threading::G4GetNumberOfCores();
        std::ofstream file;
        G4String FileName; 
        for(int i = 0; i < cores; i++){
            FileName = fFileName + std::to_string(i) + ".txt";
            file.open(FileName, std::ofstream::out | std::ofstream::trunc);
            file.close();
        }
    }

}



void MyRunAction::DisplayProgress(G4int eventID){
    G4int prg_step = ( eventsNumber - eventsNumber%100 ) / 100; // 1% step size
    if (eventID%prg_step == 0) {                                // if +1% events processed
        G4int prg_cur = eventID / prg_step;                     // get current step number ( = N of % )
        G4cout << "Progress: " << prg_cur << "%" << G4endl;     // cout that stuff
    }
}

////////////////////////////
// //write data to file
void MyRunAction::PrintEventInform(MyMainData* data){
    if(data->GetParticles()->size() == 0){
        //data->~MyMainData();
        return;
    }

    G4int thrID = G4Threading::G4GetThreadId();
    G4String FileName = fFileName + std::to_string(thrID) + ".txt";
    std::ofstream file;
    file.open(FileName, std::ios::app);
    
    if(file.is_open() == 0){
        std::cout << "err to open file" << '\n';
    }  
    
    std::vector<MyParticleData*>* Secondaries = data->GetParticles();
    size_t SecondariesSize = Secondaries->size();
    G4int eventID = data->GetNumberOfEvent();

    for(int m = 0; m < int(SecondariesSize); m ++){
        MyParticleData* Secondary = Secondaries->at(m);
        G4String str = MyPrintGetStr(Secondary, eventID);
        file << str;
        
    }
    file.close();
    //Надеюсь здесь не будет ошибки
    //освобождаем в eventAction
    data->~MyMainData();
    data = nullptr;
}




void MyRunAction::EndOfRunAction(const G4Run*){
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
        //печать в главный файл
        std::ofstream Mainfile;
        G4String FileName = fFileName + ".txt"; //main file
        Mainfile.open(FileName);
        G4String str = MyPrintInit();
        Mainfile << str;
        
        
        G4int cores = G4Threading::G4GetNumberOfCores();
        for(int i = 0; i < cores; i++){
            FileName = fFileName + std::to_string(i) + ".txt";
            std::ifstream Localfile;
            Localfile.open(FileName);
            G4String LocalLine = "";
            while(std::getline(Localfile, LocalLine)){
                Mainfile << LocalLine << '\n';
            }
            Localfile.close();
            int status = remove(FileName);
        }
        

    }
}

G4Run* MyRunAction::GenerateRun(){
    return new MyRun();
}
