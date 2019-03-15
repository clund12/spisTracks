#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Analysis.hh"
#include "RunManager.hh"
#include "MTRunManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4AccumulableManager.hh"
#include "G4Accumulable.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// For randomizing the seed
#include "Randomize.hh"
#include <time.h>

#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{

    G4long seed=time(0);
    G4Random::setTheSeed(seed);
    // Create analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(0);

    //G4cout << "Using " << analysisManager->GetType() << G4endl;


    analysisManager->CreateNtuple(
            "ys",                      // name
            "Microdosimetric distributions"); // title
    //analysisManager->CreateNtupleDColumn("Sampling volume radius");
    //analysisManager->CreateNtupleIColumn("Number of transfer points in track");
    //analysisManager->CreateNtupleDColumn("Weighted imparted energy [eV]");
    //analysisManager->CreateNtupleDColumn("Weighted squared imparted energy [eV2]");
    analysisManager->CreateNtupleDColumn("yF [keV/um]");
    analysisManager->CreateNtupleDColumn("yD [keV/um]");
//    analysisManager->CreateNtupleDColumn("Sum(wAv)");
    //analysisManager->CreateNtupleDColumn("Specific energy [Gy]");
    //analysisManager->CreateNtupleDColumn("Associated volume");
    analysisManager->FinishNtuple();


    G4AccumulableManager* accMan = G4AccumulableManager::Instance();

    // yD accumulables
    fNradii = 5;
    G4String yFName, yDName, wAvName, counterString;
    for ( int i=0; i<fNradii; ++i )
    {
        counterString = std::to_string(i);
        yFName = "yF"+counterString;
        yDName = "yD"+counterString;
        wAvName = "wAv"+counterString;

        accMan->CreateAccumulable<G4double>(yFName,  0.);
        accMan->CreateAccumulable<G4double>(yDName,  0.);
        accMan->CreateAccumulable<G4double>(wAvName, 0.);

    }

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

    G4AccumulableManager* accMan = G4AccumulableManager::Instance();
    accMan->Reset();

    // Open an output file (file type handled automatically)
    if ( IsMaster() ) {

        // Get analysis manager
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->OpenFile();

    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* aRun)
{

    G4AccumulableManager* accMan = G4AccumulableManager::Instance();
    accMan->Merge();

    if ( IsMaster() )
    {
        auto analysisManager = G4AnalysisManager::Instance();
    
        // Write values to ntuple
        G4String yFName, yDName, wAvName, counterString;
        G4double yF, yD, wAv;
        for ( int j=0; j<fNradii; ++j )
        {
    
            counterString = std::to_string(j);
            yFName = "yF"+counterString;
            yDName = "yD"+counterString;
            wAvName = "wAv"+counterString;
    
            yF = accMan->GetAccumulable<G4double>(yFName)->GetValue(); 
            yD = accMan->GetAccumulable<G4double>(yDName)->GetValue(); 
            wAv = accMan->GetAccumulable<G4double>(wAvName)->GetValue(); 
            //G4cout << "yF: " << yF << G4endl;
            //G4cout << "yD: " << yD/yF << G4endl;
    
            yF /= wAv;
            yD /= wAv;
    
            //G4cout << "yF/wAv: " << yF << G4endl;
            //G4cout << "yD/wAv: " << yD/yF << G4endl;
    
            analysisManager->FillNtupleDColumn(0,yF);
            analysisManager->FillNtupleDColumn(1,yD/yF);
            //analysisManager->FillNtupleDColumn(wAv);
    
            analysisManager->AddNtupleRow();
        }
    
    //    std::vector<G4double> yFs  = fyF.GetValue();
    //    std::vector<G4double> yDs  = fyD.GetValue();
    //    std::vector<G4double> wAvs = fWavs.GetValue();
    //    //if ( IsMaster() ) {
    //    // Save histograms
    
        analysisManager->Write();
        analysisManager->CloseFile();


    }

}
