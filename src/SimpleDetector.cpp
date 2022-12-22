#include "SimpleDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "SimpleRootWriter.hh"

using namespace CLHEP;

SimpleDetector::SimpleDetector(const G4String &name)
        : G4VSensitiveDetector(name) {

}

SimpleDetector::~SimpleDetector() {}

void SimpleDetector::Initialize(G4HCofThisEvent *hce) {

}

G4bool SimpleDetector::ProcessHits(G4Step *step, G4TouchableHistory *) {
    G4int pdgcode = step->GetTrack()->GetDefinition()->GetPDGEncoding();
    G4double energy = step->GetTrack()->GetKineticEnergy();
    G4double time = step->GetPostStepPoint()->GetGlobalTime();
    G4int id = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    G4double edep = step->GetTotalEnergyDeposit();
    SimpleRootWriter::GetPointer()->AddEdep(edep);

    return true;
}

void SimpleDetector::EndOfEvent(G4HCofThisEvent *) {

}