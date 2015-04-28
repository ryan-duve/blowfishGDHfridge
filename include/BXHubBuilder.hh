/************************************************************
 * BXHubBuilder.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * This class builds the hub for the Blowfish neutron detector array.
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

#ifndef BXHubBuilder_H
#define BXHubBuilder_H 1

//Geant4 includes
#include "G4LogicalVolume.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"


class BXHubBuilder
{
	public:

	//constructor and destructor
	BXHubBuilder();
	~BXHubBuilder(){;}

	//Builds the arm's logical volume
	//returns 0 on success
	//returns 1 if Build() has been previously run.
	//returns 2 on failure
	//showContainer: do we want the container volume to be visible?
	//useWireframe: do we want to have a wireframe hub?
	G4int Build(G4bool showContainer = false,G4bool useWireframe = false);

	//Gets a pointer to the logical volume
	inline G4LogicalVolume * GetLVPointer(void){return theHubLogicalVolume;}

	//Gets dimensions of the hub
	inline G4double GetLength(void){return hubLength;}
	inline G4double GetInnerRadius(void){return hubInnerRadius;}
	inline G4double GetOuterRadius(void){return hubOuterRadius;}
	
	private:

	//pointer to the logical volume that can be returned
	G4LogicalVolume * theHubLogicalVolume;

	//important geometrical parameters
	G4double hubLength;
	G4double hubInnerRadius;
	G4double hubOuterRadius;

};

#endif

//EOF BXHubBuilder.hh
