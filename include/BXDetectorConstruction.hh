/************************************************************
 * DetectorConstruction.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * The BXDetectorConstruction class defines the materials and
 * geometry of the simulation.  It uses several helper classes
 * to define self-contained pieces of the array.
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

#ifndef BXDetectorConstruction_H
#define BXDetectorConstruction_H 1
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "BXCellSensitiveDetector.hh"


class BXDetectorConstruction : public G4VUserDetectorConstruction
{
  	public:

	//constructor and destructor don't do anything
    	BXDetectorConstruction( G4bool orientation);
    	~BXDetectorConstruction() {;}

	//all the action happens here
    	G4VPhysicalVolume* Construct();

  	private:
	G4bool GDH_orientation;
	
	//prints the goemetry tree
	void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);
};

#endif

//EOF DetectorConstruction.hh

