#ifndef ENERGYDISTRIBUTION_HH
#define ENERGYDISTRIBUTION_HH

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <cmath>
#include <vector>
#include <string>

class MyEnergyDistribution{
    public:
    MyEnergyDistribution();
    ~MyEnergyDistribution();

    G4double GetEnergyRand();


    private:
    int fileSize;
    std::vector<double> Energy;
    std::vector<double> Probability; //[0, 1]
    std::string name = "../../sys_data/EnergyDependanceDD/res_13_keV.txt";
    //"../../sys_data/EnergyDependanceDT/energy_histogram_DT_1.txt";
    //"../../sys_data/EnergyDependanceDD/MyEnergy.txt";
    //"../../data/EnergyDependanceDD/res_13_keV.txt"
    //"../../data/EnergyDependanceDT/energy_histogram_DT_1.txt"
};
#endif