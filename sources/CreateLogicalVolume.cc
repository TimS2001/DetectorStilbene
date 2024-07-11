#include "Construction.hh"


#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

    
//корпус1
G4LogicalVolume* MyDetectorConstruction::CreateContainer1(){
    //
    G4NistManager *nist = G4NistManager::Instance();
    G4Material* containerMat = nist->FindOrBuildMaterial("G4_Al");
    //

    G4Tubs* solidDetContainer1 = new G4Tubs("ContainerSolid1", detOR, detOR + contThick, 0.5*(detZspan), 0. *deg, 360. *deg);
    
    return new G4LogicalVolume(solidDetContainer1, containerMat, "ContainerLogic1");

}

//корпус2
G4LogicalVolume* MyDetectorConstruction::CreateContainer2(){
    
    //
    G4NistManager *nist = G4NistManager::Instance();
    G4Material* containerMat = nist->FindOrBuildMaterial("G4_Al");
    //

    G4Tubs* solidDetContainer2 = new G4Tubs("ContainerSolid2", detIR, detOR + contThick, 0.5*(contThick), 0. *deg, 360. *deg);

    return new G4LogicalVolume(solidDetContainer2, containerMat, "ContainerLogic2");

}

//чувств объем
G4LogicalVolume* MyDetectorConstruction::CreateStilbeneDetector(){
    ///////////////////
    //Xylene definition
    //
    G4NistManager *nist = G4NistManager::Instance();
    G4Material* XyleneMat = nist->FindOrBuildMaterial("G4_XYLENE");
    //
    
    ////////////////////
    //Stlbene definition
    /*
    G4NistManager *nist = G4NistManager::Instance();
    G4Material* StlbeneMat = nist->FindOrBuildMaterial("G4_STILBENE");
    */
    
    ///////////////////
    //BC501A definition
    /*
    // define Carbon
    G4double a = 12.01 * g/mole;
    G4double z = 6;
    G4Element* elC = new G4Element("Carbon", "C", z, a);
    
    // define Hydrogen
    G4double a = 1.01 * g/mole;
    G4double z = 1;
    G4Element* elH = new G4Element("Hydrogen", "H", z, a);
    
    // make Composit material
    G4double density = 0.874 * g/cm3;
    G4int ncomp = 2;
    G4double fracMass;
    G4Material* NB501A = new G4Material("NB501A", density, ncomp);
    NB501A->AddElement(elH, fracMass = 0.90756);
    NB501A->AddElement(elC, fracMass = 0.092431);
    */
    G4Tubs* solidDet = new G4Tubs("DetectorSolid", detIR, detOR, 0.5 * detZspan, 0. *deg, 360. *deg); 
    return new G4LogicalVolume(solidDet, XyleneMat, "DetectorLogic");
}

//пустой мир
G4LogicalVolume* MyDetectorConstruction::CreateWorld(){

    G4NistManager *nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    //world space
    G4Box *solidWorld  = new G4Box("WorldSolid", scalesWorld[0] * 0.5, scalesWorld[1] * 0.5, scalesWorld[2] * 0.5);

    return new G4LogicalVolume(solidWorld, worldMat, "WorldLogic");
}