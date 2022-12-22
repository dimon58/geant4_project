#include "SimplePrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

SimplePrimaryGeneratorAction *SimplePrimaryGeneratorAction::fPtr = nullptr;

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction()
        : G4VUserPrimaryGeneratorAction(), fParticleGun() {
    fPtr = this;
    fParticleGun = new G4GeneralParticleSource();

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);
}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction() {
    delete fParticleGun;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

