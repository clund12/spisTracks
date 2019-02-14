#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// For randomizing the seed
#include "Randomize.hh"
#include <time.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(G4String fileName)
 : G4UserRunAction(), fFileName(fileName)
{

    G4long seed=time(0);
    G4Random::setTheSeed(seed);
    // Create analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);
    //analysisManager->SetNtupleMerging(true);

    //G4cout << "Using " << analysisManager->GetType() << G4endl;

    if ( IsMaster() ) {

        analysisManager->CreateNtuple(
                "RawData",                                          // name
                "Positions and sizes of energy deposition events"); // title
        analysisManager->CreateNtupleIColumn("Event ID");
        analysisManager->CreateNtupleIColumn("Particle ID");
        analysisManager->CreateNtupleIColumn("Process ID");
        analysisManager->CreateNtupleDColumn("post x-position");
        analysisManager->CreateNtupleDColumn("post y-position");
        analysisManager->CreateNtupleDColumn("post z-position");
        analysisManager->CreateNtupleDColumn("pre x-position");
        analysisManager->CreateNtupleDColumn("pre y-position");
        analysisManager->CreateNtupleDColumn("pre z-position");
        analysisManager->CreateNtupleDColumn("pre kinetic energy");
        analysisManager->CreateNtupleDColumn("energy deposited");
        analysisManager->CreateNtupleDColumn("energy transferred");
        analysisManager->CreateNtupleIColumn("Track ID");
        analysisManager->CreateNtupleIColumn("Parent ID");
        analysisManager->FinishNtuple();

    }

   // G4int nbins = 500;
   // G4double vmin = 1.;
   // G4double vmax = 10000000.;
   // const G4String& unitName = "none";
   // const G4String& fcnName = "none";
   // const G4String& binScheme = "log";
   // analysisManager->CreateH1("1","Primary particle spectra", nbins, vmin, vmax, unitName, fcnName, binScheme);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    // Have to manually delete the created analysis manager
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{

    // Open an output file (file type handled automatically)
    //if ( IsMaster() ) {

        // Get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();
        //G4String fileName = RunManager::GetFileName();
        analysisManager->OpenFile(fFileName);

    //}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{

    //if ( IsMaster() ) {
        // Save histograms
        auto analysisManager = G4AnalysisManager::Instance();

        analysisManager->Write();
        analysisManager->CloseFile();

    //}
}
