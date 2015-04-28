//See BXDetectorConstruction.hh for more information 

#include "BXDetectorConstruction.hh"

//helper classes
//#include "BXCellBuilder.hh"
#include "BXArmSegmentBuilder.hh"
#include "BXFrameBuilder.hh"

#include "FridgeBuilder.hh"

//materials
#include "G4Material.hh"
#include "G4NistManager.hh"

//Geometry includes
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Tet.hh"
#include "G4SubtractionSolid.hh"

//global GEANT4 includes
#include "globals.hh"

//visualisation includes
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//Parameterised volumes
//#include "G4PVParameterised.hh"
//#include "BXArcParam.hh"
//#include "BXCircParam.hh"


//Constructor
BXDetectorConstruction::BXDetectorConstruction( G4bool orientation)
{
	GDH_orientation = orientation;
}

//Constructs geometries and materials
G4VPhysicalVolume* BXDetectorConstruction::Construct()
{

	//------------------------------------------------------------------
  	// Materials 
	//------------------------------------------------------------------

 	G4double density;
  	G4int ncomponents, natoms;

	//Get the NIST defined materials and elements
	G4NistManager* nist = G4NistManager::Instance();

	G4Element * elH  = nist->FindOrBuildElement("H");
	G4Element * elC  = nist->FindOrBuildElement("C");
	G4Element * elFe = nist->FindOrBuildElement("Fe");
	G4Element * elHe = nist->FindOrBuildElement("He");
	G4Element * elCr = nist->FindOrBuildElement("Cr");
	G4Element * elNi = nist->FindOrBuildElement("Ni");
	G4Element * elMn = nist->FindOrBuildElement("Mn");
	G4Element * elSi = nist->FindOrBuildElement("Si");
	G4Element * elP  = nist->FindOrBuildElement("P");
	G4Element * elS  = nist->FindOrBuildElement("S");
	G4Element * elN  = nist->FindOrBuildElement("N");
	G4Element * elO  = nist->FindOrBuildElement("O");
	G4double a;  // atomic mass
  	G4double z;  // atomic number
  	G4String name, symbol;
  	a = 2.01*g/mole;
  	G4Element* elD = new G4Element(name="Deuterium", symbol="D", z=1., a);
	
	G4Material * Air      = nist->FindOrBuildMaterial("G4_AIR");
	//G4Material * Aluminum = nist->FindOrBuildMaterial("G4_Al");

	//BC-505 Liquid Scintillator 
  	density = 0.877*g/cm3;
  	G4Material * BC505 = new G4Material("BC505", density, ncomponents=2);
  	BC505->AddElement(elC, natoms=1000);
  	BC505->AddElement(elH, natoms=1331);

	//Steel (not stainless)
	G4Material* Steel = new G4Material("Steel", density=7.7*g/cm3, ncomponents=2);
	Steel->AddElement(elC, 0.04);
	Steel->AddElement(elFe, 0.96);

	//Stainless Steel (304, maximum composition percentages, see "stainless" in /documents)
	G4Material * Stainless = new G4Material("Stainless",density=8.0*g/cm3,ncomponents=9);
	Stainless->AddElement(elFe, 0.6650);
	Stainless->AddElement(elC, 0.0008);
	Stainless->AddElement(elCr, 0.2000);
	Stainless->AddElement(elNi, 0.1050);
	Stainless->AddElement(elMn, 0.0200);
	Stainless->AddElement(elSi, 0.0075);
	Stainless->AddElement(elP, 0.0005);
	Stainless->AddElement(elS, 0.0003);
	Stainless->AddElement(elN, 0.0010);
/*
	//Window material
	G4Material * Windowmaterial = new G4Material("Windowmaterial",density= ,ncomponents=
	Windowmaterial->AddElement(el
*/

	//Target assembly gases
	const G4double pressure = 50.0; //in atm

	// Helium Gas
	density = 0.0001636*pressure*g/cm3;
	G4Material* Helium = new G4Material("Helium_gas", density, ncomponents=1);
  	Helium->AddElement(elHe, 1.0);

	//Hydrogen Gas
	density = 0.00004120*pressure*g/cm3;
	G4Material * Hydrogen = new G4Material("Hydrogen_gas", density, ncomponents=1);
	Hydrogen->AddElement(elH, 1.0);

	// D2O Target
	density = 1.11*g/cm3;
	G4Material* D2O = new G4Material(name="D2O", density, ncomponents=2);
	D2O->AddElement(elD, natoms=2);
	D2O->AddElement(elO, natoms=1);	

  	// Lucite
  	density = 1.18*g/cm3;
  	G4Material* Lucite = new G4Material(name="Lucite", density, ncomponents=3);
  	Lucite->AddElement(elC, natoms=5);
  	Lucite->AddElement(elH, natoms=8);
  	Lucite->AddElement(elO, natoms=2);

	//------------------------------------------------------------------
  	// Geometry Variables
	//------------------------------------------------------------------

	//Much of Blowfish is designed to integral numbers of inches
	//const G4double in = 2.54*cm;

	//------------------------------------------------------------------
  	// Blowfish Neutron Detector Array Geometry
	//------------------------------------------------------------------

	// some Blowfish parameters
	const G4double cell_start_angle = 22.5*deg;
	const G4double delta_angle = (180.*deg - 2.*cell_start_angle)/10.;


	//------------------------------ experimental hall (world volume)

	// Although many elements are built in the natural geant4 coordinate system
	// with z up, they are inserted into the world with y up.
	// In the end everthing is rotated so that the beam is along the z-axis

	//arbitary values that should enclose any reasonable geometry
	const G4double expHall_x = 7.0*m;
	const G4double expHall_y = 5.0*m;
	const G4double expHall_z = expHall_x;
	G4ThreeVector hallDimensions(expHall_x, expHall_y, expHall_z);

	//create the hall
	G4Box * experimentalHallBox = new G4Box("ExpHallBox",expHall_x/2.,expHall_y/2.,expHall_z/2.);
	G4LogicalVolume * experimentalHallLV = new G4LogicalVolume(experimentalHallBox, Air,"ExpHallLV");

	G4PVPlacement * experimentalHallPhys 
		= new G4PVPlacement(0,G4ThreeVector(0.0,0.0,0.0), experimentalHallLV,"ExpHallPhys",0,false,0);

	//Make the world volume invisible
  	experimentalHallLV->SetVisAttributes( G4VisAttributes::Invisible);

	// Create a logical volume in which to build the detector
	// This will be rotated when placed depending on the GDH_orientation.
	G4Box * detectorBox = new G4Box("detectorBox",expHall_x/2.,expHall_y/2.,expHall_z/2.);
	G4LogicalVolume * detectorLV = new G4LogicalVolume(detectorBox, Air,"detectorLV");
  	detectorLV->SetVisAttributes( G4VisAttributes::Invisible);

	// build the support frame first
	// Frame is built directly into the detectorLV
	BXFrameBuilder theFrameBuilder(detectorLV);
	G4int reterr = theFrameBuilder.Build(false);
	if(reterr != 0) G4cout << "WARNING: ERROR in building frame." << G4endl;

	// Build an arm segment which contains the cell
	// the sensitive detector
	
	BXCellSensitiveDetector * cellSD = new BXCellSensitiveDetector("Cell","BC505");

	BXArmSegmentBuilder theArmSegmentBuilder;
	theArmSegmentBuilder.Build(cellSD, false, false);
	G4LogicalVolume * theArmSegmentLV = theArmSegmentBuilder.GetLVPointer();

	// This places a single copy of the segment in the world for debugging
	//new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), theArmSegmentLV, "ArmSegmentContainerPhys",experimentalHallLV,false,0);

	// now place 88 copys of the segment in the world.
	// the copy number will be the cell number (counting from 0)
	// The final placement is with Up being the +y direction.
	// Arm 1 is up in normal orientation
	// Arm 1 is up and downstream in GDH orientation
	char pname[30];
	G4RotationMatrix Rotz, Rotx;
	for(G4int cell = 0; cell < 88; cell++)
		{
		G4int ring = cell/8; //integer division
		G4int arm = cell%8;
		if(arm == 0)
			{
			Rotz.set(0.,0.,0.); //back to identity
			Rotz.rotateZ( 180.*deg - cell_start_angle - delta_angle/2. - delta_angle*ring );
			}
		Rotx = Rotz;
		if(GDH_orientation)
			{
			Rotx.rotateX(45.*deg*arm + 22.5*deg);
			}
		else
			{
			Rotx.rotateX(45.*deg*arm);
			//Rotx.rotateY(-90.*deg);
			}
		sprintf(pname, "Arm Segment %02d",cell);
		G4String sname(pname);
		new G4PVPlacement(G4Transform3D(Rotx, G4ThreeVector(0.,0.,0.)),
			theArmSegmentLV, sname, detectorLV, false, cell); 
		}
	
	// place the detector in the experimental Hall
	G4RotationMatrix DetectorRot;
	DetectorRot.set(0.,0.,0.);
	if(!GDH_orientation) DetectorRot.rotateY(-90.0*deg);
	new G4PVPlacement(G4Transform3D(DetectorRot, G4ThreeVector(0.,0.,0.)),
			detectorLV, "detectorPlacement", experimentalHallLV, false, 0); 

	// Target construction and placement would go here.
	

	// inset Fridge
	// inseting the fridge make no sense unless GDH_orientation = true
	  //instantiates Dillution Refrigerator  
  FridgeBuilder fridge;
  G4LogicalVolume * fridge_logic = fridge.GetFridge();
  G4double fridge_offset = fridge.GetOffset();

  //places fridge in world
	G4RotationMatrix FridgeRot;
	FridgeRot.set(0.,0.,0.);
	DetectorRot.rotateY(180.0*deg);
	new G4PVPlacement(G4Transform3D(DetectorRot, G4ThreeVector(0.,0.,fridge_offset)),
			fridge_logic, "FridgePlacement", experimentalHallLV, false, 0); 

	/*
	// for now just a cylinder of lucite containing heavy water
	G4double Target_length = 107.*mm;
	G4double Target_diameter = 3.*cm;
	G4double Target_container_thickness = 1.0*mm;

	// build it in a container
	G4double cont_length = (Target_length + 2.*Target_container_thickness) +0.1*mm;
	G4double cont_radius = (Target_diameter/2. + Target_container_thickness) +0.1*mm;
	G4Tubs * target_cont_cyl = new G4Tubs("target_con_cyl", 0.,
		cont_radius, cont_length/2., 0., 360.*deg);
	G4LogicalVolume * targetLV = new G4LogicalVolume(target_cont_cyl, Air, "TargetLV");
  	targetLV->SetVisAttributes( G4VisAttributes::Invisible);

	G4ThreeVector center = G4ThreeVector(0.,0.,0.);
	//target container
	G4Tubs * cont_cyl = new G4Tubs("con_cyl", Target_diameter/2.,
		Target_diameter/2.+Target_container_thickness, Target_length/2., 0., 360.*deg);
	G4LogicalVolume * contLV = new G4LogicalVolume(cont_cyl, Lucite, "contLV");
	new G4PVPlacement(0, center, contLV, "TargetContainer", targetLV, false, 0); 
	//Target
	G4Tubs * targ_cyl = new G4Tubs("targcyl", 0.,
		Target_diameter/2., Target_length/2., 0., 360.*deg);
	G4LogicalVolume * targLV = new G4LogicalVolume(targ_cyl, D2O, "targLV");
	new G4PVPlacement(0, center, targLV, "Target", targetLV, false, 0); 
	//container ends
	G4Tubs * end_cyl = new G4Tubs("endcyl", 0.,
		Target_diameter/2.+Target_container_thickness, Target_container_thickness/2., 0., 360.*deg);
	G4LogicalVolume * endLV = new G4LogicalVolume(end_cyl, Lucite, "endLV");
	G4double targ_pz = Target_length/2. + Target_container_thickness/2.;
	new G4PVPlacement(0, G4ThreeVector(0.,0.,-targ_pz), endLV, "End 1", targetLV, false, 0); 
	new G4PVPlacement(0, G4ThreeVector(0.,0.,targ_pz), endLV, "End 2", targetLV, false, 1); 
	

	G4VisAttributes* luciteAtt = new G4VisAttributes(G4Colour::White()); //white
    	luciteAtt->SetForceSolid(true);
	contLV->SetVisAttributes(luciteAtt);
	endLV->SetVisAttributes(luciteAtt);
	G4VisAttributes* targAtt = new G4VisAttributes(G4Colour::Green());
    	targAtt->SetForceSolid(true);
	targLV->SetVisAttributes(targAtt);
	
	// Place target in detector
	G4RotationMatrix TargetRot;
	TargetRot.set(0.,0.,0.);
	if(!GDH_orientation) TargetRot.rotateY(-90.0*deg);
	new G4PVPlacement(G4Transform3D(TargetRot, G4ThreeVector(0.,0.,0.)),
			targetLV, "Target", detectorLV, false, 0); 
	*/
		
	
	//------------------------------------------------------------------
	// Done with constructing the Geometry
	//------------------------------------------------------------------

	//Prints the material information
  	//G4cout << *(G4Element::GetElementTable()) <<G4endl;
  	//G4cout << *(G4Material::GetMaterialTable() ) << G4endl;

	//Prints volume information to the terminal
	//G4cout << G4endl;
	//G4cout << "Geometrical Tree:\n";
	//DumpGeometricalTree(experimentalHallPhys);
	//G4cout << G4endl;

	//we are now done
  	return experimentalHallPhys;

} //END OF BXDetectorConstruction:Construct()


//Prints the information about each volume: Taken from example A01
void BXDetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
	//spacing to make things look nice
  	for(G4int isp=0;isp<depth;isp++) { G4cout << "  "; }
  
	G4cout << aVolume->GetName() << "[";
	
	//if there is a number, print it.
	G4int copyNo = aVolume->GetCopyNo();
	if(copyNo >= 0) {
		G4cout << copyNo;}
	else if( aVolume->IsParameterised() ){
		G4cout << "P";}
	else if( aVolume->IsReplicated() ){
		G4cout << "R";}

  	G4cout << "] " << aVolume->GetLogicalVolume()->GetName() << " ";
        G4cout << aVolume->GetLogicalVolume()->GetNoDaughters() << " ";
        G4cout << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
	
	//if a volume is a sensitive detector
  	if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
  	{
    		G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()->GetFullPathName();
  	}
  
	G4cout << G4endl;

	//recursivly call this function for all volumes
  	for(G4int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++) {
  		DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
		
} //End of DumpeGeometricalTree()


//End of DetectorConstruction.cc
