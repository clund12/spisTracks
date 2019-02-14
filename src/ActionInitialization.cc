#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
//#include "StackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(G4String outputName)
    : G4VUserActionInitialization(), fFileName(outputName)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
    RunAction* runAction = new RunAction(fFileName);
    SetUserAction(runAction);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{

  PrimaryGeneratorAction* primGenAction = new PrimaryGeneratorAction();
  RunAction*              runAction     = new RunAction(fFileName);
  EventAction*            evAction      = new EventAction();
//  StackingAction*         stackAction   = new StackingAction();
//  SteppingAction*         stepAction    = new SteppingAction();

  SetUserAction(primGenAction);
  SetUserAction(runAction);
  SetUserAction(evAction);
//  SetUserAction(stackAction);
//  SetUserAction(stepAction);

}
