#ifndef PhysicsList_h
#define PhysicsList_h 

#include "G4VUserPhysicsList.hh"

class G4VPhysicsConstructor;

class PhysicsList: public G4VUserPhysicsList
{
public:

PhysicsList();
~PhysicsList();

void SetCuts();
void ConstructParticle();
void ConstructProcess();

private:

G4double cutForGamma;
G4double cutForElectron;
G4double cutForPositron;

G4VPhysicsConstructor* emPhysicsList;

};
#endif
