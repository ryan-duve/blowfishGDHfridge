/************************************************************
 * BXPrimaryGeneratorAction.hh
 *
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 * Supervisors: Rob Pywell
 *
 * Description:
 *
 * This class defines the initial particles and their energy, momentum
 * and direction.  This class also provides functionality for derived
 * classes such as a function that returns a random direction.  This
 * class does not provide any special spectrum for the emitted particles
 * and allows the user to set direction/particle/energy at the command line.
 * Derived classes have the option of providing that spectrum information.
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

#ifndef BXPrimaryGeneratorAction_h
#define BXPrimaryGeneratorAction_h 1

//Geant4 classes
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

//Virtual class
#include "G4VUserPrimaryGeneratorAction.hh"

class BXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:

	//constructor and destructor
    	BXPrimaryGeneratorAction( G4bool orientation);
    	virtual ~BXPrimaryGeneratorAction();

	//used by Geant4 to generate the primary particles of the event
    	virtual void GeneratePrimaries(G4Event* anEvent);

	//Functions and variables that are useful for derived classes
	protected:

	//Returns a unit vector pointing in a random direction
	G4ThreeVector RandomDirection(void);
	
	//Returns a unit vector pointing at a random cell
	//Assums that the particle will be generated in the centre of the array
	G4ThreeVector RandomDirectionAtCell( G4int atcell);

	//Returns a unit vector pointing in a random direction
	//Calculates neutron energy based on photon energy and neutron angle.
	G4ThreeVector DeuteronDirection(G4int atcell);

	// Calculates the neutron KE from deuteron kinematics
	void caln_dnp( G4double *, G4double *, G4double *);
	// calculates the angle of a particular cell
	void get_angles( G4int , G4int , G4bool , G4double *, G4double *);

	G4bool GDH_orientation;
	G4int Arm_up;
	G4ParticleGun* fParticleGun;
    	G4ParticleTable * fParticleTable;
	G4ThreeVector forigin;
	G4double fTarget_length;
	G4double fBeam_diameter;
	G4double fNeutron_energy;
	G4double fA;
	G4double falpha;
	G4double fbeta;
	G4double fgamma;
	G4double fepsilon;
	G4double fnu;
	G4double fPhoton_energy;
	G4double fmaxval;
	G4double fmaxval_theta_precision;
	G4double fmaxval_margin;
	G4int ftype;
	G4double fA0;
	G4double fa1;
	G4double fa2;
	G4double fa3;
	G4double fa4;
	G4double fe2;
	G4double fe3;
	G4double fe4;
	G4double fLegUseOne;

};

#endif

//EOF BXPrimaryGeneratorAction.hh
