#include "SimpleRootWriter.hh"


SimpleRootWriter *SimpleRootWriter::pInstance = nullptr;

void SimpleRootWriter::Initialize(std::filesystem::path path, bool SaveTree) {

    file = new TFile(path.c_str(), "RECREATE");

    for (int hidx = 0; hidx < 100; hidx++) {
        h1[hidx] = nullptr;
        h2[hidx] = nullptr;
    }

    fSaveTree = SaveTree;
}

void SimpleRootWriter::Fill() const {
    if (fSaveTree) tree->Fill();
}

void SimpleRootWriter::Finalize() {
    file->cd();

    int hidx = 0;
    for (hidx = 0; hidx < 100; hidx++) {
        if (h1[hidx] != nullptr) {
            h1[hidx]->Sumw2();
            h1[hidx]->Write();
        }
        if (h2[hidx] != nullptr) {
            h2[hidx]->Sumw2();
            h2[hidx]->Write();
        }
    }

    if (fSaveTree && tree != nullptr) tree->Write();

    file->Close();
}