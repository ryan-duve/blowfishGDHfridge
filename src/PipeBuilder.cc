// This will build the solid pipe and return a logical volume 


#include <iostream>
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4CutTubs.hh"
//#include "math.h" 

#include "G4SubtractionSolid.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"


//#include "FridgeConstants.hh" 
#include "PipeBuilder.hh" 
#include "FridgeMaterials.hh" 

PipeBuilder::PipeBuilder()
  {
    rotation = new G4RotationMatrix(); 
    rotation_B = new G4RotationMatrix(); 
    DefineMaterials();
   }

PipeBuilder::PipeBuilder(G4double rad_in,
	G4double thick,
	G4double a,
	G4double b,
	G4double c,
	G4double d,
	G4double alp,
	G4double bet ) 
  : pipe_log(0),
    tubeA(0),tubeB(0),tubeC(0),tubeD(0),
    sectionAB(0),sectionABC(0),sectionABCD(0),
    radius(rad_in),thickness(thick),
    heightA(a),heightB(b),heightC(c),heightD(d),
    alpha(alp),beta(bet)
{
  rotation = new G4RotationMatrix(); 
  rotation_B = new G4RotationMatrix(); 
  DefineMaterials();
  G4double startingAngle = 0; G4double spanningAngle = 360*deg;
  
  tubeA = new G4Tubs("narrow_tube",
		     radius-thickness,             //center of world
		     radius,  //outer radius
		     heightA,  //height
		     startingAngle,      
		     spanningAngle
		     );//skinny cyllinder
      
  tubeB = new G4CutTubs("tubeB", //name
			radius-thickness, //pRMin
			radius, //pRMax
			heightB, //pDz
			startingAngle,
			spanningAngle, 
			G4ThreeVector(-1,-1,-1), //low norm
			G4ThreeVector(1,1,1)
			); //high norm
  //     G4cout<<"rotation "<<rotation<<G4endl;
  
  rotation->rotateX(alpha);
  rotation_B->rotateX(beta);
  rotation->rotateY(180*degree);
  rotation_B->rotateY(180*degree);
  
  sectionAB = new G4UnionSolid( "sectionAB", 
				tubeA,
				tubeB,
				rotation,
				G4ThreeVector(0,heightB*sin(alpha),heightA+heightB*cos(alpha))
				); //boolean solid 
  
  tubeC = new G4Tubs("tubeC",
		     radius-thickness,
		     radius,
		     heightC,
		     startingAngle,
		     spanningAngle
		     ); //wider tube
  
  sectionABC = new G4UnionSolid( "sectionABC", 
				 sectionAB,
				 tubeC,
				 0,       //rotation
				 G4ThreeVector(0,2*heightB*sin(alpha),heightA+2*heightB*cos(alpha)+heightC)
				 ); 
  
  tubeD = new G4CutTubs("tubeD", //name
			radius-thickness, //pRMin
			radius, //pRMax
			heightD, //pDz
			startingAngle,
			spanningAngle, 
			G4ThreeVector(-1,-1,-1), //low norm
			G4ThreeVector(1,1,1)
			); //high norm
  
  sectionABCD = new G4UnionSolid( "sectionABCD", 
				  sectionABC,
				  tubeD,
				  rotation_B,       //rotation
				  G4ThreeVector(0,
					2*heightB*sin(alpha)+heightD*sin(beta),
					heightA+2*heightB*cos(alpha)+2*heightC+heightD*cos(beta))
				  );  
  
  
  pipe_log = new G4LogicalVolume(sectionABCD, pipeMat,"pipeLV"); //returns logical volume

  G4cout<<"Pipe material "<< pipe_log->GetMaterial()->GetName() <<G4endl;
  
  G4VisAttributes* attr = new G4VisAttributes(G4Colour(0,1.,0));
  pipe_log->SetVisAttributes(attr);
  
  
  
}
void PipeBuilder::DefineMaterials()
{

  FridgeMaterials* mat = FridgeMaterials::getInstance();

  pipeMat = mat->getAl();  //default materials - Aluminum

}

