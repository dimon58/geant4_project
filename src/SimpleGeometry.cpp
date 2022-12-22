#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "SimpleDetector.hh"

#include "configs.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry()
        : G4VUserDetectorConstruction(),
          fScoringVolume(nullptr) {
}

SimpleGeometry::~SimpleGeometry() {}


G4VPhysicalVolume *SimpleGeometry::Construct() {

    G4Material *world_material = DefineMaterial(WORLD_MATERIAL);
    G4Material *detector_material = DefineMaterial(DETECTOR_MATERIAL);

    // world
    auto *solidWorld = new G4Box("World", world_sizeXY / 2, world_sizeXY / 2, world_sizeZ / 2);
    auto *logicWorld = new G4LogicalVolume(solidWorld, world_material, "World");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(
            nullptr,                    //rotation
            G4ThreeVector(0., 0., 0.),  //position
            logicWorld,                 //this volume
            "World",                    //this placement name
            nullptr,                    //mother volume
            false,
            0,
            checkOverlaps
    );

    // detector
    auto *detector_box = new G4Box("detector_box", detector_width / 2, detector_height / 2, detector_length / 2);
    auto *detector_lv = new G4LogicalVolume(detector_box, detector_material, "detector_lv");
    new G4PVPlacement(
            nullptr, G4ThreeVector(detector_width / 2, -detector_height / 2, detector_length / 2),
            detector_lv, "detector_pv", logicWorld,
            true, 0, checkOverlaps
    );


    auto *detector = new SimpleDetector("detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    detector_lv->SetSensitiveDetector(detector);


    return physWorld;
}

G4Material *SimpleGeometry::DefineMaterial(const G4String &material, G4double density) {
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *mat = nist->FindOrBuildMaterial(material);
    if (mat != nullptr) {
        return mat;
    } else {
        G4cerr << "Unknown material: " << material << G4endl;
        return nullptr;
    }
}

