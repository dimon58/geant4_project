#include "SimpleGeometry.hh"
#include "SimplePrimaryGeneratorAction.hh"
#include "SimpleSteppingAction.hh"
#include "SimpleEventAction.hh"
#include "SimpleRootWriter.hh"

#include "G4RunManager.hh"
#include "G4OpticalPhysics.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"

#include <filesystem>
#include <iostream>
#include "Randomize.hh"


#define G4VIS_USE
#define G4UI_USE

#ifdef G4VIS_USE

#include "G4VisExecutive.hh"

#endif

#ifdef G4UI_USE

#include "G4UIExecutive.hh"

#endif


int main(int argc, char **argv) {

    // Root file path
    const std::filesystem::path ROOT_FILE = std::filesystem::path(__FILE__).parent_path() / "results" / "result.root";

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::MTwistEngine);

    // Construct the default run manager
    auto *runManager = new G4RunManager;

    // Detector construction
    runManager->SetUserInitialization(new SimpleGeometry());

    // Physics list
    G4VModularPhysicsList *physicsList = new QGSP_BERT;
    physicsList->SetVerboseLevel(1);
    physicsList->RegisterPhysics(new G4OpticalPhysics);
    runManager->SetUserInitialization(physicsList);

    // User action initialization
    runManager->SetUserAction(new SimplePrimaryGeneratorAction());
    runManager->SetUserAction(new SimpleEventAction());
    runManager->SetUserAction(new SimpleSteppingAction());


    // Initialize ROOT
    SimpleRootWriter::GetPointer()->Initialize(ROOT_FILE);
    SimpleRootWriter::GetPointer()->h1[0] = new TH1F(
            "edep",
            "Energy deposition in scintillator; E_{deposited} [MeV]; Entries",
            1000, 0, 20);

    // Initialize G4 kernel
    runManager->Initialize();

#ifdef G4VIS_USE
    // Initialize visualization
    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

    // Get the pointer to the User Interface manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) {
        // batch mode
        G4String command = "/control/execute macros/";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        // interactive mode : define UI session
#ifdef G4UI_USE
        auto *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute macros/init_vis.mac");
#else
        UImanager->ApplyCommand("/control/execute macros/init.mac");
#endif
        ui->SessionStart();
        delete ui;
#endif
    }

    SimpleRootWriter::GetPointer()->Finalize();

#ifdef G4VIS_USE
    delete visManager;
#endif
    delete runManager;

    return 0;
}
