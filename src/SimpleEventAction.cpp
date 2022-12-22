#include "SimpleEventAction.hh"

#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "SimpleRootWriter.hh"

#include "configs.hh"

SimpleEventAction::SimpleEventAction()
        : G4UserEventAction(), fPrintModulo(0) {}

SimpleEventAction::~SimpleEventAction() = default;

void SimpleEventAction::BeginOfEventAction(const G4Event *event) {

    SimpleRootWriter::GetPointer()->ResetEdep();

    G4long total = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    fPrintModulo = G4int(total / MESSAGE_EVENT_RATE);
    if (fPrintModulo < 1) fPrintModulo = 1;

    G4int eventNb = event->GetEventID() + 1;
    if (eventNb % fPrintModulo == 0) {
        G4cout << "---> Event " << eventNb << "/" << total << G4endl;
    }
}

void SimpleEventAction::EndOfEventAction(const G4Event *) {
    SimpleRootWriter::GetPointer()->FinalizeEvent();
}