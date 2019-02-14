// User defined
#include "DetectorConstruction.hh"
#include "TrackSD.hh"

// Geant4
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProductionCuts.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"

// Physical and Logical volume classes always necessary
#include "G4Orb.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"

// For sensitive detector definition and assignment of scorers to it
#include "G4SDManager.hh" 
#include "G4VSensitiveDetector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction() // initialize
{
}                               

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// don't need destructor to do anything
DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// this method simply returns the result of the ContructDetector method
G4VPhysicalVolume* DetectorConstruction::Construct() // always use pointers
{
  return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// this method is to define the geometries
G4VPhysicalVolume* DetectorConstruction::ConstructDetector()
{

    // water is defined from the NIST material database
    G4NistManager* man = G4NistManager::Instance();
    G4Material* water = man->FindOrBuildMaterial("G4_WATER");    

/* *************************************************************************************************
* World and semi-infinite water phantom
* ********************************************************************************************** */

    G4double worldRadius = 40.*km;
    
    // define solid volume
    G4Orb* solidWorld = new G4Orb( 
            "World",    // its name
            worldRadius // its radius
            );

    // define a logical volume using the solid volume
    fWorldLogical =
        new G4LogicalVolume(
                solidWorld,              // its solid
                water,                   // its material
                "World"                  // its name
                );

    // place the logical volume within the world
    G4VPhysicalVolume* physiWorld = 
        new G4PVPlacement(0,      // no rotation
                G4ThreeVector(),  // at origin
                "World",          // its name 
                fWorldLogical,    // its logical volume
                0,                // its mother volume (the world)
                false,            // no boolean operations
                0                 // copy number - no copies
                );

    // define target to assign the sensitive detector to
    G4Orb* solidTarget = new G4Orb(
            "Target",
            worldRadius
            );

    fTargetLogical = new G4LogicalVolume(
            solidTarget,
            water,
            "Target"
            );

    new G4PVPlacement(
            0,
            G4ThreeVector(),
            "Target",
            fTargetLogical,
            physiWorld,
            false,
            0
            );

/* *************************************************************************************************
* VISUALIZATION COLOURS
* ********************************************************************************************** */

    G4VisAttributes* visAttributes = 
        new G4VisAttributes(true, G4Colour(1.0, 1.0, 1.0, 0.1));
    fWorldLogical->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);

    visAttributes =
        new G4VisAttributes(true, G4Colour(0.0, 0.4, 0.8, 0.2));
   fTargetLogical->SetVisAttributes(visAttributes);
   fVisAttributes.push_back(visAttributes);


    return physiWorld;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer(); 
  SDman->SetVerboseLevel(0);
  G4String SDname;

  G4VSensitiveDetector* trackSD = new TrackSD(SDname="/track");
  SDman->AddNewDetector(trackSD);
  fTargetLogical->SetSensitiveDetector(trackSD);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
