//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// shall cite the following Geant4-DNA collaboration publication:
// Med. Phys. 37 (2010) 4692-4708
// The Geant4-DNA web site is available at http://geant4-dna.org
//
// $Id$
//
/// \file dnaphysics.cc
/// \brief Implementation of the dnaphysics example

#ifdef G4MULTITHREADED
  #include "G4MTRunManager.hh"
#else
  #include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
  #include "G4VisExecutive.hh"
#endif

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char* argv[]) 
{
  // Choose the Random engine
  // CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine); 
 
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4int seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  // Construct the default run manager

#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(2);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory user initialization classes
  runManager->SetUserInitialization(new DetectorConstruction);
  
  runManager->SetUserInitialization(new PhysicsList);



  // std::vector<std::string> args(argv, argv+argc);
  // for (size_t i = 1; i < args.size(); ++i) {
    // std::string const & aFileName = args[2];
    // G4cout <<aFileName <<std::endl;
    // Do something with aFileName
// G4String binaryFileName="track";
// G4cout <<binaryFileName <<std::endl;

// G4String binaryFileName1=argv[1];
// G4cout <<binaryFileName1<<std::endl;

// G4String binaryFileName2=argv[2];
// G4cout <<binaryFileName2<<std::endl;


// if (argc==2){
  G4String trString="track";
  G4String binString=".bin";
 G4String binaryFileName = trString+argv[1]+binString;
 // G4cout << binaryFileName;
  std::ofstream track(binaryFileName,std::ios::binary);
  // User action initialization
  
  runManager->SetUserInitialization(new ActionInitialization(track));
  
  // Initialize G4 kernel
  
  runManager->Initialize();

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
    
  // Get the pointer to the User Interface manager 
  
  G4UImanager* UI = G4UImanager::GetUIpointer();  

   // if (argc==1)   // Define UI session for interactive mode.
   // { 
// #ifdef _WIN32
//    G4UIsession * session = new G4UIterminal();
// #else
//    G4UIsession * session = new G4UIterminal(new G4UItcsh);
// #endif
    UI->ApplyCommand("/control/execute dnaphysics2.in");
       // session->SessionStart();
  //      delete session;
  // }
  // else           // Batch mode
  // { 
  //   G4String command = "/control/execute ";
  //   G4String fileName = argv[1];
  //   UI->ApplyCommand(command+fileName);
  // }

#ifdef G4VIS_USE
  delete visManager;
#endif
  track.close();
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
