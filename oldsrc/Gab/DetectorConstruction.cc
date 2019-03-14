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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ProductionCuts.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction(), fpWaterMaterial(0)
{
  // create commands for interactive definition of the detector  
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstruction::~DetectorConstruction()
{
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4VPhysicalVolume* DetectorConstruction::Construct()

{
  DefineMaterials();
  return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstruction::DefineMaterials()
{

  // Water is defined from NIST material database
  G4NistManager * man = G4NistManager::Instance();

  G4Material * H2O = man->FindOrBuildMaterial("G4_WATER");

  /*
   If one wishes to test other density value for water material,
   one should use instead:
   G4Material * H2O = man->BuildMaterialWithNewDensity("G4_WATER_MODIFIED",
   "G4_WATER",1.100*g/cm3);

   Note: any string for "G4_WATER_MODIFIED" parameter is accepted
   and "G4_WATER" parameter should not be changed
   Both materials are created and can be selected from dna.mac
   */
  fpWaterMaterial = H2O;

  //G4cout << "-> Density of water material (g/cm3)="
  // << fpWaterMaterial->GetDensity()/(g/cm/cm/cm) << G4endl;

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

  // WORLD VOLUME

  //  G4double worldSizeX = 20 * cm;
  // // G4double worldSizeX = 1 * meter;
  // G4double worldSizeY = worldSizeX;
  // G4double worldSizeZ = worldSizeX;
    //(10 + 3 * 2) * micrometer;

  G4Sphere* solidWorld = new G4Sphere("World", 0*cm, 40*km, 0.*deg, 360.*deg, 0.*deg, 180.*deg);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, fpWaterMaterial, "World"); //its name

  G4PVPlacement* physiWorld = new G4PVPlacement(0, //no rotation
      G4ThreeVector(0,0,0), //at (0,0,0)
      "World", //its name
      logicWorld, //its logical volume
      0, //its mother  volume
      false, //no boolean operation
      0); //copy number

  G4ProductionCuts* cuts = new G4ProductionCuts();

  G4double defCut = 1*nanometer;
  cuts->SetProductionCut(defCut,"gamma");
  cuts->SetProductionCut(defCut,"e-");
  cuts->SetProductionCut(defCut,"e+");
  cuts->SetProductionCut(defCut,"proton");



  // G4double slabthickness = 1*cm;

  // // shells at  1.5 , 3 , 5 ,7, 10, 12,
  // // G4double TargetSizeXY = 1*cm;
  // //1
  G4Sphere* targetSolid1 = new G4Sphere("Target", 0*cm, 40*km,0.*deg,360.*deg,0.*deg,180.*deg);  //its size
  G4LogicalVolume* logicTarget1 = new G4LogicalVolume(targetSolid1, fpWaterMaterial, "Target");    //its name
  new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target", logicTarget1, physiWorld, false, 0);           //copy number
  fpRegion1 = new G4Region("Target");
  fpRegion1->SetProductionCuts(cuts);
  fpRegion1->AddRootLogicalVolume(logicTarget1);

  //  //2
  // G4Sphere* targetSolid2 = new G4Sphere("Target2", 2.5*cm, 3.5*cm,0.*deg,360.*deg,0.*deg,180.*deg); 
  // G4LogicalVolume* logicTarget2 = new G4LogicalVolume(targetSolid2, fpWaterMaterial, "Target2");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target1", logicTarget1, physiWorld, false, 0);           //copy number
  // fpRegion2 = new G4Region("Target2");
  // fpRegion2->SetProductionCuts(cuts);
  // fpRegion2->AddRootLogicalVolume(logicTarget2);

  //  //3
  // G4Sphere* targetSolid3 = new G4Sphere("Target3", 4.5*cm, 5.5*cm,0.*deg,360.*deg,0.*deg,180.*deg); 
  // G4LogicalVolume* logicTarget3 = new G4LogicalVolume(targetSolid3, fpWaterMaterial, "Target3");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target3", logicTarget3, physiWorld, false, 0);           //copy number
  // fpRegion3 = new G4Region("Target3");
  // fpRegion3->SetProductionCuts(cuts);
  // fpRegion3->AddRootLogicalVolume(logicTarget3);

  //  //4
  // G4Sphere* targetSolid4 = new G4Sphere("Target4", 6.5*cm, 7.5*cm,0.*deg,360.*deg,0.*deg,180.*deg); 
  // G4LogicalVolume* logicTarget4 = new G4LogicalVolume(targetSolid4, fpWaterMaterial, "Target4");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target4", logicTarget4, physiWorld, false, 0);           //copy number
  // fpRegion4 = new G4Region("Target4");
  // fpRegion4->SetProductionCuts(cuts);
  // fpRegion4->AddRootLogicalVolume(logicTarget4);

  //  //5
  // G4Sphere* targetSolid5 = new G4Sphere("Target5", 9.5*cm, 10.5*cm,0.*deg,360.*deg,0.*deg,180.*deg);    //its size
  // G4LogicalVolume* logicTarget5 = new G4LogicalVolume(targetSolid5, fpWaterMaterial, "Target5");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target5", logicTarget5, physiWorld, false, 0);           //copy number
  // fpRegion5 = new G4Region("Target5");
  // fpRegion5->SetProductionCuts(cuts);
  // fpRegion5->AddRootLogicalVolume(logicTarget5);

  //  //6
  // G4Sphere* targetSolid6 = new G4Sphere("Target6", 11.5*cm, 12.5*cm,0.*deg,360.*deg,0.*deg,180.*deg);    //its size
  // G4LogicalVolume* logicTarget6 = new G4LogicalVolume(targetSolid6, fpWaterMaterial, "Target6");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target6", logicTarget6, physiWorld, false, 0);           //copy number
  // fpRegion6 = new G4Region("Target6");
  // fpRegion6->SetProductionCuts(cuts);
  // fpRegion6->AddRootLogicalVolume(logicTarget6);

  //  //7
  // G4Sphere* targetSolid7 = new G4Sphere("Target7", 13.5*cm, 14.5*cm,0.*deg,360.*deg,0.*deg,180.*deg); //its size
  // G4LogicalVolume* logicTarget7 = new G4LogicalVolume(targetSolid7, fpWaterMaterial, "Target7");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target7", logicTarget7, physiWorld, false, 0);           //copy number
  // fpRegion7 = new G4Region("Target7");
  // fpRegion7->SetProductionCuts(cuts);
  // fpRegion7->AddRootLogicalVolume(logicTarget7);

  //  //8
  // G4Sphere* targetSolid8 = new G4Sphere("Target8", 19.5*cm, 20.5*cm,0.*deg,360.*deg,0.*deg,180.*deg);    //its size
  // G4LogicalVolume* logicTarget8 = new G4LogicalVolume(targetSolid8, fpWaterMaterial, "Target8");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target8", logicTarget8, physiWorld, false, 0);           //copy number
  // fpRegion8 = new G4Region("Target8");
  // fpRegion8->SetProductionCuts(cuts);
  // fpRegion8->AddRootLogicalVolume(logicTarget8);

  //  //9
  // G4Sphere* targetSolid9 = new G4Sphere("Target9", 29.5*cm, 30.5*cm,0.*deg,360.*deg,0.*deg,180.*deg);    //its size
  // G4LogicalVolume* logicTarget9 = new G4LogicalVolume(targetSolid9, fpWaterMaterial, "Target9");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target9", logicTarget9, physiWorld, false, 0);           //copy number
  // fpRegion9 = new G4Region("Target9");
  // fpRegion9->SetProductionCuts(cuts);
  // fpRegion9->AddRootLogicalVolume(logicTarget9);

  // //9=10
  // G4Sphere* targetSolid10 = new G4Sphere("Target10", 35.5*cm, 36.5*cm,0.*deg,360.*deg,0.*deg,180.*deg); //its size
  // G4LogicalVolume* logicTarget10 = new G4LogicalVolume(targetSolid10, fpWaterMaterial, "Target10");    //its name
  // new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), "Target10", logicTarget10, physiWorld, false, 0);           //copy number
  // fpRegion10 = new G4Region("Target10");
  // fpRegion10->SetProductionCuts(cuts);
  // fpRegion10->AddRootLogicalVolume(logicTarget10);

  // Visualization attributes
  G4VisAttributes* worldVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); //White
  worldVisAtt->SetVisibility(true);
  logicWorld->SetVisAttributes(worldVisAtt);
  logicWorld->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,9*eV));

  G4VisAttributes* worldVisAtt1 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  worldVisAtt1->SetVisibility(true);
  logicTarget1->SetVisAttributes(worldVisAtt);
  logicTarget1->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,9*eV));

  // 
  // Shows how to introduce a 20 eV tracking cut
  //
  //logicWorld->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,20*eV));


  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMaterial(G4String materialChoice)
{
  // Search the material by its name   
  G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(
      materialChoice);

  if (pttoMaterial)
  {
    fpWaterMaterial = pttoMaterial;
    G4LogicalVolume* logicWorld =
        G4LogicalVolumeStore::GetInstance()->GetVolume("World");
    logicWorld->SetMaterial(fpWaterMaterial);
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());
}
