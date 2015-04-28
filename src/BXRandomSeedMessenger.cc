//See BXRandomSeedMessenger.hh

#include "BXRandomSeedMessenger.hh"

//CLHEP random number generation
#include "Randomize.hh"

//constructor: sets up options
BXRandomSeedMessenger::BXRandomSeedMessenger()
{
	//sets the seed for the random number generator
	seed = new G4UIcmdWithAnInteger("/random/setTheSeed",this);
	seed->SetGuidance("Reinitializes the generator with a seed.");
	seed->SetGuidance("Allows a macro script to set the random number");
	seed->SetGuidance("generator's seed and reinitializes the generator.");
	seed->SetParameterName("seed",false);
	seed->AvailableForStates(G4State_PreInit,G4State_Idle);

	return;
}

//destructor: frees memory
BXRandomSeedMessenger::~BXRandomSeedMessenger()
{
	delete seed;

	return;
}
	

//does all the hard work and executes commands
void BXRandomSeedMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

	//sets the new seed from the input
	if(command == seed) { HepRandom::setTheSeed( seed->GetNewIntValue(newValue) ); }
	
	return;
}

//EOF BXRandomSeedMessenger.cc
