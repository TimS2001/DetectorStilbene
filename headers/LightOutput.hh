#ifndef LIGHTOUTPUT_HH
#define LIGHTOUTPUT_HH

#include <vector>
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <string>

class MyLightConvertor{
    public:
    MyLightConvertor();
    ~MyLightConvertor();

    G4double GetLight(G4double Energy);


    private:
    int fileSize = 56;
    std::vector<double> Energy;
    std::vector<double> K;
    std::vector<double> b;
    std::string name = "../../data/L(E).txt";
};

#endif