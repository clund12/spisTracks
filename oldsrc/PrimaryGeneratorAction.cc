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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
// #include "G4Rand.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   particleGun(0)
{
  // G4int n_particle = 1;
  //  fpParticleGun  = new G4ParticleGun(n_particle);
  particleGun  = new G4GeneralParticleSource();
  
  //  fpParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  //  fpParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));

  //  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  //  fpParticleGun->SetParticleDefinition(particle);

   // Energy

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	//  std::vector<float> energies;
 //   energies.push_back(1.0000000e+02);

	//  G4int nEnergies = energies.size();
	// // // G4double aRand = rand() % nEnergies; 
	//  G4double aRand = CLHEP::RandFlat::shootInt(nEnergies);
	// // G4cout << aRand << " ";
	// // G4cout << energies[aRand] << " Energy : ";
	// // G4UniformRand();

	
	// // G4double cumulWeight[] = {0.01, 0.05, 0.1, 0.4 ,1};
	// // std::vector<float> v(cumulWeight,cumulWeight+5);
	// // std::vector<int> myvector (myints,myints+4);
 //  // std::vector<int>::iterator it;
  
 //   	G4double currentEnergy = energies[aRand]*(1*eV);
 //   fpParticleGun->SetParticleEnergy(currentEnergy);
  particleGun->GeneratePrimaryVertex(anEvent);
}
