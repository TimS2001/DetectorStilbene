#ifndef PRINT_HH
#define PRINT_HH

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "Parameters.hh" 


G4String MyPrintInit(){
    G4String str;
    str = "EventTime\t";
    str += "Type\t";
    str += "Energy_MeV\t";
    str += "Time_ns\n";
    return str;
}

G4String MyPrintGetStr(MyParticleData* Secondary, G4int eventID){
    G4int EventTime = eventID;
    G4String Type = Secondary->GetName();
    G4double Energy_MeV = Secondary->GetEnergy();
    G4double Time = Secondary->GetTime();
    Energy_MeV = (Energy_MeV / MeV * 1000) / 1000.;
    Time = (Time / ns * 1000) / 1000.;
    G4String str = "";

    str += (std::to_string(EventTime) + '\t');
    str += (Type + '\t');
    str += (std::to_string(Energy_MeV) + '\t');
    str += (std::to_string(Time) + '\n');
    return str;
}



#endif