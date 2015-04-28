/************************************************************
 * BXLucid.cc 
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell and Ru Igarashi
 *
 * Description:
 *
 * This program defines the Lucid variables and events for
 * the Blowfish neutron detector array.  It is ment to closely
 * mimic the real Blowfish so that a real looker file can be
 * tested and improved.
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

//G4Lucid includes
#include "G4Lucid.hh"
#include "G4SystemOfUnits.hh"


class BXLucid
{
	public:

	//constructor and destructor
	BXLucid() { lucidPtr = 0; }
	~BXLucid(){ delete lucidPtr; }

	//initialise the Lucid Variables (both UK and US spellings)
	G4int Initialise(void);
	inline G4int Initialize(void){ return Initialise(); }

	//Constant variables that are of use to other classes
	//These variables denote which scaler channel correspond to
	//the desired scaler
	static const G4int scalerTimerCh = 15;
	static const G4int scalerXarmCh = 5;
	
	private:

	//Initializes actual Blowfish variables
	G4int InitialiseActual(void);

	//Initializes ideal variables useful for debugging and understanding
	G4int InitialiseIdeal(void);

	//pointer to the G4Lucid object
	G4Lucid * lucidPtr;
};

//EOF BXLucid.hh
