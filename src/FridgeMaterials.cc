//C++ includes
#include <iostream>

//Geant includes
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"

//My Includes
//#include "FridgeConstants.hh"
#include "FridgeMaterials.hh"

FridgeMaterials* FridgeMaterials::instance=0;

FridgeMaterials* FridgeMaterials::getInstance()
{
  if(!instance)
    instance = new FridgeMaterials();

  return instance;
}

void FridgeMaterials::ConstructAllMaterials()
{

	G4NistManager* nist = G4NistManager::Instance();

	//Defining Elements
	O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole); 
	C = new G4Element("Carbon"  , "C", z=8., a= 12.011*g/mole);
	H = new G4Element("Hydrogen"  , "H", z=1., a= 1.0081*g/mole); 
	D = new G4Isotope("Deuterum", iz=1,n=1, a = 2.0147*g/mole);  
	elD = new G4Element("Deuterium","D", ncomp=1);
	elCu = nist->FindOrBuildElement("Cu");
	elHe4 = nist->FindOrBuildElement("He");
	//	G4Material* He4 = nist->FindOrBuildMaterial("G4_He");
	Si = nist->FindOrBuildElement("Si");
	Cr = nist->FindOrBuildElement("Cr");
	Mn = nist->FindOrBuildElement("Mn");
	Fe = nist->FindOrBuildElement("Fe");
	Ni = nist->FindOrBuildElement("Ni");
	Cu = nist->FindOrBuildMaterial("G4_Cu");
	
	////////////// liquid He3 //////////////
	// for now, use He4 temperature at about boiling point
	//	temperature = 4.*kelvin;
	// Real, from Don
	temperature = 0.05*kelvin;
	// density, for now use He4 temperature at about boiling point
	//	density = 0.125*g/cm3;
	// Real, from Don
	G4double densityHe3 = 0.081*g/cm3; // will use later, so give a separate name
	// molar mass 3.016g/mole
	a = 3.016*g/mole;
	// constructing isotope
	G4Isotope* iHe3  = new G4Isotope("iHe3", iz=1, n=3, a);

	// constructing element
	G4String symbol;
	elHe3 = new G4Element("elHe3",symbol="elHe3",ncomp=1);
	elHe3->AddIsotope(iHe3,100.*perCent);

	// liquid He3 material
	LHe3 = new G4Material("Helium-3",densityHe3,ncomp=1,kStateLiquid,temperature);
	LHe3->AddElement(elHe3,natoms=1);

	////////////////////// liquid He4 ////////////////////////
	temperature = 0.05*kelvin;
	G4double densityHe4 = 0.125*g/cm3; // will use later, so give a separate name
	a = 4.02602*g/mole;
	// constructing isotope
	G4Isotope* iHe4  = new G4Isotope("iHe4", iz=2, n=4, a);
	// constructing element
	elHe4 = new G4Element("elHe4",symbol="elHe4",ncomp=1);
	elHe4->AddIsotope(iHe4,100.*perCent);
	// liquid He4 material
	LHe4 = new G4Material("Helium-4",densityHe4,ncomp=1,kStateLiquid,temperature);
	LHe4->AddElement(elHe4,natoms=1);
	/////////////////////////////////
	/////////////// Mixing chamber Helium mixture ///////////////
	// According to Don, 70% He3, 30% He4 (by volume?)
	G4double fractionHe3 = 0.7;
	G4double fractionHe4 = 1. - fractionHe3;
	G4double densityHeMix = fractionHe3*densityHe3+fractionHe4*densityHe4;
	G4cout<<"fractionHe3 "<<fractionHe3<<G4endl;
	G4cout<<"fractionHe4 "<<fractionHe4<<G4endl;
	G4cout<<"densityHe3 "<<densityHe3/(g/cm3)<<G4endl;
	G4cout<<"densityHe4 "<<densityHe4/(g/cm3)<<G4endl;
	G4cout<<"densityHeMix "<<densityHeMix/(g/cm3)<<G4endl;
	// If 70/30 by volume, find fractionmass
	G4double fractionmassHe3 = fractionHe3*densityHe3/densityHeMix;
	G4double fractionmassHe4 = fractionHe4*densityHe4/densityHeMix;
	HeMix = new G4Material("HeMix", densityHeMix,ncomp=2);
	HeMix->AddMaterial(LHe3, fractionmassHe3);
        HeMix->AddMaterial(LHe4, fractionmassHe4);
	////////////////////////////////////////////////////////////
	//////////////////////// gas He4 ///////////////////////////
	gasHe4 = nist->FindOrBuildMaterial("G4_He");
	
	//creates StainlessSteel        
	StainlessSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

	
	//creates isotope
	elD->AddIsotope(D, abundance=100*perCent);

	//creates Butenol

	Butanol = new G4Material("Butanol", density = 810.00*kg/m3,ncomp=3);

	Butanol->AddElement(H, 10);
	Butanol->AddElement(O, 1); 
	Butanol->AddElement(C, 4);

	
	dButanol = new G4Material("dButanol", density = 810.00*kg/m3,ncomp=3);
	dButanol->AddElement(elD,natoms=10);
	dButanol->AddElement(O,natoms=1); 
	dButanol->AddElement(C,natoms=4);    

	
	//creates mishmash
	// material emulating a mixture of copper (?) <-- check with Don
	// and He4 in the area around the spiral providing He
	// visual estimate ~25% metal (Cu?) and ~75% gaseous (?check w Don) He4
	// the density is then 0.25*dens(Cu)+0.75*dens(He4) ~ 0.25*dens(Cu)
	density = 2.24*g/cm3;
	/*
	MishMash = new G4Material("MishMash", density,ncomp=2);
	MishMash->AddElement(elCu,fractionmass=.25);
        MishMash->AddElement(elHe4, fractionmass=.75);
	*/
	// with such ratio of Cu and He, fraction mass of He will go unnoticed,
	// make material out of Cu with smaller density
	Mix75He25Cu = nist->BuildMaterialWithNewDensity("LightCu2575","G4_Cu",density);
	// heavier mixture (50/50) for narrow tube
	density = 4.48*g/cm3;
	Mix50He50Cu = nist->BuildMaterialWithNewDensity("LightCu5050","G4_Cu",density);

	//Predefined Materials
	Aluminum = nist->FindOrBuildMaterial("G4_Al");
	Vaccum = nist->FindOrBuildMaterial("G4_Galactic");
	Plastic = nist->FindOrBuildMaterial("G4_POLYPROPYLENE");
	Kapton = nist->FindOrBuildMaterial("G4_KAPTON");

}



