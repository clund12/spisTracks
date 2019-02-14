#include "NullSession.hh"
#include "G4UImanager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NullSession::NullSession()
{
    G4String toNull;
    toNull = "/dev/null";
//	outFile = ofstream(toNull);
//	errFile = ofstream(toNull);
	outFile.open(toNull);
	errFile.open(toNull);
	G4UImanager* UI = G4UImanager::GetUIpointer();
	UI->SetCoutDestination(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NullSession::~NullSession()
{
	outFile.close();
	errFile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4UIsession* NullSession::SessionStart()
{
	return NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int NullSession::ReceiveG4cout(G4String output)
{
	outFile<<output;
	outFile.flush();
	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int NullSession::ReceiveG4cerr(G4String err)
{
	errFile<<err;
	errFile.flush();
	return 0;
}
