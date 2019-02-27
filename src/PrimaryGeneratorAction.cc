#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4GeneralParticleSource.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    G4VUserPrimaryGeneratorAction(),
    fGPS(new G4GeneralParticleSource)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fGPS->GeneratePrimaryVertex(anEvent);    

    G4double energy = fGPS->GetParticleEnergy();
    G4cout << "The energy is " << G4BestUnit(energy, "Energy") << G4endl;
}
