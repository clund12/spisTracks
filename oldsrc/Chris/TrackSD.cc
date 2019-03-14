#include "TrackSD.hh"
#include "TrackHit.hh"

#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4VSolid.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackSD::TrackSD(G4String name)
    : G4VSensitiveDetector(name),
      fDose(0),
      fHitsCollection(0),
      fTrackHCID(-1)
{
    G4String hcName = "trackColl";
    collectionName.insert(hcName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackSD::~TrackSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackSD::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new TrackHitsCollection(SensitiveDetectorName, collectionName[0]);

    if ( fTrackHCID<0 )
    {
        fTrackHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fTrackHCID, fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{

    /*************************************************************************************************
     * If you want to score particle ID and the process at each step, put that here. For now, they
     * are left as dummy variables
    *************************************************************************************************/

    G4int particleID = 0;
    G4int processID = 0;

    G4double eDep = step->GetTotalEnergyDeposit();
    if ( eDep == 0. ) return true;
    
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();

    G4ThreeVector prePos = preStepPoint->GetPosition();
    G4ThreeVector postPos = postStepPoint->GetPosition();

    G4double preKin = preStepPoint->GetKineticEnergy();
    G4double postKin = postStepPoint->GetKineticEnergy();
    G4double eTrans = preKin-postKin;

    G4int trackID = step->GetTrack()->GetTrackID();
    G4int parentID = step->GetTrack()->GetParentID(); 


    TrackHit* hit = new TrackHit(
            particleID, processID, postPos, prePos, preKin, eDep, eTrans, trackID, parentID
            );
    fHitsCollection->insert(hit);
    
    return true;
}
