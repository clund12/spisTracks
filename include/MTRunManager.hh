#ifndef MTRunManager_h
#define RunAction_h 1

#include "G4MTRunManager.hh"
#include "globals.hh"

class MTRunManager : public G4MTRunManager
{
    public:
        MTRunManager(G4String fileName);
        virtual ~MTRunManager();

//        virtual void Initialize();
//        virtual void BeamOn(G4int n_event);
//        virtual void DefineWorldVolume(G4VPhysicalVolume * worldVol);
//        virtual void AbortRun();

        void SetFileName(G4String fileName) { fFileName = fileName; }

        G4String GetFileName() const { return fFileName; }

//    protected: 
//        virtual void InitializeGeometry();
//        virtual void InitializePhysics();
//        virtual G4bool ConfirmBeamOnCondition();
//        virtual void RunInitialization();
//        virtual void DoEventLoop(G4int n_events);
//        virtual G4Event* GenerateEvent(G4int i_event);
//        virtual void AnalyzeEvent(G4Event* anEvent);
//        virtual void RunTermination();
//        virtual void DefineWorldVolume(G4VPhysicalVolume * worldVol);

    private:
        G4String fFileName;

};

#endif
