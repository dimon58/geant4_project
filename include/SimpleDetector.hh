#pragma once

#include "G4VSensitiveDetector.hh"

#include <vector>

class G4Step;

class G4HCofThisEvent;

class SimpleDetector : public G4VSensitiveDetector {
public:
    explicit SimpleDetector(const G4String &name);

    ~SimpleDetector() override;

    // methods from base class
    void Initialize(G4HCofThisEvent *hitCollection) override;

    G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;

    void EndOfEvent(G4HCofThisEvent *hitCollection) override;

private:

};
