#include "StackingAction.hh"
#include "G4StackManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction()
    : G4UserStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* aTrack)
{

    G4ClassificationOfNewTrack classification = fWaiting;

    const G4ParticleDefinition* particleType = aTrack->GetParticleDefinition();
    //G4String particleName = particleType->GetParticleName();
    // G4double charge = particleType->GetPDGCharge();
    if ( particleType == G4Gamma::Gamma() ) {

        // G4cout << "A(n) " << particleName << " was killed because it's charge was " << G4BestUnit(charge,"Electric charge") << " and not 0." << G4endl;
        G4ClassificationOfNewTrack classification = fKill;

    }

    return classification;

}
