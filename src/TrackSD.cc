#include "TrackSD.hh"
#include "TrackHit.hh"
#include "Analysis.hh"
#include "RunAction.hh"

// Geant4 classes
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
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"
#include "G4Accumulable.hh"

// C++ classes
#include <cmath>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackSD::TrackSD(G4String name)
    : G4VSensitiveDetector(name),
      //fDose(0),
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
    // Get current run action (for accumulables)
    //const G4UserRunAction* runAction = G4RunManager::GetRunManager()->GetUserRunAction();

    // Get the pointer to the current accumulables manager
    G4AccumulableManager* accMan = G4AccumulableManager::Instance();

    // Strings for the accumulable names
    G4String yFName, yDName, wAvName, counterString;

    // Get number of hits
    G4int nHits = fHitsCollection->entries();

    // Set the radii of the scoring volumes to be used
    std::vector<G4double> radii {
            //0.5*nm,
            //1.*nm,
            //2.5*nm,
            //2.*nm,
            //10.*nm,
            //30.*nm,
            //100.*nm,
            //500.*nm
            //2.5*nm,
            //5.*nm,
            //10.*nm,
            //15.*nm,
            //25.*nm
                1.*nm,
                5.*nm,
                10.*nm,
                15.*nm,
                25.*nm,
                50.*nm,
                100.*nm,
                500.*nm
            };

    //std::vec<double> volumes = GetAssociatedVolumes(radii);

    // Sample the random track nSample times
    G4int nSample = 1000;

    // Variables to be used during the calculation
    G4double rR; G4double rTheta; G4double rPhi;
    G4double rX; G4double rY; G4double rZ;
    G4double y; G4double y2;

    // Final vectors to be recorded
    //std::vector<double>

    // Pre-allocate some vectors
    //std::vector<G4double> eImps;
    //eImps.reserve(1000);
    //std::vector<G4int>    nEdeps;
    //nEdeps.reserve(1000);
    G4double wTp; //weight to account for density of transfer points
    G4double eImpw   = 0; // sum of energy imparted * wTp
    G4double eImp2w  = 0; // sum of energy imparted squared * wTp
    G4double wTps    = 0; // sum of wTps for normalization
    G4int    counter = 0;;
    for ( const auto& radius : radii )
    {

        G4double wAv = GetAssociatedVolumeWeight(radius);

        counterString = std::to_string(counter);
        wAvName = "wAv"+counterString;
        *accMan->GetAccumulable<G4double>(wAvName) += wAv;

        for ( G4int i=0; i<nSample; i++ )
        {

            // Select random hit: random number * nHits gives a random index between 0 and nHits
            // Make sure the random index is converted to an integer (UniformRand samples continuously)
            G4int rHit = 0;
            rHit = static_cast<G4int>( G4UniformRand()*nHits );

            // Get the position of the random hit
            G4ThreeVector rHitPos = (*fHitsCollection)[rHit]->GetPostPos();

            // Sample a radius factor between 0 and 1 (to be multiplied by the sampling radius)
            // Note the cubic root: to ensure uniform sampling within the associated volume, it 
            // should be more likely that a point is sampled further from a point as the volume 
            // fraction increases with the cube of the distance
            rR     = radius*std::cbrt(G4UniformRand());
            // Sample arcsin between -1 and 1 and add pi/2 to get a random polar angle in [-pi/2, pi/2]
            rTheta = asin(2.*G4UniformRand()-1.) + CLHEP::pi/2.;
            // Sample between 0 and 2pi to get a random azimuthal angle
            rPhi   = 2. * CLHEP::pi * G4UniformRand();

            // Need to randomly set the sampling sphere's centre to be within radius rHitPos

            // Convert random spherical coordinates to cartesian
            rX = rR*sin(rTheta)*cos(rPhi);
            rY = rR*sin(rTheta)*sin(rPhi);
            rZ = rR*cos(rTheta);

            G4bool isIn = rX*rX + rY*rY + rZ*rZ < radius*radius;
            if ( !isIn ) {

                G4cout << "No hits seen! Need to fix position sampling" << G4endl;

            }
            
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
            for ( G4int j=0; j<nHits; j++ )
            {
               // if ((*fHitsCollection)[i]->GetEdep()>0)
               //     eInc = (*fHitsCollection)[i]->GetEdep();

                G4ThreeVector localPos = (*fHitsCollection)[j]->GetPostPos();

                if (
                        (localPos.x()-rCentrePos.x()) * (localPos.x()-rCentrePos.x()) +
                        (localPos.y()-rCentrePos.y()) * (localPos.y()-rCentrePos.y()) +
                        (localPos.z()-rCentrePos.z()) * (localPos.z()-rCentrePos.z())
                        <= radius*radius
                   ) {

                    eImp += (*fHitsCollection)[j]->GetEdep();
                    nEdep++;

                } 

            }

            // Get weighted energy imparted and energy imparted squared values
            wTp    = 1. / nEdep;
            eImp   = eImp/eV;
            eImpw  +=  eImp * wTp;
            eImp2w +=  eImp*eImp * wTp;
            wTps   += wTp;

            //G4cout << "Radius " << radius/nm << " nm: Sample " << i << ": " << nEdep 
            //    << " transfer points, " << eImpw << ", " << eImp2w << G4endl;
        }
        // Calculate mean chord length and mass of sampling volume for use in weights
        G4double chord   = 4.*radius/3./nm; // Mean chord length in a sphere (4*volume/surface area)
        //G4double density = 1. * g/cm3;
        //G4double mass    = (4./3) * CLHEP::pi * std::pow(radius,3) * density;

        // Convert weighted imparted energies to lineal energy values (see eq. (3) in Famulari et
        // al, 2017)
        // The chord length can be divided out later
        y  = eImpw / chord / wTps;
        y2 = eImp2w / (chord*chord) / wTps;

        //G4cout << "y: " << y << ", y2: " << y2 << G4endl;
        //G4cout << "y*wAv: " << y*wAv << ", y2*wAv: " << y2*wAv << G4endl;

        // Add to the proper accumulables
        yFName = "yF"+counterString;
        yDName = "yD"+counterString;

        *accMan->GetAccumulable<G4double>(yFName)  += y*wAv;
        *accMan->GetAccumulable<G4double>(yDName)  += y2*wAv;

        //G4cout << "acc y*wAv: " << accMan->GetAccumulable<G4double>(yFName)->GetValue();
        //G4cout << ", acc y2*wAv: " << accMan->GetAccumulable<G4double>(yDName)->GetValue() << G4endl;

        //runAction->SumwAv(y*wAv,counter);
        //runAction->SumyD(y2*wAv,counter);
        //runAction->SumwAv(wAv,counter);

        // Get pointer to current analysis manager instance
        //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

        //analysisManager->FillNtupleDColumn(0, radius/nm);
        //analysisManager->FillNtupleIColumn(1, nHits);
        //analysisManager->FillNtupleDColumn(2, y);
        //analysisManager->FillNtupleDColumn(3, y2);
//      //  analysisManager->FillNtupleDColumn(2, (eImpw/wTps)/eV);
//      //  analysisManager->FillNtupleDColumn(3, (eImp2w/wTps)/(eV*eV));
//      //  analysisManager->FillNtupleDColumn(4, (eImpw/mass)/gray);
        //analysisManager->FillNtupleDColumn(4, wAv);
        ////analysisManager->FillNtupleDColumn(4, y2/y);
        ////analysisManager->FillNtupleDColumn(6, eInc/eV);
        //analysisManager->AddNtupleRow();
            
        // Reset accumulables to zero
        eImpw  = 0;
        eImp2w = 0;
        wTps   = 0;
        //eImps.clear();
        //nEdeps.clear();

        counter++;

    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double TrackSD::GetAssociatedVolumeWeight(G4double radius)
{

    // Get number of hits
    G4int nHits = fHitsCollection->entries();

    G4ThreeVector                        hitPos;
    std::vector<G4double>                doubleHitPos;
    std::vector< std::vector<G4double> > allHitPos;
    G4double hitX, hitY, hitZ;
    for ( G4int i=0; i<nHits; ++i )
    {
        // Get the positions of each hit
        hitPos = (*fHitsCollection)[i]->GetPostPos();

        // Convert positions to G4doubles (get rid of units)
        hitX = hitPos.x()/nm;
        hitY = hitPos.y()/nm;
        hitZ = hitPos.z()/nm;

        doubleHitPos.push_back(hitX);
        doubleHitPos.push_back(hitY);
        doubleHitPos.push_back(hitZ);

        // Add them to a single vector
        allHitPos.push_back(doubleHitPos);

        doubleHitPos.clear();

    }

    G4double voxelDivisions = 3.; // Must be odd
    G4double voxelSide = 2.0 * radius/nm / voxelDivisions;
    G4double voxelDimensions[3];
    voxelDimensions[0] = voxelSide / 2.0;
    voxelDimensions[1] = voxelSide / 2.0;
    voxelDimensions[2] = voxelSide / 2.0;


    // Apply offset of voxelDimensions to input points - store in tpPosData
    // Also divide each component by the voxel side, then floor the value - this gives an
    // integer-based transfer point (tp) position
    std::vector< std::vector<G4int> > tpPosData;
    std::vector<G4int>                tpPos;
    for ( auto pos : allHitPos )
    {
        //std::cout << "Current vector: " << std::endl;
        //PrintVectorDouble(pos);
        for ( G4int i = 0; i < 3; i++ ) {
            pos.at(i) += voxelDimensions[i];
            pos.at(i) /= voxelSide;
            tpPos.push_back( std::floor(pos.at(i)) );
        }

        tpPosData.push_back(tpPos);
        tpPos.clear();
    }

    //std::cout << "All tps: " << std::endl;
    //for ( std::vector<G4int> vox : tpPosData ) {
    //    PrintVectorInt(vox);
    //}

    tpPosData = Unique(tpPosData);

    //std::cout << "Vector of unique tp positions:" << std::endl;
    //for ( std::vector<G4int> unique : tpPosData ) 
    //{
    //    PrintVectorInt(unique);
    //}

    G4double numTPs = tpPosData.size();
    //std::cout << "Number of unique tp positions: " << numTPs << std::endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // Expand TP positions out in 3D (like meshgrid in matlab but without unnecessary - as no
    // plotting is taking place - copies of each vector)
    std::vector<G4int> currentPos;
    G4double x, y, z;
    G4int k0;//, k1, k2;
    std::vector<G4int> meshX, meshY, meshZ;
    std::vector< std::vector<G4int> > currentMesh;
    std::vector< std::vector< std::vector<G4int> > > fullMesh;
    G4int padding = (voxelDivisions - 1) / 2;
    for ( G4int j=0; j<numTPs; j++) 
    {
        currentPos = tpPosData.at(j);
        //std::cout << "Current tp position being meshed:" << std::endl;
        //PrintVectorInt(currentPos);
        x = currentPos.at(0);
        y = currentPos.at(1);
        z = currentPos.at(2);

        for ( k0 = -1*padding; k0 < padding+1; ++k0 ) 
        {
            meshX.push_back( x + k0 );
            meshY.push_back( y + k0 );
            meshZ.push_back( z + k0 );
            
        }

        currentMesh.push_back(meshX);
        currentMesh.push_back(meshY);
        currentMesh.push_back(meshZ);

        meshX.clear();
        meshY.clear();
        meshZ.clear();

        fullMesh.push_back(currentMesh);

        currentMesh.clear();

    }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // Find all x,y,z combinations (positions voxels describing the associated volume about the
    // transfer points - although not centred)
    // Any overlapping voxels will later be removed to avoid double counting
    std::vector< std::vector<G4int> > collapsedMesh;
    std::vector<G4int>                voxelCoord;

    G4int voxelXCoord, voxelYCoord, voxelZCoord;
    for ( auto const mesh : fullMesh )
    {
        for ( G4int ix=0; ix<voxelDivisions; ++ix )
        {
            for ( G4int iy=0; iy<voxelDivisions; ++iy )
            {
                for ( G4int iz=0; iz<voxelDivisions; ++iz )
                {
                    voxelXCoord = mesh.at(0).at(ix);
                    voxelYCoord = mesh.at(1).at(iy);
                    voxelZCoord = mesh.at(2).at(iz);

                    voxelCoord.push_back(voxelXCoord);
                    voxelCoord.push_back(voxelYCoord);
                    voxelCoord.push_back(voxelZCoord);

                    collapsedMesh.push_back(voxelCoord);

                    voxelCoord.clear();
                }
            }

        }

    }

    //for ( auto row : collapsedMesh )
    //{
    //    PrintVectorInt(row);
    //    std::cout << std::endl;
    //}

    //std::cout << "Number of voxels (not necessarily unique): " << collapsedMesh.size() << std::endl;

    // Remove overlapping voxels
    collapsedMesh = Unique(collapsedMesh);
    //for ( auto uniqueRow : collapsedMesh )
    //{
    //    PrintVectorInt(uniqueRow);
    //    std::cout << std::endl;
    //}

    G4int nUnique = collapsedMesh.size();
    //std::cout << "Number of unique voxels: " << nUnique << std::endl;

    // Calculate the approximate associated volume (aAV) - it is a relative, not absolute, value
    G4double aAV = nUnique * ( CLHEP::pi / 6. ) * std::pow(voxelSide, 3);

    //std::cout << "aAV: " << aAV << " nm3" << std::endl;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    return aAV;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector< std::vector<G4int> > TrackSD::Unique( std::vector< std::vector<G4int> > vec )
{
    std::vector< std::vector<G4int> >::const_iterator it0;
    std::vector< std::vector<G4int> >::iterator it1;
    // In a set, each value serves as its own key and must be unique.
    // When inserting into a set, there is a check to ensure that the element to be inserted does
    // not already exist in the set. If it does, the element will not be inserted but rather the
    // function will return an iterator to the equivalent element already in the set. This boolean
    // check can be accessed using (*insert iterator).second (true if unique, false if not inserted)
    std::set< std::vector<G4int> > uniquePos;
    bool isUniquePos;

    //std::cout << "Finding unique values. Checking: " << std::endl;
    for( it0 = vec.begin(), it1 = vec.begin(); it0 != vec.end(); ++it0 ) 
    {
        // If the element was the first with its value (and was thus inserted), set the current value
        // pointed to by it1 to this and then increment it1. This 'overwrites' the current value of
        // vec with only unique values. Once it0 reaches the end, the new vec written by it1 will be
        // shorter than the original by the number of elements between the current memory address
        // pointed to by it1 and the end of the originally allocated memory for vec. Therefore, the
        // original value will remain there (meaning at least one duplicate will exist). This is 
        // solved by an erase call after the loop.
        isUniquePos = uniquePos.insert(*it0).second;
        if( isUniquePos ) 
        {
            *it1++ = *it0;
        }

    }
    
    // Clear extraneous values at the end of tpPosData
    vec.erase( it1, vec.end() );

    return vec;

}
