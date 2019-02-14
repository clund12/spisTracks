//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// shall cite the following Geant4-DNA collaboration publication:
// Med. Phys. 37 (2010) 4692-4708
// The Geant4-DNA web site is available at http://geant4-dna.org
//
// $Id$
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
#include <G4RunManager.hh>
#include "Analysis.hh"
#include "G4EmCalculator.hh"

#include "SteppingAction.hh"
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"

#include "G4Electron.hh"
#include "G4Proton.hh"
#include "G4Gamma.hh"
#include "G4Alpha.hh"
#include "G4DNAGenericIonsManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"

#include "G4EmCalculator.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(RunAction* run,std::ofstream& out):Run(run),track(out)
 // G4UserSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{ 
  if (step->GetTotalEnergyDeposit() != 0) {
  G4StepPoint* point1=step->GetPreStepPoint();
   G4TouchableHandle touch1 = point1->GetTouchableHandle();
   G4VPhysicalVolume* volume = touch1->GetVolume();
   G4String volumeName = volume->GetName();
  G4double eDep=step->GetTotalEnergyDeposit();
  G4ParticleDefinition* part=step->GetTrack()->GetDefinition();
  // G4double partEnergy=step->GetTrack()->GetKineticEnergy();
   G4LogicalVolume* lVolume = volume->GetLogicalVolume();
   // G4Region* regionDeDx=lVolume->GetRegion();

    G4Material* material = lVolume->GetMaterial();
  // G4EmCalculator emCalculator;
  // G4double range= emCalculator.GetRange(partEnergy,part,material);
  // G4Track * aTrack = step->GetTrack();
  // G4cout << partEnergy/eV << " eV, "<< range/nm <<" nm"<< std::endl;

  G4String partName = part->GetParticleName();
  G4StepPoint* point2=step->GetPostStepPoint();
  G4ThreeVector pPost = point2->GetPosition();
  G4ThreeVector pPre = point1->GetPosition();
  G4String limitingProcessName = point2->GetProcessDefinedStep()->GetProcessName();

  // kill all other photons
  G4int trackID = step->GetTrack()->GetTrackID();
  G4int parentID = step->GetTrack()->GetParentID();
  G4double kinEnergyPre = point1->GetKineticEnergy();
  G4ThreeVector mDir1 = point1->GetMomentumDirection();
  G4double kinEnergyPost = point2->GetKineticEnergy();
  // G4cout << "Edep (eV) : " << eDep/ eV <<G4endl;

  G4EmCalculator emCalculator;
  G4double massSigma = emCalculator.GetCrossSectionPerVolume(kinEnergyPre, part, limitingProcessName, material)/(1*g/cm3);
  /*if (limitingProcessName == "e-_G4DNAIonisation"){
    G4cout << kinEnergyPre << "  " << massSigma/cm2 << G4endl;
  }*/
  /*if (step->GetPostStepPoint()->GetKineticEnergy() == 0) {
    G4cout << step->GetTrack()->GetVertexKineticEnergy() << "  " << step->GetTrack()->GetTrackLength()/nm << G4endl;
  }*/


    G4int flagParticle, flagProcess;
    // G4ParticleDefinition* part = aTrack->GetDefinition();
    G4double eTrans = (kinEnergyPre - kinEnergyPost);
    if (partName == "e-")                                    {

    flagParticle = 1;}
    else if (partName == "gamma")                            {flagParticle = 7;
       // G4cout <<kinEnergyPre/eV<<G4endl;
    }
    else                                     {flagParticle = 0;} //none of the known particles
    if (limitingProcessName =="e-_G4DNAElastic")                  flagProcess = 11;
    else if (limitingProcessName =="e-_G4DNAExcitation")               flagProcess = 12;
    else if (limitingProcessName =="e-_G4DNAIonisation")               flagProcess = 13;
    else if (limitingProcessName =="e-_G4DNAAttachment")   
            {
                flagProcess = 9;
                if (eTrans==0) //correct DEA bug;
                {eTrans=eDep;}
             }
    else if (limitingProcessName =="e-_G4DNAVibExcitation")            flagProcess = 10;
    else if (limitingProcessName =="UserSpecialCut")   
            {flagProcess = 8;
                if (eTrans==0)
                {eTrans=eDep;}
             }
    else if (limitingProcessName=="phot")                            {flagProcess =30;
      step->GetTrack()->SetTrackStatus(fStopAndKill);
       // G4cout << kinEnergyPre/eV<<G4endl;
    }//);
    else if (limitingProcessName=="compt")                       {flagProcess =31;
      step->GetTrack()->SetTrackStatus(fStopAndKill);//);
      // G4cout << kinEnergyPre/eV<<G4endl;
    }
    else if (limitingProcessName=="conv")                            flagProcess =32;
    else if (limitingProcessName=="Rayl")                            flagProcess =33;
    else flagProcess = 0 ; //none of the known processes
                 
    // G4EmCalculator emCalculator;
    // G4double density = material->GetDensity();
    //   // if (partName =="gamma" && limitingProcessName == "compt"){
    //       // if (partName =="gamma" && limitingProcessName == "Rayl"){
    //       if (partName =="gamma" && limitingProcessName == "phot"){

    //   G4double massSigma = emCalculator.ComputeCrossSectionPerVolume(kinEnergyPre,part,limitingProcessName,material)/density;                     
    //   G4cout << massSigma/(cm*cm/g) << " " << kinEnergyPre/eV << " " << limitingProcessName << G4endl;
    // }

    if (limitingProcessName =="compt" || limitingProcessName =="phot"){ // only one of these
      Run->SetpZeroX(pPost.getX()/nm);
      Run->SetpZeroY(pPost.getY()/nm);
      Run->SetpZeroZ(pPost.getZ()/nm);
      
      // G4cout << initPointX << " " << initPointY << " " << initPointZ << G4endl;

    }
    // G4cout << initPoint;
   float nEv=G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
                    // if (partName == "gamma") {
                    //   G4cout << kinEnergyPre/eV << " "<<flagProcess<< " " << nEv << G4endl;
                    // }
                       
    G4double buff;  
    float buf;
    // G4int dummy = 0;
    // int indint=Run->GetInd();
    // G4ThreeVector pPre = point1->GetPosition();
      buf = nEv;
      track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
    track.write(reinterpret_cast<const char *>(&flagParticle),sizeof(short));
    track.write(reinterpret_cast<const char *>(&flagProcess),sizeof(short));
        buff = pPost.getX()/nm - Run->GetpZeroX();
        buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
      buff = pPost.getY()/nm - Run->GetpZeroY();
      buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
      buff = pPost.getZ()/nm - Run->GetpZeroZ();
        // G4cout << pPost.getZ()/nm << " " <<Run->GetpZeroZ()/nm <<G4endl;
      buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));


          buff = pPre.getX()/nm - Run->GetpZeroX();
          buf = buff;
        track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
          buff = pPre.getY()/nm - Run->GetpZeroY();
          buf = buff;
        track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
          buff = pPre.getZ()/nm - Run->GetpZeroZ();
          buf = buff;
        track.write(reinterpret_cast<const char *>(&buf),sizeof(float));


      buff = kinEnergyPre/eV;
      buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
      buff =eDep/eV;
      buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
      buff = eTrans/eV;
      buf = buff;
    track.write(reinterpret_cast<const char *>(&buf),sizeof(float));
    track.write(reinterpret_cast<const char *>(&trackID),sizeof(short));
    track.write(reinterpret_cast<const char *>(&parentID),sizeof(short));
   
   
  }
}    
