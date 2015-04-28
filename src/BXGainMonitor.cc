//See BXGainMonitor.hh for more details
#include "BXGainMonitor.hh"

//The spectrum to use for the 'monitor' event.
//This spectrum was obtained from an actual spectrum measured
//for flasher detector 2 of the gain monitoring system.
const G4double BXGainMonitor::monitorEventSpectrum[] = 
{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 7.0, 14.0, 14.0,
14.0, 34.0, 81.0, 139.0, 291.0, 353.0, 511.0, 711.0, 1080.0,
1585.0, 2025.0, 2659.0, 3504.0, 4388.0, 5322.0, 6207.0, 7197.0,
8195.0, 8801.0, 9405.0, 9873.0, 10602.0, 10736.0, 10971.0, 10844.0,
10797.0, 10635.0, 10269.0, 9939.0, 9691.0, 9569.0, 8938.0,
8804.0, 8545.0, 8168.0, 8070.0, 7814.0, 7487.0, 7388.0, 7181.0,
6843.0, 6800.0, 6568.0, 6286.0, 6367.0, 6160.0, 6069.0, 5786.0, 5772.0,
5544.0, 5597.0, 5511.0, 5363.0, 5170.0, 5166.0, 5186.0, 4932.0,
4842.0, 4712.0, 4643.0, 4523.0, 4345.0, 4181.0, 4164.0, 3976.0,
3880.0, 3802.0, 3615.0, 3334.0, 3372.0, 3168.0, 3118.0, 3111.0,
2893.0, 2936.0, 2907.0, 2882.0, 2902.0, 2946.0, 3167.0, 3218.0,
3279.0, 3471.0, 3659.0, 3892.0, 4093.0, 4405.0, 4606.0, 4918.0,
5143.0, 5326.0, 5503.0, 5991.0, 6197.0, 6339.0, 6460.0, 6701.0,
6701.0, 6709.0, 6569.0, 6500.0, 6490.0, 6341.0, 6146.0, 6080.0,
5681.0, 5556.0, 5389.0, 4987.0, 4790.0, 4426.0, 4277.0, 3847.0,
3626.0, 3388.0, 3159.0, 2926.0, 2813.0, 2591.0, 2399.0, 2195.0,
2054.0, 1996.0, 1862.0, 1726.0, 1618.0, 1539.0, 1391.0, 1416.0,
1311.0, 1212.0, 1162.0, 1175.0, 1046.0, 1017.0, 962.0, 943.0,
824.0, 802.0, 766.0, 726.0, 694.0, 631.0, 645.0, 631.0, 566.0,
480.0, 543.0, 434.0, 412.0, 408.0, 405.0, 341.0, 329.0, 313.0,
284.0, 259.0, 256.0, 225.0, 200.0, 172.0, 148.0, 142.0, 123.0,
109.0, 89.0, 80.0, 89.0, 59.0, 65.0, 55.0, 49.0, 59.0, 47.0};
const G4int BXGainMonitor::monitorSpectrumDatapoints = sizeof(monitorEventSpectrum)/sizeof(*monitorEventSpectrum);


//constructor
BXGainMonitor:: BXGainMonitor(G4int ADC_cell_to_mod_in[], G4int ADC_cell_to_chan_in[],G4int numbCells_in)
{
	//Gets a pointer to the Lucid object
	lucidPtr = G4Lucid::GetLucidPointer();

	//Get pointers the needed Lucid events
	monitorEvt = lucidPtr->GetLucidEvent("monitor");
	flasherEvt = lucidPtr->GetLucidEvent("flasher");

	//Get pointers the the needed Lucid variables
	vmeadc_l[0] = flasherEvt->GetLucidV792("vmeadc_l_1");
	vmeadc_s[0] = flasherEvt->GetLucidV792("vmeadc_s_1");
	vmeadc_l[1] = flasherEvt->GetLucidV792("vmeadc_l_2");
	vmeadc_s[1] = flasherEvt->GetLucidV792("vmeadc_s_2");
	vmeadc_l[2] = flasherEvt->GetLucidV792("vmeadc_l_3");
	vmeadc_s[2] = flasherEvt->GetLucidV792("vmeadc_s_3");
	vmeadc_s[2] = flasherEvt->GetLucidV792("vmeadc_s_3");
	vmeadc_ig   = flasherEvt->GetLucidV792("vmeadc_ig");
	countFlasher= flasherEvt->GetLucidLong("count_flasher");
	countMonitor= monitorEvt->GetLucidLong("count_monitor");

	//Save the cell mapping data in global variables
	this->numbCells = numbCells_in;
	this->ADC_cell_to_mod  = new G4int[numbCells];
	this->ADC_cell_to_chan = new G4int[numbCells];
	for(G4int jj = 0; jj < numbCells; jj++)
	{
		this->ADC_cell_to_mod [jj] = ADC_cell_to_mod_in [jj];
		this->ADC_cell_to_chan[jj] = ADC_cell_to_chan_in[jj];
	}

	//Set the number of flashers and create the flasher map
	numbFlashers = 4;
	flasher_to_chan = new G4int[numbFlashers];
	flasher_to_chan[0] = 0;
	flasher_to_chan[1] = 1;
	flasher_to_chan[2] = 2;
	flasher_to_chan[3] = 3;

	//Set the mean and standard devition for the flasher event
	//These values are taken from fitting a gaussian to a flahser spectrum
	//for an actual Blowfish neutron cell and flasher detector
	cellMeanFlasherEvent = 1500.0*keV;
	cellStdDevFlasherEvent = 65.0*keV;
	detectorMeanFlasherEvent = cellMeanFlasherEvent;
	detectorStdDevFlasherEvent = 150.0*keV;

	//new random number generator for the monitor spectrum using the array defined above
	monitorRand = new RandGeneral(monitorEventSpectrum,monitorSpectrumDatapoints);
	monitorEventMax = 4.0*MeV; //maximum value for the spectrum
}

//destructor
BXGainMonitor::~BXGainMonitor()
{
	delete[] ADC_cell_to_mod;
	delete[] ADC_cell_to_chan;
	delete[] flasher_to_chan;
	delete monitorRand;
}

//Generates and writes a flasher event to the Lucid file
void BXGainMonitor::FlasherEvent(void)
{
	G4double randomNumber;
	
	//Fill all of the cell ADCs
	for(G4int jj = 0; jj < numbCells; jj++)
	{
		randomNumber = RandGauss::shoot(cellMeanFlasherEvent, cellStdDevFlasherEvent);
		vmeadc_l[ ADC_cell_to_mod[jj] ]->SetQDC(randomNumber, ADC_cell_to_chan[jj] );
		vmeadc_s[ ADC_cell_to_mod[jj] ]->SetQDC(randomNumber, ADC_cell_to_chan[jj] );
	}
	
	//Fill all of the flasher detector ADCs
	for(G4int jj = 0; jj < numbFlashers; jj++)
	{
		randomNumber = RandGauss::shoot(detectorMeanFlasherEvent, detectorStdDevFlasherEvent);
		vmeadc_ig->SetQDC(randomNumber, flasher_to_chan[jj] );
	}
	
	//Increment the counter and write the event
	countFlasher->Increment();
	flasherEvt->WriteEventClear();
}
	
//Generates and writes a monitor event to the Lucid file
void BXGainMonitor::MonitorEvent(void)
{
	G4double randomNumber;
	G4double randomEnergy;
	
	for(G4int jj = 0; jj < numbFlashers; jj++)
	{
		//gets a random number between 0 and 1 and convert it to an energy range
		randomNumber = monitorRand->shoot();
		randomEnergy = monitorEventMax*randomNumber;

		vmeadc_ig->SetQDC(randomEnergy,flasher_to_chan[jj] );
	}

	//Increment the counter and write the event
	countMonitor->Increment();
	monitorEvt->WriteEventClear();
}

//EOF BXGainMonitor.cc
