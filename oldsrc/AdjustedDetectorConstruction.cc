#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
//#include "G4ProductionCuts.hh"
#include "G4Orb.hh"


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

  fpWaterMaterial = H2O;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{
  G4double worldSize = 40*km;

  G4Orb* solidWorld = new G4Orb(
          "World",
          worldSize
          );

  G4LogicalVolume* logicWorld = new G4LogicalVolume(
          solidWorld,
          fpWaterMaterial,
          "World"
          );

  G4PVPlacement* physiWorld = new G4PVPlacement(
          0,
          G4ThreeVector(),
          "World",
          logicWorld,
          0,
          false,
          0
          );

//  G4ProductionCuts* cuts = new G4ProductionCuts();
//
//  // come back to this
//  G4double defCut = 1*nanometer;
//  cuts->SetProductionCut(defCut,"gamma");
//  cuts->SetProductionCut(defCut,"e-");
//  cuts->SetProductionCut(defCut,"e+");
//  cuts->SetProductionCut(defCut,"proton");

  G4Orb* targetSolid1 = new G4Orb(
          "Target", 
          worldSize
          );

  G4LogicalVolume* logicTarget1 = new G4LogicalVolume(
          targetSolid1,
          fpWaterMaterial,
          "Target"
          );
  
  new G4PVPlacement(
          0, 
          G4ThreeVector(),
          "Target",
          logicTarget1, 
          physiWorld,
          false, 
          0
          );

  fpRegion = new G4Region("Target");
  fpRegion->SetProductionCuts(cuts);
  fpRegion->AddRootLogicalVolume(logicTarget1);

  // Visualization attributes
  G4VisAttributes* worldVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
  worldVisAtt->SetVisibility(true);
  logicWorld->SetVisAttributes(worldVisAtt);
  logicWorld->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,7.4*eV));

  G4VisAttributes* worldVisAtt1 = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  worldVisAtt1->SetVisibility(true);
  logicTarget1->SetVisAttributes(worldVisAtt);
  logicTarget1->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,DBL_MAX,7.4*eV));

  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMaterial(G4String mat)
{
  // Search the material by its name   
  G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(
      mat
      );

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
