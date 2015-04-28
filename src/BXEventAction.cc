//See BXEventAction.hh
 
//my includes
#include "BXEventAction.hh"
#include "BXCellHit.hh"
#include "BXLucid.hh"

//geant4 includes
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4ThreeVector.hh"

//CHLEP includes
#include <CLHEP/Random/Randomize.h>

//Lucid includes
#include "G4Lucid.hh"
#include "G4LucidEvent.hh"
#include "G4LucidV792.hh"
#include "G4LucidV775.hh"
#include "G4LucidLong.hh"
#include "G4LucidFloat.hh"

//C includes
#include <string.h>
#include <stdlib.h>

//C++ includes
#include <fstream>
using namespace std;

//these token delimiters should be available to all functions in this file
static const char tokenDelim[] = " []=\t\n";

//Constructor
BXEventAction::BXEventAction()
{
	//Gets a pointer to the Lucid object
	lucidPtr = G4Lucid::GetLucidPointer();

	neutronEvt = lucidPtr->GetLucidEvent("neutron");
	pedestalEvt = lucidPtr->GetLucidEvent("pedestal");
	scalerreadEvt = lucidPtr->GetLucidEvent("scalerread");
	vmeadc_l[0] = neutronEvt->GetLucidV792("vmeadc_l_1");
	vmeadc_s[0] = neutronEvt->GetLucidV792("vmeadc_s_1");
	vmeadc_l[1] = neutronEvt->GetLucidV792("vmeadc_l_2");
	vmeadc_s[1] = neutronEvt->GetLucidV792("vmeadc_s_2");
	vmeadc_l[2] = neutronEvt->GetLucidV792("vmeadc_l_3");
	vmeadc_s[2] = neutronEvt->GetLucidV792("vmeadc_s_3");
	vmetdc[0] = neutronEvt->GetLucidV775("vmetdc_1");
	vmetdc[1] = neutronEvt->GetLucidV775("vmetdc_2");
	vmetdc[2] = neutronEvt->GetLucidV775("vmetdc_3");
	vmeadc_ig = neutronEvt->GetLucidV792("vmeadc_ig");
	cellScaler[0] = scalerreadEvt->GetLucidLong("cell_scaler1");
	cellScaler[1] = scalerreadEvt->GetLucidLong("cell_scaler2");
	cellScaler[2] = scalerreadEvt->GetLucidLong("cell_scaler3");
	scaler[0] = scalerreadEvt->GetLucidLong("scaler1");
	scaler[1] = scalerreadEvt->GetLucidLong("scaler2");
	scaler[2] = scalerreadEvt->GetLucidLong("scaler3");
	count_neutron = scalerreadEvt->GetLucidLong("count_neutron");
	count_pedestal = scalerreadEvt->GetLucidLong("count_pedestal");
	count_scalerread = scalerreadEvt->GetLucidLong("count_scalerread");

	//Setup the ideal events that produce data not available from the real Blowfish
	neutronIdeal = lucidPtr->GetLucidEvent("ideal_neutron");
	
	//Stores ideal information that we will not need until the end of the run
	windupIdeal = lucidPtr->GetLucidEvent("ideal_windup");
	geantinoHits = windupIdeal->GetLucidLong("geantino_hits");
	
	//These values were chosen to accurately simulate the neutron cells
	//Notice that light output is expressed in terms of keVee but since
	//Geant4 does not support this unit, we simply use keV.  There is a distinction
	//as keVee is a unit of detector responce and keV is a unit of energy.
	//TODO: Cite paper here
	sigmaLightStatistical = 77.0*keV;
	sigmaLightNoise = 5.0*keV;
	
	//Set all hardware thresholds to the same value
	for(G4int jj = 0; jj < numbCells; jj++)
	{
		hardwareThreshold[jj] = 40.0*keV;
	}

	//Try to get the cell map from the file
	ReadCellMap();
	
	//A class used to perform 'monitor' and 'flasher' events
	fGainMonitor = new BXGainMonitor(ADC_cell_to_mod,ADC_cell_to_chan,numbCells);
}

//Destructor
BXEventAction::~BXEventAction()
{
	delete fGainMonitor;
}

//Reads the cell map file into memory
void BXEventAction::ReadCellMap(void)
{
	//Initialize the arrays for safety
	for(G4int ii = 0; ii < numbCells; ii++){
		ADC_cell_to_mod [ii] = 1;
		ADC_cell_to_chan[ii] = 0;
		TDC_cell_to_mod [ii] = 1; 
		TDC_cell_to_chan[ii] = 0;
		SCA_cell_to_mod [ii] = 1; 
		SCA_cell_to_chan[ii] = 0;}

	//Get the mappings from VME channels to Cells
	if(!getenv("CellMapFile"))
		{
		G4Exception("EventAction::ReadCellMap","Fatal", FatalException,
		"Please setenv CellMapFile to point to the cell map file.\n");
		//G4Exception("Please setenv CellMapFile to point to the cell map file.");
		//G4Exception("Exiting...");
		}
	G4String cellfile = getenv("CellMapFile");

	ifstream fp(cellfile.c_str(), ios::in); //open file for reading
	if(fp.fail()) //if we were unable to open the file
	{
		G4cerr << "EventAction::ReadCellMap() -> ERROR: Unable to open cell map file: " << cellfile << G4endl;
		//G4Exception("Exiting...");
		G4Exception("EventAction::ReadCellMap","Fatal", FatalException, "Exiting...\n");
	}
	else //we were able to open file
	{
		G4cout << "EventAction::ReadCellMap() -> Reading from cell map file: " << cellfile << G4endl;
		char line[1024];	//A line of the file
		char * firstToken;	//A pointer to the first token

		while( !fp.eof() ) //loop until there is no more data
		{
			fp.getline(line,sizeof(line));

			firstToken = strtok(line,tokenDelim); 
			if(firstToken == NULL){ continue; }
			
			//Use the first token to decide what type of information is contained in this line
			//Then use a helper function to decode the rest of the line
			if     ( strcmp(firstToken,"ADC_Cell_to_mod") == 0) {CellMapHelper(ADC_cell_to_mod ,1,3);}
			else if( strcmp(firstToken,"ADC_Cell_to_chan") == 0){CellMapHelper(ADC_cell_to_chan,0,31);}
			else if( strcmp(firstToken,"TDC_Cell_to_mod") == 0) {CellMapHelper(TDC_cell_to_mod ,1,3);}
			else if( strcmp(firstToken,"TDC_Cell_to_chan") == 0){CellMapHelper(TDC_cell_to_chan,0,31);}
			else if( strcmp(firstToken,"SCA_Cell_to_mod") == 0) {CellMapHelper(SCA_cell_to_mod ,1,3);}
			else if( strcmp(firstToken,"SCA_Cell_to_chan") == 0){CellMapHelper(SCA_cell_to_chan,0,31);}

		}	

		//Change the module numbers form [1,3] to [0,2]
		for(G4int ii = 0; ii < numbCells; ii++){
			ADC_cell_to_mod[ii] --;
			TDC_cell_to_mod[ii] --; 
			SCA_cell_to_mod[ii] --; }

	}
		
	fp.close();
}

//Helps ReadCellMap()
void BXEventAction::CellMapHelper(G4int * array, G4int min, G4int max)
{
	char * tokenString;
	
	//Get the next token and ensure it is valid
	tokenString = strtok(NULL,tokenDelim); 
	if(tokenString == NULL){ return; }

	G4int cellNumb = strtol(tokenString,NULL,0); // convert the string to a number
	if(cellNumb < 1 || cellNumb > numbCells) { return;} //cell number must be valid
	cellNumb --; //now is 0 to 87

	//Get the next token and ensure it is valid
	tokenString = strtok(NULL,tokenDelim); 
	if(tokenString == NULL){ return; }

	G4int valueNumber = strtol(tokenString,NULL,0); // convert the string to a number
	if(valueNumber < min || valueNumber > max){ return; } //must be in the specified range

	//we now put the data in the array
	array[cellNumb] = valueNumber;
}

//Performs a pedestal event
void BXEventAction::PedestalEvent(void)
{
	vmeadc_l[0]->SetZeroSuppression(false);
	vmeadc_l[1]->SetZeroSuppression(false);
	vmeadc_l[2]->SetZeroSuppression(false);
	vmeadc_s[0]->SetZeroSuppression(false);
	vmeadc_s[1]->SetZeroSuppression(false);
	vmeadc_s[2]->SetZeroSuppression(false);
	vmeadc_ig->SetZeroSuppression(false);

	count_pedestal->Increment();
	pedestalEvt->WriteEvent();
	
	vmeadc_l[0]->SetZeroSuppression(true);
	vmeadc_l[1]->SetZeroSuppression(true);
	vmeadc_l[2]->SetZeroSuppression(true);
	vmeadc_s[0]->SetZeroSuppression(true);
	vmeadc_s[1]->SetZeroSuppression(true);
	vmeadc_s[2]->SetZeroSuppression(true);
	vmeadc_ig->SetZeroSuppression(true);
}

//Code run at the beginning of an event 
void BXEventAction::BeginOfEventAction(const G4Event* evt)
{
	//display interval is static so that it keeps its value after function returns
	static G4int displayInterval = 1000;

	//prints the event number and outputs pedestals at regular intervals
	G4int eventNo = evt->GetEventID();
	if(eventNo%displayInterval == 0)
	{
		if(eventNo > 0)
		{
			G4cout << " G4Event number " << eventNo << G4endl; 
			if(eventNo >= 100000){ displayInterval = 100000; }
			else if(eventNo >= 10000){ displayInterval = 10000;}
		}

		PedestalEvent();
	}
	
	//Increment the timer.  This gives us an event rate of 1 Hz
	//Notice that since a Geant4 simulation has no dead time, we
	//increment both the real and live time scalers here.
	scaler[0]->Increment(BXLucid::scalerTimerCh);
	scaler[1]->Increment(BXLucid::scalerTimerCh);

	//We perform a scaler read every '2 seconds' according to
	//the scaler timer.  This is the same as the real Blowfish
	if(scaler[0]->Get(BXLucid::scalerTimerCh) >= 2000)
	{
		count_scalerread->Increment();
		scalerreadEvt->WriteEventClear();
	}
	
	//Write a flasher and monitor event on a regular basis
	const G4int flasherInterval = 100;
	if(eventNo%flasherInterval == 0){
		fGainMonitor->FlasherEvent(); 
		fGainMonitor->MonitorEvent();}
	
	
	return;
}

//Run at the end of an event
void BXEventAction::EndOfEventAction(const G4Event* evt)
{	

	//gets the hit collectors for the neutron cells detector so that we can extract hits from them.
	G4int CHCID = G4SDManager::GetSDMpointer()->GetCollectionID("Cell/HitCollection");
	BXCellHitsCollection * cellHitsCollection = (BXCellHitsCollection *) (evt->GetHCofThisEvent()->GetHC(CHCID));
	G4int cnHit = cellHitsCollection->entries();
	BXCellHit * aHit; //used to iterate through cellHitsCollection
	
	//If no particles entered a detector, we should return
	if(cnHit == 0){ return; }
	
	//Debugging code that can be turned on or off
	#if 0
	G4cout << "---------------------------------------\n";
	cellHitsCollection->PrintAllHits();
	#endif

	//Get the energy deposited and light output for each cell
	//We examine all of the hits individually and add up the energy
	//This allows us to do almost all of the analysis here, instead of
	//doing it in the sensitive detector.
	G4double energyDeposited[numbCells];
	G4double lightOutput[numbCells];
	G4double shortADCresponse[numbCells];
	G4double hitTime[numbCells];
	//G4int arm, ring, cell;
	G4int cell;
	for(G4int jj = 0; jj < numbCells; jj++){ //zero all of the arrays
		energyDeposited[jj] = lightOutput[jj] = shortADCresponse[jj] = hitTime[jj] = 0.0; }
	for(G4int jj = 0; jj < cnHit; jj++) //for all hits
	{
		aHit = (*cellHitsCollection)[jj];
		//arm  = aHit->GetArmNumber();
		//ring = aHit->GetRingNumber();
		//cell = 8*ring + arm;
		cell = aHit->GetCellNumber();

		//We take special action if a geantino hits, as this means the user is doing
		//ray tracing for measuring solid angle, etc.
		if(aHit->GetParticle() == "geantino")
		{
			geantinoHits->Increment(cell);
			continue;
		}
		
		//Fill the arrays with the deposited energy and light output
		energyDeposited[cell]  += aHit->GetEnergyDeposited();
		lightOutput[cell]      += aHit->GetLightOutput();
		shortADCresponse[cell] += ComputeShortADC(aHit->GetLightOutput(), aHit->GetParticle());

		//Compute the approximate time of the hit
		//Assumes that hitsCollection is sorted, which may not be true (TODO: sort hits collection)
		if(lightOutput[cell] >= hardwareThreshold[cell] && hitTime[cell] == 0)
		{
			//average time durring the step
			hitTime[cell] = aHit->GetInitTime()+aHit->GetDeltaTime()/2.0;
		}
	}

	//Perform light output smearing on all of the cells and check to see if there is still a hit
	//Smearing of light output simumlates detector characteristics
	G4double lightOutSmear;
	G4bool hitOccured = false;
	for(cell = 0; cell < numbCells; cell++)
	{
		if(lightOutput[cell] == 0){ continue; } //Proceed only if there was light output
		
		//Units are carried by sigmaLightStatistical and sigmaLightNoise
		//Statistical -- proportional to sqrt(light_output)
  		lightOutSmear = (sqrt(lightOutput[cell]/MeV)) * RandGauss::shoot(0.0, sigmaLightStatistical);
		//Noise -- constant contribution
		lightOutSmear += RandGauss::shoot(0.0, sigmaLightNoise);
		lightOutput[cell] += lightOutSmear;
		if(lightOutput[cell] < 0.0){ lightOutput[cell] = 0.0; }

		//We smear the short ADC by applying the same smear fator as above
		//since short and long ADC measure the same pulse, only over different time scales
		//TODO: Do we need to multiply by a number, such as 0.8
		shortADCresponse[cell] += lightOutSmear;
		if(shortADCresponse[cell] < 0){ shortADCresponse[cell] = 0.0; }
		
		//We check to see if a hit has occured after light output smearing
		if(lightOutput[cell] >= hardwareThreshold[cell])
		{
			hitOccured = true;
		}
		else
		{
			//With light output smearing, there is no hit on this cell
			hitTime[cell] = 0.0;
		}
	}

	//If no hit occured, then we do not take any action
	if(hitOccured == false){ return; }

	//Set common start to the TDCs
	vmetdc[0]->SetCommonStartTime(0.0);
	vmetdc[1]->SetCommonStartTime(0.0);
	vmetdc[2]->SetCommonStartTime(0.0);

	//Fill all of the ADCs and TDCs and increment the scalers
	for(G4int jj = 0; jj < numbCells; jj++)
	{
		vmeadc_l[ADC_cell_to_mod[jj]]->SetQDC( lightOutput[jj],     ADC_cell_to_chan[jj]);
		vmeadc_s[ADC_cell_to_mod[jj]]->SetQDC( shortADCresponse[jj],ADC_cell_to_chan[jj]);
		vmetdc  [TDC_cell_to_mod[jj]]->SetStopTime(hitTime[jj],     TDC_cell_to_chan[jj]);

		//Increment the cell scalers if there was a hit
		if( hitTime[jj] > 0.0)
		{
			cellScaler[SCA_cell_to_mod[jj]]->Increment(SCA_cell_to_chan[jj]);
		}
	}

	//Incremement the appropriate counter, write the event and clear the VME modules only
	count_neutron->Increment();
	neutronEvt->WriteEventClear();

	//Write the ideal variables
	neutronIdeal->WriteEventClear();
	
	return;
	
}//end of EndOfEventAction()


//Computes the short gate ADC based on the long gate and PSD parameter
G4double BXEventAction::ComputeShortADC(G4double lightOutput, G4String particle)
{
	if(lightOutput <=0.0){ return 0.0;} //no light output, no short ADC
	
	if(particle == "e-" || particle == "e+")
	{
		//See page 102 of Ward Wurtz's logbook for 2 May 2006
		return 0.882*lightOutput;
	}
	else// if the particle is a proton or ion
	{
		//See page 154 of Ward Wurtz's logbook for 4 Dec 2008
		if(lightOutput < 300.0*keV)
		{
			return 0.772*lightOutput;
		}
		else //lightOutput >= 300 keVee
		{
			return 0.826*lightOutput - 13.0*keV;
		}
	}
}



//end of EventAction.cc
