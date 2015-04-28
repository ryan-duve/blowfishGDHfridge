//see BXRunaction.hh for more details

//my includes
#include "BXRunAction.hh"

//CLHEP includes
#include <CLHEP/Random/Randomize.h>

//Geant4 includes
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//G4Lucid includes
#include "G4LucidEvent.hh"
#include "G4LucidLong.hh"
#include "G4LucidFloat.hh"

using namespace std;

//Constructor
BXRunAction::BXRunAction()
{
	//pointer to the Lucid object
	lucidPtr = G4Lucid::GetLucidPointer();

	//timer setup
	timer = new G4Timer();

	// messenger to allow use to reset seed via a macro
	rsm = new BXRandomSeedMessenger();
}


//Destructor
BXRunAction::~BXRunAction()
{
	delete timer;
	delete rsm;
}


//Code executed at the beginning of a run
void BXRunAction::BeginOfRunAction(const G4Run* aRun)
{
  ifstream runin;
  ofstream runout;
  G4int runno;
  // if the file "flux.runno" exists - use its contents as the lucid run number
  runin.open("blowfish.runno");
  if(runin.good())
  	{
  	runin>>runno;
	runin.close();
	}
  else
  	{
	runno = 0;
	}
  runno++;
  runout.open("blowfish.runno", ios::trunc);
  if(runout.good())
  	{
  	runout << runno << endl;
  	runout.close();
	}
  else
  	{
  	G4cout << "Cannot open blowfish.runno" << G4endl;
	}

	//begins the Lucid Run and clears most of the 'real' events, but not the 'ideal' events

	int seed = time(NULL) + 4668414*runno;
	HepRandom::setTheSeed(seed);
	// should be in constructor?
	// BXRandomSeedMessenger * rsm = new BXRandomSeedMessenger();

	G4cout << "Seed: " << seed << G4endl;

	lucidPtr -> BeginRun( runno );
	lucidPtr->GetLucidEvent("neutron")   ->ForceClear();
	lucidPtr->GetLucidEvent("scalerread")->ForceClear();
	lucidPtr->GetLucidEvent("pedestal")  ->ForceClear();
	lucidPtr->GetLucidEvent("flasher")   ->ForceClear();
	lucidPtr->GetLucidEvent("monitor")   ->ForceClear();
	lucidPtr->GetLucidEvent("flux")      ->ForceClear();
	lucidPtr->GetLucidEvent("paddle")    ->ForceClear();
	lucidPtr->GetLucidEvent("goodbye")   ->ForceClear();
	G4cout << "Lucid Run " << lucidPtr->GetRunNumber() << " started." << G4endl;

	//writes ideal startup Lucid event
	G4LucidEvent * startup = lucidPtr->GetLucidEvent("ideal_startup");
	startup->GetLucidLong("g4_run_no")->Set( aRun->GetRunID() );
	startup->GetLucidLong("lucid_run_no")->Set( runno );
	startup->GetLucidLong("rand_seed")->Set( HepRandom::getTheSeed() ); //gets the random seed from CLHEP
	startup->WriteEvent();

	//writes actual startup Lucid event
	lucidPtr->GetLucidEvent("startup")->WriteEvent();

	//writes a scallread event
	G4LucidEvent * scalerread = lucidPtr->GetLucidEvent("scalerread");
	scalerread->GetLucidLong("count_scalerread")->Increment();
	scalerread->WriteEventClear();

	//start your engines! (and the timer)
	timer->Start();

	return;

}

//Code executed at the end of a run
void BXRunAction::EndOfRunAction(const G4Run*)
{
	//stop the timer
	timer->Stop();

	//writes a scallread event
	G4LucidEvent * scalerread = lucidPtr->GetLucidEvent("scalerread");
	scalerread->GetLucidLong("count_scalerread")->Increment();
	scalerread->WriteEventClear();

	//writes actual goodbye Lucid event
	lucidPtr->GetLucidEvent("goodbye")->WriteEvent();

	//gets the time spent on the run and writes it to Lucid through the ideal windup event
	G4LucidEvent * windup = lucidPtr->GetLucidEvent("ideal_windup");
	windup->GetLucidFloat("time_real_s")  ->Set( timer->GetRealElapsed() );
	windup->GetLucidFloat("time_system_s")->Set( timer->GetSystemElapsed() );
	windup->GetLucidFloat("time_user_s")  ->Set( timer->GetUserElapsed() );
	windup->WriteEventClear();

	//ends the Lucid Run
	G4int lucidRunNo = lucidPtr->GetRunNumber();
	lucidPtr->EndRun();
	G4cout << "Lucid Run " << lucidRunNo << " ended." << G4endl;
}


//EOF BXRunAction.cc
