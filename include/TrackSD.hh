#ifndef TrackSD_h
#define TrackSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackHit.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackSD : public G4VSensitiveDetector
{
  public:
      TrackSD(G4String name);
      virtual ~TrackSD();

      virtual void   Initialize(G4HCofThisEvent*);
      virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      virtual void   EndOfEvent(G4HCofThisEvent*);

      //virtual std::vec<double> GetAssociatedVolumes(std::vec<double>);
      virtual G4double GetAssociatedVolumeWeight(G4double);

      void SetDose(G4double dose) { fDose = dose; }
      G4double GetDose() const { return fDose; }

  private:
      TrackHitsCollection* fHitsCollection;
      G4int fTrackHCID;
      G4double fDose;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
