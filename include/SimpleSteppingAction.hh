#pragma once


#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SimpleSteppingAction : public G4UserSteppingAction {
public:
    SimpleSteppingAction();

    ~SimpleSteppingAction() override;

    void UserSteppingAction(const G4Step *) override;
};