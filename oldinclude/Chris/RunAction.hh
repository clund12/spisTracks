#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"
#include <vector>

class G4Run;
/// Run action class

class RunAction : public G4UserRunAction
{
  public:
    RunAction(G4String);
    // TIP: avoid constructors with arguments
    // all data can be retrieved from G4RunManager
    // or others: G4SDManager::FindSensitiveDetector
    virtual ~RunAction();

    //virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
  	G4int    fRunID;
    G4String fFileName;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
