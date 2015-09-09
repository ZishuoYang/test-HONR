// main91.cc is a part of the PYTHIA event generator.
// Copyright (C) 2015 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.
// It studies the charged multiplicity distribution at the LHC.
// Modified by Rene Brun, Axel Naumann and Bernhard Meirose
// to use ROOT for histogramming.

// Stdlib header file for input and output.
#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TH1.h"
#include "TTree.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

using namespace Pythia8;

int main(int argc, char* argv[]) {

  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);

  // Create Pythia instance and set it up to generate hard QCD processes
  // above pTHat = 20 GeV for pp collisions at 14 TeV.
  Pythia pythia;
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.readString("Beams:eCM = 14000.");
  pythia.init();

  // Create file on which histogram(s) can be saved.
  TFile* outFile = new TFile("hist.root", "RECREATE");

  // Book histogram.
  TH1F *multch = new TH1F("multch","charged multiplicity", 100, -0.5, 799.5);
  TH1F *multneu = new TH1F("multneu","neutral multiplicity", 100, -0.5, 799.5);
  TH1F *ppid = new TH1F("ppid","particle identification number", 1000, -500, 500);

  // Book tree
  TTree t1("t1","a tree");
  float ncharged,nneutral;
  t1.Branch("ncharged",&ncharged,"ncharged/F");
  t1.Branch("nneutral",&nneutral,"nneutral/F");

  // Begin event loop. Generate event; skip if generation aborted.
  for (int iEvent = 0; iEvent < 100; ++iEvent) {
    if (!pythia.next()) continue;

    // Find number of all final charged particles.
    int nCharged = 0;
    int nNeutral = 0;
    for (int i = 0; i < pythia.event.size(); ++i) {
      //      std::cout<<pythia.event[i].isCharged()<<endl;
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()==0)
        ++nCharged;

      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()!=0)
        ++nNeutral;

      if(pythia.event[i].isFinal())
	ppid->Fill( pythia.event[i].id() );
    }

    // Fill charged multiplicity in histogram. End event loop.
    multch->Fill( nCharged );
    multneu->Fill( nNeutral );
    ncharged=nCharged;
    nneutral=nNeutral;
    t1.Fill();
  }

  // Statistics on event generation.
  pythia.stat();


  // Save histogram on file and close file.
  multch->Write();
  multneu->Write();
  ppid->Write();
  t1.Write();
  delete outFile;

  // Done.
  return 0;
}
