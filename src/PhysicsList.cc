#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4EmDNAPhysics.hh"
//#include "G4EmDNAPhysics_option4.hh"
#include "G4EmDNAPhysics_option4_Modded.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{

    G4int verbosity = 0;
    SetVerboseLevel(verbosity);

    // default production thresholds for the world volume
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(7.4*eV, 1*GeV);

//    RegisterPhysics(new G4EmDNAPhysics_option4());
    RegisterPhysics(new G4EmDNAPhysics_option4_Modded(verbosity));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
