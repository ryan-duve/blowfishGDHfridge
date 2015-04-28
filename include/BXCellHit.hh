/************************************************************
 * BXCellHit.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * The BXCellHit class stores information about a particle
 * hitting a neutron cell.  This file also contains some memory
 * managment details that GEANT4 reccomends.
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

#ifndef BXCellHit_h
#define BXCellHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class BXCellHit : public G4VHit
{
  	public:

      	BXCellHit();
      	~BXCellHit(){;}

	//overloaded operators with with hits allocator
	//because that's the way Geant4 wants it
      	inline void *operator new(size_t);
      	inline void operator delete(void *aHit);

	//prints information about the variable
	void Print(std::ostream & os);
	void Print(){ Print(G4cout); }

	//Energy deposited
	inline void SetEnergyDeposited(G4double de) { edep = de; }
	inline G4double GetEnergyDeposited(void){ return edep; }

	//Light output
	inline void SetLightOutput(G4double lo){ lightOut = lo; }
	inline G4double GetLightOutput(void){ return lightOut; }

	//the name of the particle
	inline void SetParticle(G4String part) { particle = part; }
	inline G4String GetParticle(void){ return particle; }

	//time at the beginning of the step
	inline void SetInitTime(G4double tm) { time=tm;}
	inline G4double GetInitTime(void) { return time; }

	//amount of time for the step
	inline void SetDeltaTime(G4double tm) {deltaTime=tm;}
	inline G4double GetDeltaTime(void) {return deltaTime;}

	//the idenification number of the track
	inline void SetTrackID(G4int id) {trackID=id;}
	inline G4int GetTrackID(void) {return trackID;}

	//ring number: 0 to 10
	inline void SetRingNumber(G4int no) {ringNo=no;}
	inline G4int GetRingNumber(void) {return ringNo;}

	//arm number: 0 to 7
	inline void SetArmNumber(G4int no) {armNo=no;}
	inline G4int GetArmNumber(void) {return armNo;}

	//cell number: 0 to 87
	inline void SetCellNumber(G4int no) {cellNo=no;}
	inline G4int GetCellNumber(void) {return cellNo;}

	//Sets and gets the pre and post-step hit positions in the coordinates of the detector
	inline void SetPreLocalPosition (G4ThreeVector pos){localPrePos  = pos;}
	inline void SetPostLocalPosition(G4ThreeVector pos){localPostPos = pos;}
	inline G4ThreeVector GetPreLocalPosition (void){ return localPrePos; }
	inline G4ThreeVector GetPostLocalPosition(void){ return localPostPos; }
	
	private:

	G4double edep;
	G4double lightOut;
	G4double time;
	G4double deltaTime;
	G4int trackID;
	G4int ringNo; //stored 0 to 10
	G4int armNo; //stored 0 to 7
	G4int cellNo; // stored 0 to 87
	G4String particle;
	G4ThreeVector localPrePos, localPostPos;
};

//for operator overloading of printing operator
std::ostream &operator<<(std::ostream &os,BXCellHit &var);

//HitsCollection template for BXCellHit
typedef G4THitsCollection<BXCellHit> BXCellHitsCollection;

//Allocator template for BXCellHit
extern G4Allocator<BXCellHit> BXCellHitAllocator;

//overloaded new operator works with allocator
//because cause that's the way Geant4 wants it
inline void* BXCellHit::operator new(size_t)
{
	void* aHit;
	aHit = (void*)BXCellHitAllocator.MallocSingle();
	return aHit;
}

//overloaded delete operator works with allocator
//because that's the way Geant4 wants it
inline void BXCellHit::operator delete(void* aHit)
{
 	BXCellHitAllocator.FreeSingle((BXCellHit*) aHit);
}

#endif

//EOF BXCellHit.hh
