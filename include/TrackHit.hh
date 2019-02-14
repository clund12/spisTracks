#ifndef TrackHit_h
#define TrackHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4AttDef;
class G4AttValue;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackHit : public G4VHit
{
  public:
      TrackHit(
              G4int partID, G4int procID, G4ThreeVector postPos, G4ThreeVector prePos,
              G4double preKin, G4double eDep, G4double eTrans, G4int TrackID, G4int parentID
              );
      virtual ~TrackHit() {}

      inline void *operator new(size_t);
      inline void operator  delete(void*aHit);

      void Print();

      void SetPartID(G4int partID) { fPartID = partID; }
      void SetProcID(G4int procID) { fProcID = procID; }
      void SetPostPos(G4ThreeVector postPos) { fPostPos = postPos; }
      void SetPrePos(G4ThreeVector prePos) { fPrePos = prePos; }
      void SetPreKin(G4double preKin) { fPreKin = preKin; }
      void SetEdep(G4double eDep) { fEdep = eDep; }
      void SetEtrans(G4double eTrans) { fEtrans = eTrans; }
      void SetTrackID(G4int trackID) { fTrackID = trackID; }
      void SetParentID(G4int parentID) { fParentID = parentID; }

      G4int         GetPartID()   const { return fPartID; }
      G4int         GetProcID()   const { return fProcID; }
      G4ThreeVector GetPostPos()  const { return fPrePos; }
      G4ThreeVector GetPrePos()   const { return fPrePos; }
      G4double      GetPreKin()   const { return fPreKin; }
      G4double      GetEdep()     const { return fEdep; }
      G4double      GetEtrans()   const { return fEtrans; }
      G4int         GetTrackID()  const { return fTrackID; }
      G4int         GetParentID() const { return fParentID; }

  private:
      G4int         fPartID;
      G4int         fProcID;
      G4ThreeVector fPostPos;
      G4ThreeVector fPrePos;
      G4double      fPreKin;
      G4double      fEdep;
      G4double      fEtrans;
      G4int         fTrackID;
      G4int         fParentID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Memory allocation stuff to speed things up. /unused/DNAHit.hh has more info.
typedef G4THitsCollection<TrackHit> TrackHitsCollection;

extern G4ThreadLocal G4Allocator<TrackHit>* TrackHitAllocator;

inline void* TrackHit::operator new(size_t)
{
    if ( !TrackHitAllocator )
        TrackHitAllocator = new G4Allocator<TrackHit>;
    return (void*)TrackHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void TrackHit::operator delete(void*aHit)
{
    TrackHitAllocator->FreeSingle( ( TrackHit* ) aHit );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
