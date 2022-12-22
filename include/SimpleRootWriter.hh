#pragma once

#include "G4SystemOfUnits.hh"
#include "G4Types.hh"

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include <string>
#include <iostream>
#include <filesystem>

using namespace std;

class SimpleRootWriter {
public:
    void Initialize(const std::filesystem::path& path, bool SaveTree = false);

    void Fill() const;                // store an event
    void Finalize();    // write tree to a file
    static SimpleRootWriter *GetPointer() {
        if (pInstance == nullptr) pInstance = new SimpleRootWriter();
        return pInstance;
    };

    void ResetEdep() { edepScint1 = 0.; };

    void AddEdep(G4double edep) { edepScint1 += edep; }

    void FinalizeEvent() {
        h1[0]->Fill(edepScint1 / MeV);
    };

private:
    SimpleRootWriter() { fSaveTree = false; };     // empty constructor
    static SimpleRootWriter *pInstance;

    bool fSaveTree;

    G4double edepScint1;

public:

    TH1F *h1[500];
    TH2F *h2[100];

    TTree *tree;

private:
    TFile *file;
};
