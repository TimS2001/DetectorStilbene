#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

//#include "G4RunManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

//Volume
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
//




class MyDetectorConstruction: public G4VUserDetectorConstruction{
    public:
        MyDetectorConstruction() = default;
        ~MyDetectorConstruction() = default;

        G4VPhysicalVolume* Construct();
        const G4VPhysicalVolume* GetDetector() const {return physDetector;}
        const G4ThreeVector GetScalesDetector() const {return scalesDetector;}
        const G4ThreeVector GetPositionDetector() const {return DetectorPosition;}

    private:
        virtual void ConstructSDandFild();
        G4LogicalVolume* CreateStilbeneDetector();
        G4LogicalVolume* CreateContainer1();
        G4LogicalVolume* CreateContainer2();
        G4LogicalVolume* CreateWorld();
        G4VPhysicalVolume* physDetector = nullptr;
        //void SetupDetectors();
    //////////////////

    //constants
    G4double l = 4 * cm;
    G4double M = 15 * l; //100. * cm;
    G4ThreeVector scalesWorld = G4ThreeVector(M / 2, M / 2, M); 
    G4double detIR = 0.*cm;        // cylinder inner radius
    G4double detOR = l / 2;        // cylinder outer radius
    G4double detZspan = l;      // cylinder length
    G4double contThick = 0.3*cm; // container thickness

    G4ThreeVector DetectorPosition = G4ThreeVector(0., 0., 10. * cm); 
    G4double Z = detZspan + 2 * contThick;
    G4double R = detOR + contThick;
    G4ThreeVector scalesDetector = G4ThreeVector(R, Z, 0.);
};




#endif