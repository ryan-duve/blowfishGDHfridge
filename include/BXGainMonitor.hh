/************************************************************
 * BXLucid.cc 
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisor: Rob Pywell
 *
 * Description:
 *
 * This class is used to mimic the gain monitoring system.  It
 * writes the Lucid events 'flasher' and 'monitor' which are used
 * to track the gain of the neutron cells.
 *
 * Credits:
 * 
 * Much of this code is from my supervisor, Dr. Pywell and the
 * examples produced by the Geant4 Collaboration and distributed
 * with GEANT4.  Lisence details for the GEANT4 collaboration code
 * can be found at http://geant4.web.cern.ch/geant4/license/
 * Since these details are vague, I assume that all code is released
 * under an LGPL or BSD-like license.
 * 
 ********************************************************************
 * DISCLAIMER                                                       *
 *                                                                  *
 * The following disclaimer summarizes all the specific disclaimers *
 * of contributors to this software. The specific disclaimers,which *
 * govern, are listed with their locations in:                      *
 *   http://cern.ch/geant4/license                                  *
 *                                                                  *
 * Neither the authors of this software system, nor their employing *
 * institutes,nor the agencies providing financial support for this *
 * work  make  any representation or  warranty, express or implied, *
 * regarding  this  software system or assume any liability for its *
 * use.                                                             *
 *                                                                  *
 * By copying,  distributing  or modifying the Program (or any work *
 * based  on  the Program)  you indicate  your  acceptance of  this *
 * statement, and all its terms.                                    *
 ********************************************************************/
#include "globals.hh"
#include "G4SystemOfUnits.hh"

//G4Lucid includes
#include "G4Lucid.hh"
#include "G4LucidEvent.hh"
#include "G4LucidLong.hh"
#include "G4LucidV792.hh"

//Random number generator
#include "Randomize.hh"

using namespace CLHEP;

class BXGainMonitor
{
	public:

	//constructor and destructor
	//The constructor takes information needed to map blowfish cells into ADC modules and channels
	//It also takes the number of cells in the detector array and the number of flashers
	BXGainMonitor(G4int ADC_cell_to_mod_in[], G4int ADC_cell_to_chan_in[],G4int numbCells_in);
	~BXGainMonitor();

	//Generates and writes a flasher event to the Lucid file
	void FlasherEvent(void);
	
	//Generates and writes a monitor event to the Lucid file
	void MonitorEvent(void);
	
	private:

	//These arrays map each cell to a module and channel
	G4int numbCells;
	G4int numbFlashers;
	G4int * ADC_cell_to_mod;
	G4int * ADC_cell_to_chan;
	G4int * flasher_to_chan;

	//The mean and standard deviation of the gaussian of a flasher event
	//All ADCs use the same mean for convinience
	G4double cellMeanFlasherEvent;
	G4double cellStdDevFlasherEvent;
	G4double detectorMeanFlasherEvent;
	G4double detectorStdDevFlasherEvent;
	
	//The following array keeps the spectrum to use for generating
	//a random 'monitor' event
	static const G4double monitorEventSpectrum[];
	static const G4int monitorSpectrumDatapoints;
	G4double monitorEventMax;
	
	//A general random number generator for the monitor event.
	RandGeneral * monitorRand;

	//pointer to the G4Lucid object
	G4Lucid * lucidPtr;

	//Pointers to the G4Lucid events
	G4LucidEvent * monitorEvt;
	G4LucidEvent * flasherEvt;
	
	//Pointers to the needed Lucid Variables
	G4LucidLong * countMonitor;
	G4LucidLong * countFlasher;
	G4LucidV792 * vmeadc_l[3]; //QDC
	G4LucidV792 * vmeadc_s[3]; //QDC
	G4LucidV792 * vmeadc_ig; //QDC
};

//EOF BXGainMonitor.hh
