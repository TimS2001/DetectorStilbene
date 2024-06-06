#include "LightOutput.hh"

#include <iostream>
#include <fstream>

MyLightConvertor::MyLightConvertor(){
    std::string line;
    std::ifstream in(name);
    if (in.is_open()){
        //while (std::getline(in, line)){
        for(int i = 0; i < fileSize; i++){
            double fEnergy;
            long double fK;
            long double fb;
            in >> fEnergy >> fK >> fb;
            Energy.push_back(fEnergy);
            K.push_back(fK);
            b.push_back(fb); 
            //std::cout << fEnergy << ' ' << fK << ' ' << fb << '\n';
        }
    }
    in.close();
}

MyLightConvertor::~MyLightConvertor(){
    Energy.clear();
    K.clear();
    b.clear();
}

G4double MyLightConvertor::GetLight(G4double E){
    int i = 0;
    while((Energy[i] <= E)&&(i < fileSize)){
        i++;
    }
    i--;

    return K[i] * E + b[i];
}
