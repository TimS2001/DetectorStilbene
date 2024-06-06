#include "EnergyDistribution.hh"
#include "Randomize.hh"

#include <iostream>
#include <fstream>

MyEnergyDistribution::MyEnergyDistribution(){
    std::string line;
    std::ifstream in(name);
    if (in.is_open()){
        //while (std::getline(in, line)){
        in >> fileSize;
        for(int i = 0; i < fileSize; i++){
            double fEnergy;
            long double fProb;
            in >> fEnergy >> fProb;
            Energy.push_back(fEnergy);
            Probability.push_back(fProb); 
             
        }
    }
    in.close();
}

MyEnergyDistribution::~MyEnergyDistribution(){
    Energy.clear();
    Probability.clear();
}

G4double MyEnergyDistribution::GetEnergyRand(){
    double x = G4UniformRand();
    int i = 0;
    while(Probability[i] < x){
        i++;
    }
    double k = (Energy[i] - Energy[i - 1])/(Probability[i] - Probability[i - 1]);
    double fEnergy = k * (x - Probability[i]) + Energy[i];
    return fEnergy;
}
