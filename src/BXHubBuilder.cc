//See BXHubBuilder.hh for more details
#include "BXHubBuilder.hh"

//Geant4 materials includes
#include "G4Material.hh"
#include "G4NistManager.hh"

//Geant4 geometry includes
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh" 

//visualisation includes
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//Parameterised volumes
#include "G4PVParameterised.hh"

//constructor does no work: only initializes
BXHubBuilder::BXHubBuilder()
{
	theHubLogicalVolume = 0;
	hubLength = 0.0;
	hubInnerRadius = 0.0;
	hubOuterRadius = 0.0;
}

//constructor builds the cell
G4int BXHubBuilder::Build(G4bool showContainer,G4bool useWireframe)
{
	//if they builder has already been sucessfully run
	if( theHubLogicalVolume != 0) return 1;

	G4NistManager* nist = G4NistManager::Instance();

	//get a pointer to the needed materials
	G4Material * Aluminum = nist->FindOrBuildMaterial("G4_Al");
	G4Material * Air      = nist->FindOrBuildMaterial("G4_AIR");

	//Checks these pointers for good results
	//if there is a problem, G4Material::GetMaterial() will output the bad Material's name
	if(Aluminum == 0 || Air == 0){
		G4cerr << "BXHubBuilder::Build() -> ERROR: Cannot find materials needed to build the cell." << G4endl;
		return 2; }

		
	//---------------------------------- The constant parameters
	
	//All parameters from CAD file Hub-rotating_2.dwb except where noted
	
	//Extends Geant4 to use inches since blowfish is designed using inches 
	const G4double in = 2.54*cm;

	//material thickness
	const G4double material_thickness = 0.5*in;

	//flange parameters
	const G4double flange_inner_diam = 8.5*in;
	const G4double flange_outer_diam = 11.0*in;

	//inner hub parameters
	const G4double ihub_inner_diam = 8.5*in;
	const G4double ihub_length = 4.5*in;

	//outer hub parameters
	const G4double ohub_inner_diam = 10.5*in;
	const G4double ohub_length = (14.0 + 31.0/32.0)*in;

	//overlap between inner and outer hub
	const G4double io_overlap = 0.5*in;

	//Arm connector paramters from inner_bar_l_3-b
	const G4double connector_inner_diam = 9.25*in;
	const G4double connector_outer_diam = 11.0*in; //This is an approximation
	
	
	//---------------------------------- Aluminum visual attributes 
	
	G4Colour yellowOffWhite = G4Colour(1.0,1.0,224.0/255.0);
	G4VisAttributes* hubAtt = new G4VisAttributes(yellowOffWhite); 
	if(useWireframe) 
	{
		hubAtt->SetForceWireframe(true); 
	}
	else 
	{
		hubAtt->SetForceSolid(true); 
	}

	
	//---------------------------------- The hub container
	
	//Contains the contents of the hub
		
	const G4double hubCont_Rmax = ohub_inner_diam/2.0 + material_thickness;
	const G4double hubCont_Rmin = ihub_inner_diam/2.0;
	const G4double hubCont_z =  (2.0*material_thickness + ihub_length + ohub_length - io_overlap)/2.0;
	const G4double hub_As = 0*deg; 	   //angle to begin at
	const G4double hub_AD = 360.0*deg; //angle to cover
	G4Tubs * hubContTubs = new G4Tubs("HubContTubs",hubCont_Rmin,hubCont_Rmax,hubCont_z,hub_As,hub_AD);
	
	//some of these parameters correspond to global varaibles
	//that other classes may need
	hubLength = 2.0*hubCont_z;
	hubInnerRadius = hubCont_Rmin;
	hubOuterRadius = hubCont_Rmax;
	
	//the global logical volume
	theHubLogicalVolume = new G4LogicalVolume(hubContTubs, Air,"HubContLV");

	//either show the wireframe container or make it invisible
	if(showContainer)
	{
  		G4VisAttributes* hubContAtt = new G4VisAttributes();
		hubContAtt->SetForceWireframe(true);
		hubContAtt->SetForceAuxEdgeVisible(true);
		theHubLogicalVolume->SetVisAttributes(hubContAtt);
	}
	else
	{
  		theHubLogicalVolume->SetVisAttributes( G4VisAttributes::Invisible);
	}

	
	//---------------------------------- The hub/arm connector
	
	//Peice that the arms are connected
	
	const G4double connect_Rmax = connector_outer_diam/2.0;
	const G4double connect_Rmin = connector_inner_diam/2.0;
	const G4double connect_z = material_thickness/2.0;
	G4Tubs * connectTubs = new G4Tubs("ArmConnectorTubs",connect_Rmin,connect_Rmax,connect_z,hub_As,hub_AD);
	
	//the connector's logical volume
	G4LogicalVolume * connectLV = new G4LogicalVolume(connectTubs, Aluminum,"ArmConnectorLV");
	connectLV->SetVisAttributes(hubAtt);
	
	//place the connector in the container
	const G4double connect_pz = hubCont_z - connect_z;
	const G4ThreeVector connectPos = G4ThreeVector(0.0,0.0,connect_pz);

	new G4PVPlacement(0, connectPos, connectLV, "ArmConnectorPhys",theHubLogicalVolume,false,0); 


	//---------------------------------- The flange
	
	const G4double flange_Rmax = flange_outer_diam/2.0;
	const G4double flange_Rmin = flange_inner_diam/2.0;
	const G4double flange_z = material_thickness/2.0;
	G4Tubs * flangeTubs = new G4Tubs("HubFlangeTubs",flange_Rmin,flange_Rmax,flange_z,hub_As,hub_AD);
	
	//the flange's logical volume
	G4LogicalVolume * flangeLV = new G4LogicalVolume(flangeTubs, Aluminum,"HubFlangeLV");
	flangeLV->SetVisAttributes(hubAtt);
	
	//place the flange in the container
	const G4double flange_pz = connectPos.z() - connect_z - flange_z;
	const G4ThreeVector flangePos = G4ThreeVector(0.0,0.0,flange_pz);

	new G4PVPlacement(0, flangePos, flangeLV, "HubFlangePhys",theHubLogicalVolume,false,0); 

	
	//---------------------------------- The inner hub
	
	//Connects the flange to the outer hub and turns in the outer hub
	
	const G4double inner_Rmax = ihub_inner_diam/2.0 + material_thickness;
	const G4double inner_Rmin = ihub_inner_diam/2.0;
	const G4double inner_z = ihub_length/2.0;
	G4Tubs * innerTubs = new G4Tubs("InnerHubTubs",inner_Rmin,inner_Rmax,inner_z,hub_As,hub_AD);

	//the inner hub's logical volume
	G4LogicalVolume * innerLV = new G4LogicalVolume(innerTubs, Aluminum,"InnerHubLV");
	innerLV->SetVisAttributes(hubAtt);

	//place the inner hub in the container
	const G4double inner_pz = flangePos.z() - flange_z - inner_z;
	const G4ThreeVector innerPos = G4ThreeVector(0.0,0.0,inner_pz);
	
	new G4PVPlacement(0, innerPos, innerLV, "InnerHubPhys",theHubLogicalVolume,false,0); 
	
	//---------------------------------- The outer hub
	
	//connects the array to the frame: spins relative to the inner hub
	
	const G4double outer_Rmax = ohub_inner_diam/2.0 + material_thickness;
	const G4double outer_Rmin = ohub_inner_diam/2.0;
	const G4double outer_z = ohub_length/2.0;
	G4Tubs * outerTubs = new G4Tubs("OuterHubTubs",outer_Rmin,outer_Rmax,outer_z,hub_As,hub_AD);

	//the outer hub's logical volume
	G4LogicalVolume * outerLV = new G4LogicalVolume(outerTubs, Aluminum,"OuterHubLV");
	outerLV->SetVisAttributes(hubAtt);

	//place the outer hub in the container
	const G4double outer_pz = -hubCont_z + outer_z;
	const G4ThreeVector outerPos = G4ThreeVector(0.0,0.0,outer_pz);
	
	new G4PVPlacement(0, outerPos, outerLV, "OuterHubPhys",theHubLogicalVolume,false,0);

	//---------------------------------- Done with geometry
	
	return 0;
		
}//end of Build()


//EOF BXHubBuilder.cc
