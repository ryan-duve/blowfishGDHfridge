/************************************************************
 * BXRunAction.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * Code run at the beginning and end of a run.  It outputs information
 * to Lucid about the details of the run.
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

#ifndef BXRunAction_h
#define BXRunAction_h 1

//Geant4 includes
#include "G4UserRunAction.hh"
#include "globals.hh"

//classes I need from Geant4
#include "G4Run.hh"
#include "G4Timer.hh"

//Lucid classes
#include "G4Lucid.hh"

#include "BXRandomSeedMessenger.hh"

using namespace CLHEP;

class BXRunAction : public G4UserRunAction
{
  	public:
    	BXRunAction();
   	~BXRunAction();

 	//functions called by Geant4
    	void BeginOfRunAction(const G4Run*);
    	void EndOfRunAction(const G4Run*);

  	private:

	//pointer to Lucid
    	G4Lucid * lucidPtr;
	
	//keeps track of time elapsed
	G4Timer * timer;

	BXRandomSeedMessenger * rsm;
};

#endif //#ifndef BXRunAction_h

//EOF BXRunAction.hh
