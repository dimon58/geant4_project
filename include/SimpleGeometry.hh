#pragma once


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class G4LogicalVolume;

class G4Material;

class SimpleGeometry : public G4VUserDetectorConstruction {
public:
    SimpleGeometry();

    ~SimpleGeometry() override;

    G4VPhysicalVolume *Construct() override;

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    static G4Material *DefineMaterial(const G4String& material, G4double density = 0);

protected:
    G4LogicalVolume *fScoringVolume;
private:
    G4double fAngle;
};

