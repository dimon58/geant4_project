#pragma once


#include "G4UserEventAction.hh"
#include "globals.hh"

class SimpleEventAction : public G4UserEventAction {
public:
    SimpleEventAction();

    ~SimpleEventAction() override;

    void BeginOfEventAction(const G4Event *event) override;

    void EndOfEventAction(const G4Event *event) override;

private:
    G4int fPrintModulo;
};