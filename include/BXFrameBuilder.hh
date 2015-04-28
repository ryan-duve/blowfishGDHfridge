/************************************************************
 * BXFrameBuilder.hh
 *
 ********************************************************************/

#ifndef BXFrameBuilder_H
#define BXFrameBuilder_H 1

//Geant4 includes
#include "G4LogicalVolume.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

//sensitive detector includes
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

class BXFrameBuilder
{
	public:

	//constructor and destructor
	BXFrameBuilder( G4LogicalVolume *);
	~BXFrameBuilder(){;}

	//Builds the frame's logical volume
	//returns 0 on success
	//returns 2 on failure
	//useWireframe: do we want to have a wireframe arm?
	G4int Build( G4bool useWireframe = false);

	private:

	//pointer to the logical volume that can be returned
	G4LogicalVolume * frameLV;

};

#endif

//EOF BXArmSegmentBuilder.hh
