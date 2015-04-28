/************************************************************
 * BXEventAction.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell 
 *
 * Description:
 *
 * Code run at the beginning and end of an event.  This class
 * is responsible for writing the bulk of Lucid's data to
 * the disk.
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

 
#ifndef BXEventAction_h
#define BXEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
//Other BlowfishX classes
#include "BXGainMonitor.hh"

using namespace CLHEP;

//Geant 4 classes
class G4Event;
class TString;

//G4Lucid clases
class G4Lucid;
class G4LucidEvent;
class G4LucidV792;
class G4LucidV775;
class G4LucidLong;
class G4LucidFloat;

class BXEventAction : public G4UserEventAction
{
  	public:

	//constructor and destructor
    	BXEventAction();
   	~BXEventAction();

	//run by G4 at the beginning and end of a run.
    	void BeginOfEventAction(const G4Event*);
    	void EndOfEventAction(const G4Event*);

  	private:

	//Computes the short gate ADC based on the long gate and PSD parameter
	G4double ComputeShortADC(G4double lightOutput, G4String particle);
	
	//Loads the cell map into memory
	void ReadCellMap(void);
	void CellMapHelper(G4int * array, G4int min, G4int max);
	
	//Performs a 'pedestal' event
	void PedestalEvent(void);

	//A class used to perform 'monitor' and 'flasher' events
	BXGainMonitor * fGainMonitor;
	
	//pointer to Lucid
	G4Lucid * lucidPtr;

	//pointer to Lucid events
	G4LucidEvent * neutronEvt; //information as from the real blowfish
	G4LucidEvent * neutronIdeal; //ideal information not avialable from the real blowfish
	G4LucidEvent * windupIdeal;
	G4LucidEvent * pedestalEvt;
	G4LucidEvent * scalerreadEvt;
	
	//pointer to Lucid variables (real ones)
	G4LucidV792 * vmeadc_l[3]; //QDC
	G4LucidV792 * vmeadc_s[3]; //QDC
	G4LucidV792 * vmeadc_ig; //QDC
	G4LucidV775 * vmetdc[3]; //TDC
	G4LucidLong * cellScaler[3]; //Scalers for the neutron cells
	G4LucidLong * scaler[3]; //The rest of the scalers
	G4LucidLong * count_neutron, * count_pedestal, * count_scalerread;
	
	//pointer to Lucid variables (ideal ones)
	G4LucidLong * geantinoHits;

	//These arrays map each cell to a module.
	//Get these values from your experiment's Cell_Map.dat file
	static const G4int numbCells = 88;
	G4int ADC_cell_to_mod[numbCells];  //modules: 0 to 2
	G4int ADC_cell_to_chan[numbCells]; //channels: 0 to 31
	G4int TDC_cell_to_mod[numbCells]; 
	G4int TDC_cell_to_chan[numbCells];
	G4int SCA_cell_to_mod[numbCells];  //cell scalers
	G4int SCA_cell_to_chan[numbCells];
	
	//Hardware thresholds
	G4double hardwareThreshold[numbCells];

	//Light output smearing widths
	G4double sigmaLightStatistical;
	G4double sigmaLightNoise;
};


#endif

//end of EventAction.hh
