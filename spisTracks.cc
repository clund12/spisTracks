#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "NullSession.hh"

#include "G4RunManager.hh"
//#include "G4MTRunManager.hh"
//#include "RunManager.hh"

#include "G4UImanager.hh"
//#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UIExecutive.hh"
//#include "G4VisExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char* argv[])
{

  G4Random::setTheEngine(new CLHEP::RanluxEngine);

  G4String trString = "/track";
  G4String outputName = argv[2]+trString+argv[3];

  G4RunManager* runManager = new G4RunManager();
  runManager->SetVerboseLevel(0);
  runManager->SetPrintProgress(0);
  //G4MTRunManager* runManager = new G4MTRunManager();
  //RunManager* runManager = new RunManager(outputName);

  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);

  PhysicsList* physics = new PhysicsList;
  runManager->SetUserInitialization(physics);

  ActionInitialization* action = new ActionInitialization(outputName);
  runManager->SetUserInitialization(action);

  // initialize visualization (not that it can take a verbosity argument as a string, e.g. "Quiet")
//  G4VisManager* visManager = new G4VisExecutive;
//  visManager->Initialize();
//
  // get the pointer to the UI manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  NullSession* nullSession = new NullSession;
  UImanager->SetCoutDestination(nullSession);

  G4UIExecutive* ui(0);
//
//
  if ( argc>1 )
  {
    ui = new G4UIExecutive(argc, argv, "tcsh");
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
//
//
//  else
//  {
//    ui = new G4UIExecutive(argc, argv, "qt");
//    UImanager->ApplyCommand("/control/execute init_vis.mac");
//    
//    if ( ui->IsGUI() )
//    {
//      UImanager->ApplyCommand("/control/execute gui.mac");
//      UImanager->ApplyCommand("/vis/open OGL 800x600-0+0");
//      ui->SessionStart();
//      delete ui;
//    }
//  }
//
//  delete visManager;
  delete nullSession;
  delete runManager;
//
  return 0;
  
}
