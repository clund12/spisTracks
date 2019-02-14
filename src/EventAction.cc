#include "EventAction.hh"
#include "TrackHit.hh"
#include "Analysis.hh"
//#include "SteppingAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(),
    fTrackHCID(-1)
{
  G4RunManager::GetRunManager()->SetPrintProgress(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    if ( fTrackHCID==-1 )
    {
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        fTrackHCID = sdManager->GetCollectionID("track/trackColl");
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get the hits collection of the event
  G4HCofThisEvent* hce = event->GetHCofThisEvent();

  if (!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found.\n";
    G4Exception("EventAction::EndOfEventAction()",
                "Code001",
                JustWarning,
                msg);
    return;
  }

  // Get the collection corresponding to the phantom
  TrackHitsCollection* trackHC = static_cast<TrackHitsCollection*>(hce->GetHC(fTrackHCID));

  if ( (!trackHC) )
  {
      G4ExceptionDescription msg;
      msg << "Some of the hits collections of this event not found.\n";
      G4Exception("EventAction::EndOfEventAction()",
              "Code001",
              JustWarning,
              msg);
      return;
  }

  // Display hits
  G4int n_hit = trackHC->entries();
  // G4cout << "There were " << n_hit << " energy deposition events along this track." << G4endl;
  G4int eventID = event->GetEventID();

  auto analysisManager = G4AnalysisManager::Instance();
 
  // Get starting position of track
  TrackHit* hit = (*trackHC)[0];
  G4ThreeVector pos = hit->GetPostPos();
  G4double x0 = pos.x();
  G4double y0 = pos.y();
  G4double z0 = pos.z();

  G4int partID; G4int procID; G4double postX; G4double postY; G4double postZ; 
  G4double preX; G4double preY; G4double preZ; G4double preKin; G4double eDep; G4double eTrans; 
  G4int trackID; G4int parentID;
  for (G4int i=0; i<n_hit; i++)
  {
      hit = (*trackHC)[i];
      //hit->Print();
        
      partID = hit->GetPartID();
      procID = hit->GetProcID();

      pos   = hit->GetPostPos();
      postX = pos.x() - x0;
      postY = pos.y() - y0;
      postZ = pos.z() - z0;

      pos  = hit->GetPrePos();
      preX = pos.x() - x0;
      preY = pos.y() - y0;
      preZ = pos.z() - z0;

      preKin = hit->GetPreKin();
      eDep   = hit->GetEdep();
      eTrans = hit->GetEtrans();

      trackID = hit->GetTrackID();
      parentID = hit->GetParentID();

      analysisManager->FillNtupleIColumn(0, eventID);
      analysisManager->FillNtupleIColumn(1, partID);
      analysisManager->FillNtupleIColumn(2, procID);
      analysisManager->FillNtupleDColumn(3, postX/nm);
      analysisManager->FillNtupleDColumn(4, postY/nm);
      analysisManager->FillNtupleDColumn(5, postZ/nm);
      analysisManager->FillNtupleDColumn(6, preX/nm);
      analysisManager->FillNtupleDColumn(7, preY/nm);
      analysisManager->FillNtupleDColumn(8, preZ/nm);
      analysisManager->FillNtupleDColumn(9, preKin/eV);
      analysisManager->FillNtupleDColumn(10, eDep/eV);
      analysisManager->FillNtupleDColumn(11, eTrans/eV);
      analysisManager->FillNtupleIColumn(12, trackID);
      analysisManager->FillNtupleIColumn(13, parentID);
      analysisManager->AddNtupleRow();
  }

}
