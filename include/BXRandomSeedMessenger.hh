/************************************************************
 * BXRandomSeedMessenger.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * Provides a messenger to (re)initialise the GEANT4 random
 * number generator with a new seed.  This is useful for
 * scripts so that different scripts can be run with
 * different random numbers without having to recompile
 * the program.
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

#ifndef BXRandomSeedMessenger_h
#define BXRandomSeedMessenger_h 1


#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"

#include "globals.hh"

using namespace CLHEP;

//messenger setting the seed of the random number generator
class BXRandomSeedMessenger: public G4UImessenger
{
	public:

    	BXRandomSeedMessenger();
   	~BXRandomSeedMessenger();
    
    	void SetNewValue(G4UIcommand*, G4String);
    
	private:

	//sets seed 
	G4UIcmdWithAnInteger * seed;
	
    
};


#endif

//EOF BXRandomSeedMessenger.hh
