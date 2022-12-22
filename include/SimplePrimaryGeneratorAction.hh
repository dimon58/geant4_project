#pragma once


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include <G4ParticleGun.hh>
#include "globals.hh"

class G4Event;

class SimplePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    SimplePrimaryGeneratorAction();

    ~SimplePrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event *) override;

    static SimplePrimaryGeneratorAction *GetPointer() { return fPtr; }

    const G4ParticleGun *GetParticleGun() const { return fParticleGun; }

private:
    G4ParticleGun *fParticleGun; // pointer a to G4 gun class
    static SimplePrimaryGeneratorAction *fPtr;
};


