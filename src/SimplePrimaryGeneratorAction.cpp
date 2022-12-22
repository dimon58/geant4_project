#include "SimplePrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "cmath"


#define PARTICLE "mu-"

G4double e0 = 20 * cm;
G4double energy = 20 * GeV;

SimplePrimaryGeneratorAction *SimplePrimaryGeneratorAction::fPtr = nullptr;

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction()
        : G4VUserPrimaryGeneratorAction(), fParticleGun() {
    fPtr = this;
    fParticleGun = new G4ParticleGun();


    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle(PARTICLE);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->SetParticleEnergy(energy);

}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction() {
    delete fParticleGun;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

    // Генерируем частицы с одинаковой энергией = energy,
    // которые гарантировано (если не создадут ливень) пройдут через детектор.
    // Частица будет иметь случайное направление,
    // но будет изначально расположена на расстоянии e0 от точки пересечения со сцинтиллятором
    // Частицы будут появляться только сверху, так как это не будет влиять на картину, но так легче считать.

    G4double alpha = G4UniformRand() * pi, beta = G4UniformRand() * pi;
    G4double x0 = G4UniformRand() * 20 * cm, z0 = G4UniformRand() * 20 * cm;

    G4double ctg_a = tan(pi / 2 - alpha), ctg_b = tan(pi / 2 - beta);

    G4double dy = e0 / sqrt(1 + ctg_a * ctg_a + ctg_b * ctg_b);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ctg_a, -1, ctg_b));
    fParticleGun->SetParticlePosition(G4ThreeVector(x0 - dy * ctg_a, dy, z0 - dy * ctg_b));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

