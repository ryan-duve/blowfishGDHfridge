/************************************************************
 * BXCellSensitiveDetector.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisor: Rob Pywell
 *
 * Description:
 *
 * Responds to a hit on a neutron cell, which is a sensitive detector.
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

#ifndef BXCellSensitiveDetector_hh
#define BXCellSensitiveDetector_hh 1
#include "globals.hh"
#include "G4SystemOfUnits.hh"
//Virtual class
#include "G4VSensitiveDetector.hh"

//classes needed by this one
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"

//my classes
#include "LightOutput.hh"

//The hit class for cells
#include "BXCellHit.hh"


class BXCellSensitiveDetector : public G4VSensitiveDetector
{

  	public:

	//Constructor and destrutor
     	BXCellSensitiveDetector(G4String name, G4String material);
      	virtual ~BXCellSensitiveDetector();

	//Functions called by GEANT4
      	virtual void Initialize(G4HCofThisEvent*HCE);
      	virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      	virtual void EndOfEvent(G4HCofThisEvent*){;}

  	private:

      	//the collection of hits.
      	BXCellHitsCollection* hitsCollection;

      	//The material of the sensitive detector.
      	//Needed for obtaining light output.
      	G4String cellMaterial;

	//A class used to compute the light output
	LightOutput * lightOutput;

	// parentage to find cell number
	G4int fParentage;

	// to suppress printout
	G4bool fPrintGuess;
};

#endif

//EOF BXCellSensitiveDetector.hh
