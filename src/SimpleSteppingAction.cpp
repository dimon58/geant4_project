#include "SimpleSteppingAction.hh"
#include "G4Step.hh"


using namespace CLHEP;

SimpleSteppingAction::SimpleSteppingAction() : G4UserSteppingAction() {}

SimpleSteppingAction::~SimpleSteppingAction() = default;

void SimpleSteppingAction::UserSteppingAction(const G4Step *step) {
    int pdg = step->GetTrack()->GetDefinition()->GetPDGEncoding();

    double edep = step->GetTotalEnergyDeposit();
    G4ThreeVector position = step->GetTrack()->GetPosition();

}