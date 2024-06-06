#include "construction.hh"

#include "G4PVPlacement.hh"

const bool checkOverlaps = false;
G4VPhysicalVolume* MyDetectorConstruction::Construct(){

    
    G4LogicalVolume* LogicDetectorVolume = CreateStilbeneDetector();
    G4LogicalVolume* LogicContainerVolume1 = CreateContainer1();
    G4LogicalVolume* LogicContainerVolume2 = CreateContainer2();
    G4LogicalVolume* LogicWorld = CreateWorld();
    
    G4ThreeVector Cont2 = G4ThreeVector(DetectorPosition[0],DetectorPosition[1],DetectorPosition[2] + (detZspan + contThick) * (-0.5));
    G4ThreeVector Cont3 = G4ThreeVector(DetectorPosition[0],DetectorPosition[1],DetectorPosition[2] + (detZspan + contThick) * (0.5));

    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), LogicWorld, "physWorld", 0, false, 0, 0);
    G4PVPlacement* fContainerPV1 = new G4PVPlacement(0, DetectorPosition,  LogicContainerVolume1, "physContainer1", LogicWorld, false, 0, checkOverlaps);
    G4PVPlacement* fContainerPV2 = new G4PVPlacement(0, Cont2,  LogicContainerVolume2, "physContainer2", LogicWorld, false, 0, checkOverlaps);
    G4PVPlacement* fContainerPV3 = new G4PVPlacement(0, Cont3,  LogicContainerVolume2, "physContainer3", LogicWorld, false, 0, checkOverlaps);
    
    physDetector = new G4PVPlacement(0, DetectorPosition, LogicDetectorVolume, "physDetector", LogicWorld, false, 0, checkOverlaps);


    return physWorld;
}

void MyDetectorConstruction::ConstructSDandFild(){
    //need to create Fild
}
