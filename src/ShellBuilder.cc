// This will build the solid shell and return a logical volume 


#include <iostream>
#include "G4Tubs.hh"
#include "G4TwistedTubs.hh"
#include "G4UnionSolid.hh"
#include "G4Cons.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4Para.hh"

#include "FridgeMaterials.hh"
//#include "FridgeConstants.hh" 
#include "ShellBuilder.hh" 

//ShellBuilder::ShellBuilder()
//   {
//    DefineMaterials();
// }

ShellBuilder::ShellBuilder(G4double narrowR,
		G4double wideR,
		G4double pD,
		G4double thick,
		G4double narrowH,
		G4double wideH,
		G4double off_in,
		G4Material *sMat,
		G4Material *gMat) 
  : shell_log(0),shell_physi(0),gas_log(0),
    narrow_tube(0),blankoff(0),narrow_tube_blank(0),
    gas_narrow(0),wide_tube(0),gas_wide(0),
    cone(0),gas_cone(0),funnel(0),gas_funnel(0),
    shell(0),gas_shell(0),
    narrowRadius(narrowR),wideRadius(wideR),
    pDz(pD),thickness(thick),
    narrowHeight(narrowH),wideHeight(wideH),
    offset(off_in),
    rotation(0),shellMat(sMat),gasMat(gMat),
    micro_offset(0.01*mm),
    startingAngle(0.), spanningAngle(360*deg)
{
  DefineMaterials(); 

  G4bool with_blank = true;
  
  //Builds mother volume
  gas_narrow = new G4Tubs("gas_tube",       //narrow gas tube
			  0,                      //inner radius
			  narrowRadius+micro_offset, //outer radius
			  (narrowHeight+micro_offset)/2,    //half height
			  startingAngle,      
			  spanningAngle);
  
  
  narrow_tube = new G4Tubs("narrow_tube",
			   narrowRadius-thickness, //inner radius
			   narrowRadius,  //outer radius
			   (narrowHeight)/2,  //half height
			   startingAngle,      
			   spanningAngle);//skinny tube of shell

  blankoff = new G4Tubs("blank",
			0., //inner radius
			narrowRadius-micro_offset,   //outer radius
			thickness/2.,  //half height
			startingAngle,      
			spanningAngle);//skinny tube of shell

  
  narrow_tube_blank = new G4UnionSolid( "narrow_tube_blank", 
					narrow_tube,
					blankoff,
					rotation,
					G4ThreeVector(0,
						      0,
						      -narrowHeight/2.+thickness/2.
						      )
					); //boolean solid 
  
  gas_cone = new G4Cons("gas_cone",
			0, //inner radius 
			narrowRadius+micro_offset, 
			0,
			wideRadius+micro_offset,
			pDz/2,
			startingAngle,
			spanningAngle); 
  
  cone = new G4Cons("cone",  
		    narrowRadius-thickness,     //inner radius
		    narrowRadius,  //outer radius (small)  
		    wideRadius-thickness,             //inner radius
		    wideRadius,    //outer radius (big)
		    (pDz)/2,           //change in angle of cone
		    startingAngle,
		    spanningAngle); //cone piece
  
  
  gas_funnel = new G4UnionSolid( "gas_funnel", 
				 gas_narrow,
				 gas_cone,
				 rotation,
			//	 G4ThreeVector(0,0,(narrowHeight+micro_offset)/2+pDz/2)); //boolean solid 
				 G4ThreeVector(0,0,(narrowHeight)/2+pDz/2)); //boolean solid 
  
  if(with_blank)
    funnel = new G4UnionSolid( "funnel", 
			       narrow_tube_blank,
			       cone,
			       rotation,
			       //			     G4ThreeVector(0,0,(narrowHeight-thickness)/2)); //boolean solid 
			       G4ThreeVector(0,0,(narrowHeight/2)+pDz/2)); //boolean solid
  else{
    G4cout<<"Without blanks"<<G4endl;
    funnel = new G4UnionSolid( "funnel", 
			       narrow_tube,
			       cone,
			       rotation,
			       //			     G4ThreeVector(0,0,(narrowHeight-thickness)/2)); //boolean solid 
			       G4ThreeVector(0,0,(narrowHeight/2)+pDz/2)); //boolean solid
  }
  
  gas_wide = new G4Tubs("wide_tube",
			0,                  //inner radius
			wideRadius+micro_offset,  //outer radius
			(wideHeight+micro_offset)/2, //half height
			startingAngle,
			spanningAngle); //wider tube
  
  wide_tube = new G4Tubs("wide_tube",
			 wideRadius-thickness, //inner radius
			 wideRadius,
			 (wideHeight+micro_offset)/2,  //half height
			 startingAngle,
			 spanningAngle); //wider tube
  
  
  gas_shell = new G4UnionSolid( "pipe", 
				gas_funnel,
				gas_wide,
				rotation,
				//G4ThreeVector(0,0,((narrowHeight+micro_offset)/2+(pDz+micro_offset)+(wideHeight+micro_offset)/2))); //connects wider tube to funnel
				G4ThreeVector(0,0,((narrowHeight)/2+(pDz)+(wideHeight)/2))); //connects wider tube to funnel
  
  
  shell = new G4UnionSolid( "joint_shell", 
			    funnel,
			    wide_tube,
			    rotation,       
			    G4ThreeVector(0,0,(narrowHeight)/2+(wideHeight)/2+(pDz))); //connects wider tube to funnel
  
  //  G4cout<<"shellMat "<<shellMat<<G4endl;
  shell_log = new G4LogicalVolume(shell, shellMat,"shellLV"); //returns logical volume
  G4VisAttributes* attrbs = new G4VisAttributes(G4Colour(1,1,0));
  attrbs->SetForceSolid(true);
  shell_log->SetVisAttributes(attrbs);
  
 
  gas_log = new G4LogicalVolume(gas_shell, gasMat,"gasLV"); //returns logical volume
  
  G4VisAttributes* gattrbs = new G4VisAttributes(G4Colour(1,0,0));
  gattrbs->SetForceSolid(true);
  gas_log->SetVisAttributes(gattrbs);
  
  shell_physi = new G4PVPlacement(0,
				  G4ThreeVector(0,0,micro_offset+offset),
				  shell_log, 
				  "shell",
				  gas_log,
				  false,
				  0);
    
}


//setters
void ShellBuilder::set_narrowRadius(G4double new_narrowRadius){  narrowRadius = new_narrowRadius;}
void ShellBuilder::set_wideRadius(G4double new_wideRadius){ wideRadius = new_wideRadius; }
void ShellBuilder::set_thickness(G4double new_thickness){ thickness = new_thickness;}
void ShellBuilder::set_narrowHeight(G4double new_narrowHeight){ narrowHeight = new_narrowHeight;}
void ShellBuilder::set_wideHeight(G4double new_wideHeight){ wideHeight = new_wideHeight;}
void ShellBuilder::set_shellMat(G4Material* new_shellMat){shellMat = new_shellMat;}
void ShellBuilder::set_gasMat(G4Material* new_gasMat){gasMat= new_gasMat;}

void ShellBuilder::DefineMaterials()
{
  //  G4cout<<"shellMat "<<shellMat<<G4endl;
  
  FridgeMaterials* mat = FridgeMaterials::getInstance();
  //assigns materials as needed   
  if(shellMat == NULL) shellMat = mat->getAl();  //default material
  if(gasMat == NULL) gasMat = mat->getVac();   //default gas material

  //  G4cout<<"shellMat "<<shellMat<<G4endl;
  
  //does no reassign
  //all shells  
}
