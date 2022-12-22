#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "SimpleDetector.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry()
        : G4VUserDetectorConstruction(),
          fScoringVolume(nullptr) {
}

SimpleGeometry::~SimpleGeometry() {}


G4VPhysicalVolume *SimpleGeometry::Construct() {
    G4bool checkOverlaps = true;


    // world
    G4Material *air = DefineMaterial("G4_AIR");

    G4double world_sizeXY = 2 * m;
    G4double world_sizeZ = 2 * m;

    G4Material *water = DefineMaterial("G4_WATER");

    auto *solidWorld = new G4Box("World", 0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);

    auto *logicWorld =            new G4LogicalVolume(solidWorld, air, "World");

    G4VPhysicalVolume *physWorld =
            new G4PVPlacement(nullptr,                      //rotation
                              G4ThreeVector(),       //position
                              logicWorld,            //this volume
                              "World",               //this placement name
                              nullptr,                     //mother volume
                              false,
                              0,
                              checkOverlaps);

    // geometry
    G4double scintWidth = 30 * cm;
    G4double scintLength = 30 * cm;
    G4double scintHeight = 2 * cm;
    G4double dist = 10 * cm; //CLHEP::cm


    // detector
    auto *sc1box = new G4Box("sc1box", scintWidth / 2, scintHeight / 2, scintLength / 2);
    auto *sc1lv = new G4LogicalVolume(sc1box, water, "sc1lv");
    new G4PVPlacement(nullptr, G4ThreeVector(0., -dist, 0.),
                      sc1lv, "sc1pv", logicWorld, true,
                      0, checkOverlaps);


    auto *sd1 = new SimpleDetector("sc1sd");
    G4SDManager *SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(sd1);
    sc1lv->SetSensitiveDetector(sd1);


    // detector 2
    auto *box2 = new G4Box("box2", scintWidth / 2, scintHeight / 2, scintLength / 2);
    auto *sc2lv = new G4LogicalVolume(box2, water, "sc2lv");
    new G4PVPlacement(0, G4ThreeVector(0., dist, 0.),
                      sc2lv, "sc2pv", logicWorld, true,
                      0, checkOverlaps);


    auto *sd2 = new SimpleDetector("sc2sd");
    SDman->AddNewDetector(sd2);
    sc2lv->SetSensitiveDetector(sd2);

    return physWorld;
}

G4Material *SimpleGeometry::DefineMaterial(const G4String& material, G4double density) {
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *mat = nist->FindOrBuildMaterial(material);
    if (mat != nullptr) {
        return mat;
    } else {
        G4cerr << "Unknown material: " << material << G4endl;
        return nullptr;
    }
}

