#include "StackingAction.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <G4RunManager.hh>

// #include "G4NeutrinoE.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction(std::ofstream& out):myfile(out)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
  G4ClassificationOfNewTrack     classification = fUrgent;
  //keep primary particle
  // if (track->GetDefinition()->GetParticleName() == "gamma") G4cout << track->GetKineticEnergy()/eV <<G4endl;
  if (track->GetParentID() > 0 && track->GetDefinition()->GetParticleName() == "gamma") 
    {//classification= fKill;
       // G4cout <<" Killing Fluoro!";
    }
  
  if (track->GetDefinition()->GetParticleName() == "e-") {
    if (track->GetKineticEnergy() < 10*CLHEP::eV) {
        classification=fKill;
    }
     // G4cout << track->GetKineticEnergy()/eV <<G4endl;
      // classification= fKill;
 //  G4int trackID = track->GetTrackID();
 //  G4int parentID = track->GetParentID();
 //  G4ThreeVector pPost = track->GetPosition();
 //  G4ThreeVector mDir1 = track->GetMomentumDirection();
 //  G4double kinEnergyPre = track->GetKineticEnergy();
 //  G4double dummy = -1.0; 
 //   G4int flagParticle, flagProcess;
 //   flagParticle = 1;
 //   flagProcess = 0; // creation
 //  // G4cout << "electron! "<< trackID <<" " <<parentID <<" " << pos.getX()/mm<<" " << pos.getY()/mm<<" " << pos.getZ()/mm<<" "<<ener/MeV<<" " <<G4endl;

	// float nEv=G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
 //    G4double buff;  
 //    float buf;
 //    // G4int dummy = 0;
 //    // int indint=Run->GetInd();
 //    // G4ThreeVector pPre = point1->GetPosition();
 //      buf = nEv;
 //      myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //    myfile.write(reinterpret_cast<const char *>(&flagParticle),sizeof(short));
 //    myfile.write(reinterpret_cast<const char *>(&flagProcess),sizeof(short));
 //        buff = pPost.getX()/nm;
 //        buf = buff;
 //    myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //      buff = pPost.getY()/nm;
 //      buf = buff;
 //    myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //      buff = pPost.getZ()/nm;
 //      buf = buff;
 //    myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));


 //          buff = mDir1.getX();
 //          buf = buff;
 //        myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //          buff = mDir1.getY();
 //          buf = buff;
 //        myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //          buff = mDir1.getZ();
 //          buf = buff;
 //        myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));


 //      buff = kinEnergyPre/eV;
 //      buf = buff;
 //    myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //     	buff =dummy;
 //        buf = buff;
 //        myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));
 //        myfile.write(reinterpret_cast<const char *>(&buf),sizeof(float));

 //    myfile.write(reinterpret_cast<const char *>(&trackID),sizeof(short));
 //    myfile.write(reinterpret_cast<const char *>(&parentID),sizeof(short));


}
    
    return classification;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
