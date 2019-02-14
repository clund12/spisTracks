#include "TrackHit.hh"

#include "G4VisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<TrackHit>* TrackHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackHit::TrackHit(
        G4int partID, G4int procID, G4ThreeVector postPos, G4ThreeVector prePos,
        G4double preKin, G4double eDep, G4double eTrans, G4int trackID, G4int parentID
        )
    : G4VHit(), fPartID(partID), fProcID(procID), fPostPos(postPos), fPrePos(prePos),
      fPreKin(preKin), fEdep(eDep), fEtrans(eTrans), fTrackID(trackID), fParentID(parentID)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackHit::Print()
{
//    G4cout << G4BestUnit(fEdep, "Energy") << " was deposited at target position [" << G4BestUnit(fPos, "Length") << "]" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
