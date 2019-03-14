#include "PhysicsList.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmDNAPhysics_option5.hh"
// #include "G4EmDNAPhysics1.hh"
// #include "G4EmDNAPhysics2.hh"

#include "G4UserSpecialCuts.hh"
#include "G4PhysicsListHelper.hh"
#include "G4Electron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhysicsList::PhysicsList(): G4VUserPhysicsList()
{
defaultCutValue = 1*CLHEP::nanometer;
cutForGamma = defaultCutValue;
cutForElectron = defaultCutValue;
cutForPositron = defaultCutValue;

// these cuts are ignored since all Geant4-DNA processes are discrete

emPhysicsList = new G4EmDNAPhysics_option5();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

PhysicsList::~PhysicsList()
{
delete emPhysicsList;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhysicsList::ConstructParticle()
{
emPhysicsList->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhysicsList::ConstructProcess()
{
AddTransportation();
emPhysicsList->ConstructProcess();
G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
ph->RegisterProcess(new G4UserSpecialCuts(),G4Electron::ElectronDefinition()); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void PhysicsList::SetCuts()
{
SetCutValue(cutForGamma, "gamma");
SetCutValue(cutForElectron, "e-");
SetCutValue(cutForPositron, "e+");
}
