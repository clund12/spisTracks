#ifndef NullSession_hh
#define NullSession_hh

#include "G4UIsession.hh"
#include <iostream>
#include <fstream>

using namespace std;

class NullSession : public G4UIsession {

public:
	NullSession();
	~NullSession();

	G4UIsession* SessionStart();
	G4int ReceiveG4cout(G4String);
	G4int ReceiveG4cerr(G4String);

private:
	ofstream outFile;
	ofstream errFile;
};

#endif 
