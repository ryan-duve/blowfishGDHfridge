//See PrimaryGeneratorAction.hh

#include "BXPrimaryGeneratorAction.hh"

//Geant4 includes
#include "globals.hh"
#include "Randomize.hh"
#include "G4ParticleDefinition.hh"

#include <fstream>
#include <iostream>
#define RUN_CELL 45 // > 88 means at any random cell

using namespace std;

//constructor
BXPrimaryGeneratorAction::BXPrimaryGeneratorAction( G4bool orientation)
{
	//particle gun and particle table 
	fParticleGun = new G4ParticleGun();
  	fParticleTable = G4ParticleTable::GetParticleTable();

	//default particle
  	fParticleGun->SetParticleDefinition(fParticleTable->FindParticle("neutron"));
  	fParticleGun->SetParticleEnergy( 1.0*MeV );
 	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.0));

	GDH_orientation = orientation;
	Arm_up = 1;

	//fTarget_length = 107*mm;
	G4double targHoldH = 5.*cm;  
	G4double targHoldTh = .1*cm;
	fTarget_length = targHoldH - 2.*targHoldTh;
	fBeam_diameter = 22*mm;
	fNeutron_energy = 4.0*MeV;
	//fmaxval_theta_precision = 0.1;
	//fmaxval_margin = 0.05;

	fPhoton_energy = 8*MeV;
	G4cout << "    Photon energy = " << fPhoton_energy/MeV << " MeV" << G4endl;
}

//destructor
BXPrimaryGeneratorAction::~BXPrimaryGeneratorAction()
{
  	delete fParticleGun;
}

//Generate particle event using whatever momentum/energy the user specified
void BXPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// choose a random place in the target
	// Note that in this version of the simulation the geometry is build
	// so that the z axis is the beam direction, y is up an z is beam left.
	G4double x,y,z,r;
	//G4cout << "Start of GeneratePrimaries" << G4endl;
	z = G4UniformRand()*fTarget_length - fTarget_length/2.;
	do	{
		y = G4UniformRand()*fBeam_diameter - fBeam_diameter/2.;
		x = G4UniformRand()*fBeam_diameter - fBeam_diameter/2.;
		r = sqrt(x*x + y*y);
		} while (r > fBeam_diameter/2.);
	G4ThreeVector position(x,y,z);
	// FOR TESTING
	//G4ThreeVector position(0.,0.,0.);
	fParticleGun->SetParticlePosition(position);
 	
 	//fParticleGun->SetParticleMomentumDirection( RandomDirection() );
	fParticleGun->SetParticleMomentumDirection( DeuteronDirection(RUN_CELL) );
 	//fParticleGun->SetParticleMomentumDirection( RandomDirectionAtCell( RUN_CELL) );
	// Call to WeightedDirection functions must come before this line!
	// since fNeutron_energy is set by them.
	fParticleGun->SetParticleEnergy(fNeutron_energy);

  	fParticleGun->GeneratePrimaryVertex(anEvent); //Fire at will, Mr. Worf!
	//G4cout << "End of GeneratePrimaries" << G4endl;
}

//returns a unit vector pointing at a specific or random cell
G4ThreeVector BXPrimaryGeneratorAction::RandomDirectionAtCell( G4int atcell )
{
	//We emit the gamma ray towards a cell
	G4int cell; //the cell to fire at
	if(atcell < 1 || atcell > 88) { cell = (G4int) (88.0*G4UniformRand()) + 1;}
	else { cell = atcell; }

	//compute the current angles of the cell
	G4double theta, phi;
	get_angles(cell, Arm_up, GDH_orientation, &theta, &phi);

	//Compute the (x,y,z) position of the cell with the center of Blowfish as the origin
	G4double pz = cos(theta);
	G4double px = sin(theta)*cos(phi);
	G4double py = sin(theta)*sin(phi);
	G4ThreeVector direction(px,py,pz);
	
	return direction;
}

//returns a unit vector pointing in a random direction
G4ThreeVector BXPrimaryGeneratorAction::RandomDirection()
{
	//samples phi and cos_theta from a uniform distribution
	G4double cos_theta = 2.0*G4UniformRand() - 1.0; // -1 <= cos(theta) < 1
	G4double phi = G4UniformRand()*2.0*M_PI;
	G4double sin_theta = sqrt( 1.0 - cos_theta*cos_theta);

	//Compute the (x,y,z) direction
	G4double pz = cos_theta;
	G4double px = sin_theta*cos(phi);
	G4double py = sin_theta*sin(phi);
	G4ThreeVector direction(px,py,pz);

	return direction;
}
// returns a unit vector pointing in a direction based on
// deuteron kinematics.
G4ThreeVector BXPrimaryGeneratorAction::DeuteronDirection( G4int atcell)
{

	G4int cell;
	if(atcell < 1 || atcell > 88) { cell = (G4int) (88.0*G4UniformRand()) + 1; } //the cell to fire at
	else { cell = atcell; }

	//compute the current angles of the cell
	G4double theta_detector, phi_detector;
	get_angles(cell, Arm_up, GDH_orientation, &theta_detector, &phi_detector);

	G4double delta_angle = 10.0*deg; // angle range for neutrons
  	// 10 deg will cover one cell
	G4double cosmin = cos(theta_detector + delta_angle);
	G4double cosmax = cos(theta_detector - delta_angle);
	G4double cos_theta = G4UniformRand()*(cosmax-cosmin) + cosmin;
	G4double phi = G4UniformRand()*2.*delta_angle + phi_detector - delta_angle;
	G4double sin_theta = sqrt( 1.0 - cos_theta*cos_theta);

	G4double pz = cos_theta;
  	G4double px = sin_theta * cos(phi);
  	G4double py = sin_theta * sin(phi);
	G4ThreeVector direction(px,py,pz);

	// calculate neutron energy from angle
	G4double neutron_angle = acos(cos_theta);
	(void) caln_dnp(&fPhoton_energy, &neutron_angle, &fNeutron_energy);
	//G4cout << "photon energy = " << fPhoton_energy/MeV << " MeV" << G4endl;
	//G4cout << "neutron angle = " << neutron_angle/deg << " deg" << G4endl;
	//G4cout << "neutron KE = " << fNeutron_energy/MeV << " MeV" << G4endl;

	return direction;
}

void
BXPrimaryGeneratorAction::caln_dnp( G4double *photon_eng, G4double *neutron_angle, G4double *neutron_ke)
	{
	double mass[4], t3[2], t4[2], a4[2];
	double t1, theta3;
	void kin2body( double*, double*, double*, double*, double*, double*);

/*	deuteron kinematics
c	particle 0 photon
c	particle 1 deuteron
c	particle 2 neutron
c	particle 3 proton
*/
	mass[0] = 0.;
	mass[1] = 1875.628;
	mass[2] = 939.57;
	mass[3] = 938.28;

	t1 = (*photon_eng)/MeV;
	theta3 = (*neutron_angle)/deg;

	(void) kin2body(&t1, &theta3, mass, t3, t4, a4);

	*neutron_ke = t3[0]*MeV;
	}
void
kin2body(double *t1, double *a3, double *mass, double *t3, double *t4, double *a4)
	{
	double p3[2], p4[2], e3[2], e4[2];
	double pi, e1, et, et2, ct, ct2, m32, p1, aa, a, b, c, det;
	int i;

/*	general 2 body kinematics (Lab Frame)
c	m(1) + m(2) -> m(3) + m(4)
c
c	INPUTS
c		t1	KE of incident particle (1)
c			target is particle 2 (stationary)
c		a3	angle of outgoing particle (3)
c		mass(4)	masses of particles (1,2,3,4)
c			Units: degrees, MeV, MeV/c^2
c
c	OUTPUTS
c		t3(2)	KE of outgoing particle (3)
c		t4(2)	KE of outgoing particle (4)
c		a4(2)	angle of particle 4
c			Two possible solutions for above
*/

	pi = 3.1415926535;
	e1 = *t1 + mass[0];
	et = e1 + mass[1];
	et2 = et*et;
	ct = cos(*a3*pi/180.);
	ct2 = ct*ct;
	m32 = mass[2]*mass[2];
	p1 = sqrt(e1*e1 - mass[0]*mass[0]);
	aa = p1*p1 - et2 - m32 + mass[3]*mass[3];
	a = 4.*(et2 - p1*p1*ct2);
	b = 4.*aa*p1*ct;
	c = 4*et2*m32 - aa*aa;

	det = b*b - 4.*a*c;
	if(det < 0.)
		{
		printf("kin_2body(): determinant < 0.\n");
		t3[0] = -1.;
		t4[0] = -1.;
		a4[0] = 0.;
		t3[1] = -1.;
		t4[1] = -1.;
		a4[1] = 0.;
		return;
		}

	p3[0] = (-b + sqrt(det))/2./a;
	p3[1] = (-b - sqrt(det))/2./a;

	for(i=0; i<2; i++)
		{
		if(p3[i] > 0.)
			{
			e3[i] = sqrt(p3[i]*p3[i] + m32);
			t3[i] = e3[i] - mass[2];
			det = p1*p1 - 2.*p1*p3[i]*ct + p3[i]*p3[i];
			if(det < 0.)
				p4[i] = -1.;
			else
				p4[i] = sqrt(det);
			if(p4[i] > 0.)
				{
				c = (p1 - p3[i]*ct)/p4[i];
				if(abs(c) < 1.)
					a4[i] = acos(c)*180./pi;
				else
					a4[i] = 0.;
				}
			else
				{
				a4[i] = 180.;
				}
			e4[i] = sqrt(p4[i]*p4[i] + mass[3]*mass[3]);
			t4[i] = e4[i] - mass[3];
			}
		}

/*	make first solution be valid if there are valid solutions */
	if(p3[0] < 0.)
		{
		p3[0] = p3[1];
		t3[0] = t3[1];
		t4[0] = t4[1];
		a4[0] = a4[1];
		p3[1] = -1.;
		}
/*	make invalid solution energies = -1. */
	for(i=0; i<2; i++)
		{
		if(p3[i] < 0.)
			{
			t3[i] = -1.;
			t4[i] = -1.;
			a4[i] = 0.;
			}
		}
	return;
	}

// get_angles returns the angles of a cell
// gdh = true means in the gdh orientation
//         cell 1 to beam right
//         arm_up is the arm that is up and
//         downstream (22.5 deg from vertical)
// gdh = false means the usual orientation
//         cell 1 upstream
//         arm_up is the arm that is vertical
//   theta = 0 is forward
//   phi = 0 is beam left
//   phi = 90 deg is up

void
BXPrimaryGeneratorAction::get_angles( G4int cell, G4int arm_up, G4bool gdh, G4double *theta, G4double *phi)
	{
	G4double theta_in, phi_in, theta_out, phi_out;
	G4double x_in, y_in, z_in;
	G4double x, y, z;

	G4int arm = (cell-1)%8; //0 to 7
	G4int ring = (cell-1)/8; // 0 to 10

	const G4double delta_phi = 45.0*deg; //angle between cells in a ring
	const G4double theta_start = (180.0-22.5)*deg; //last cell is at 22.5 degrees
	const G4double delta_theta = 13.5*deg; //angle between cells in an arm

	//compute the current angles of the cell
	theta_in = theta_start - delta_theta*((G4double) ring);
	G4int irot = arm + 1 - arm_up;
	if(irot < 0) irot += 8;
	phi_in = ((G4double) irot)*delta_phi + 90.0*deg;
	if(phi_in >= 360.0*deg) phi_in -= 360.0*deg;
	//G4cout << "Cell " << cell << " Arm "<<arm<<" Ring "<< ring << G4endl;
	//G4cout << "Theta_in = " << theta_in/deg << " deg" << G4endl;
	//G4cout << "Phi_in = " << phi_in/deg << " deg" << G4endl;
	if(!gdh)
		{
		*theta = theta_in;
		*phi = phi_in;
		return;
		}
	// GDH orientation. Blowfish rotated 22.5 deg.
	phi_in += delta_phi/2.;
	
	// cell location (radius = 1)
	// +z beam dir, +y up, +x beam left
	x_in = cos(phi_in) * sin(theta_in);
	y_in = sin(phi_in) * sin(theta_in);
	z_in = cos(theta_in);

	// rotate blowfish 90 deg around +y
	y = y_in;
	x = z_in;
	z = -x_in;

	phi_out =  atan2(y, x)*rad;
	theta_out = acos(z)*rad;

	if(phi_out < 0.*deg) phi_out += 360.*deg;

	*theta = theta_out;
	*phi = phi_out;
	}

#undef RUN_CELL
//EOF BXPrimaryGeneratorAction.cc
