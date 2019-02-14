#ifndef DetectorContruction_h
#define DetectorConstruction_h 1

// inherit from the following
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"

class G4GenericMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    // also define some new members
    DetectorConstruction();
    virtual ~DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    

private:
    G4VPhysicalVolume* ConstructDetector();

    std::vector<G4VisAttributes*> fVisAttributes;

    G4LogicalVolume* fWorldLogical;
    G4LogicalVolume* fTargetLogical;

};
#endif
