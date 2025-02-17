#include "TrackSD.hh"
#include "TrackHit.hh"
#include "Analysis.hh"

#include "G4SystemOfUnits.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4VSolid.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"

#include <cmath>

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackSD::EndOfEvent(G4HCofThisEvent*)
{
    // Get number of hits
    G4int nHits = fHitsCollection->entries();

    // Set the radii of the scoring volumes to be used
    std::vector<double> radii {
            2.*nm,
            10.*nm,
            30.*nm,
            100.*nm,
            500.*nm
            };

    //std::vec<double> volumes = GetAssociatedVolumes(radii);

    // Sample the random track nSample times
    G4int nSample = 1000;
    G4double rFactor; G4double rTheta; G4double rPhi;
    G4double rX; G4double rY; G4double rZ; G4double rR;
    for ( G4int i=0; i<nSample; i++ )
    {
        // Select random hit: random number * nHits gives a random index between 0 and nHits
        // Make sure the random index is converted to an integer (UniformRand samples continuously)
        G4int rHit = 0;
        rHit = static_cast<G4int>( G4UniformRand()*nHits );

        // Get the position of the random hit
        G4ThreeVector rHitPos = (*fHitsCollection)[rHit]->GetPostPos();

        // Sample a radius factor between 0 and 1 (to be multiplied by the sampling radius)
        G4double rFactor = G4UniformRand();
        // Sample arcsin between -1 and 1 and add pi/2 to get a random polar angle in [-pi/2, pi/2]
        G4double rTheta  = asin(2*G4UniformRand()-1) + CLHEP::pi/2;
        // Sample between 0 and 2pi to get a random azimuthal angle
        G4double rPhi    = 2 * CLHEP::pi * G4UniformRand();

        // The rest must be looped over the different radius values
        for ( const auto& radius : radii )
        {
            // Need to randomly set the sampling sphere's centre to be within radius rHitPos

            // Convert random spherical coordinates to cartesian
            rR = rFactor*radius;
            rX = rR*sin(rTheta)*cos(rPhi);
            rY = rR*sin(rTheta)*sin(rPhi);
            rZ = rR*cos(rTheta);
            
            // Set the random centre position
            G4ThreeVector rCentrePos(
                    rX+rHitPos.x(), 
                    rY+rHitPos.y(),
                    rZ+rHitPos.z()
                    );

            // Check for neighbouring hits in the sphere and determine the total imparted energy
            G4double eImp  = 0;
            G4int    nEdep = 0;
            //G4double eInc = 0;
            for ( G4int i=0; i<nHits; i++ )
            {
               // if ((*fHitsCollection)[i]->GetEdep()>0)
               //     eInc = (*fHitsCollection)[i]->GetEdep();

                G4ThreeVector localPos = (*fHitsCollection)[i]->GetPostPos();

                if (
                        (localPos.x()-rCentrePos.x()) * (localPos.x()-rCentrePos.x()) +
                        (localPos.y()-rCentrePos.y()) * (localPos.y()-rCentrePos.y()) +
                        (localPos.z()-rCentrePos.z()) * (localPos.z()-rCentrePos.z())
                        <= radius*radius
                   ) {

                    eImp += (*fHitsCollection)[i]->GetEdep();
                    nEdep++;

                } 

            }

            // Calculate mean chord length and mass of sampling volume for use in weights
            G4double chord   = 4.*radius/3; // Mean chord length in a sphere (4*volume/surface area)
            G4double density = 1. * g/cm3;
            G4double mass    = (4./3) * CLHEP::pi * std::pow(radius,3) * density;

            double volume = GetAssociatedVolume(radius);

            G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

            analysisManager->FillNtupleDColumn(0, radius/nm);
            analysisManager->FillNtupleDColumn(1, nHits);
            analysisManager->FillNtupleDColumn(2, nEdep);
            analysisManager->FillNtupleDColumn(3, (eImp/eV)/(chord/nm));
            analysisManager->FillNtupleDColumn(4, (eImp/mass)/gray);
            analysisManager->FillNtupleDColumn(5, volume);
            //analysisManager->FillNtupleDColumn(6, eInc/eV);
            analysisManager->AddNtupleRow();

        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

double TrackSD::GetAssociatedVolume(double radius)
{
   // // Start empty vector
   // std::vec<double> volumes;

   // for ( double radius : radii )
   // {
   //     volumes.push_back(1);
   // }

   // return volumes;
   G4double volume = 1;

   return volume;

}
