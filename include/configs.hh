#pragma once

#include <G4Types.hh>
#include <G4SystemOfUnits.hh>

// -------------------- Geometry -------------------- //

#define WORLD_MATERIAL "G4_AIR"
#define DETECTOR_MATERIAL "G4_POLYSTYRENE"

G4bool checkOverlaps = true;

G4double world_sizeXY = 2 * m;
G4double world_sizeZ = 2 * m;

// scintillator sizes
G4double detector_width = 20 * cm;
G4double detector_length = 20 * cm;
G4double detector_height = 1 * cm;