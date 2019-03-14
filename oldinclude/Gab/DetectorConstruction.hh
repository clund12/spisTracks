#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

class G4Region;
class DetectorMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();

  virtual ~DetectorConstruction();
  virtual G4VPhysicalVolume* Construct();

  void SetMaterial(G4String);
  void UpdateGeometry();

private:
  G4Region*          fpRegion1;
  G4Material* fpWaterMaterial;

  void DefineMaterials();

  G4VPhysicalVolume* ConstructDetector();
  DetectorMessenger* fDetectorMessenger;

};
#endif
