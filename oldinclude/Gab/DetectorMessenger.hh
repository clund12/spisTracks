#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction*);
    virtual ~DetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction*      fpDetector;
    G4UIcmdWithAString*        fpMaterCmd;
    G4UIcmdWithoutParameter*   fpUpdateCmd;
};

#endif

