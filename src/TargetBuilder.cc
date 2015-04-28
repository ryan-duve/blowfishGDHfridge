// C++ includes
#include<iostream>

///// GEANT includes

//Geant4 materials includes
#include "G4Material.hh"
#include "G4NistManager.hh"

//Geant4 geometry include
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

//My files
#include "TargetBuilder.hh"
//#include "FridgeConstants.hh"
#include "FridgeMaterials.hh" 

//visualisation includes
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

TargetBuilder::TargetBuilder( G4double targHoldR, G4double targHoldH, G4double targHoldTh)
:targHold_log(0),target_log(0),targHold_tube(0),target_tube(0)
{

  //Assigns material to target
  FridgeMaterials* mat = FridgeMaterials::getInstance();
  G4Material *shell_mat   = mat->getPlas(); 
  G4Material *target_mat = mat->getdBut(); 
  G4double startingAngle = 0; G4double spanningAngle = 360*deg;
  
  //creates target shell
  targHold_tube  = new G4Tubs("tube",  //name
			   0.,
			   targHoldR,
			   targHoldH/2.,
			   startingAngle,
			   spanningAngle);
  
  target_tube = new G4Tubs("inner_tube", 
			   0., 
			   targHoldR-targHoldTh, 
			   targHoldH/2.-targHoldTh, 
			   startingAngle, 
			   spanningAngle); 
  
  //creats logical volume for shell
  targHold_log  = new G4LogicalVolume(targHold_tube,shell_mat,"tube_log");
  G4cout<<"Target holder material "<< targHold_log->GetMaterial()->GetName() <<G4endl;

  // LV for target material
  target_log = new G4LogicalVolume(target_tube, target_mat, "inner_log");
  G4cout<<"Target material "<< target_log->GetMaterial()->GetName() <<G4endl;

  // place targ material inside the target holder  
  new G4PVPlacement(0,		    
		    G4ThreeVector(0.,0.,0),
		    target_log,
		    "Target",
		    targHold_log,
		    false,
		    0);
  
  //change color
  G4VisAttributes* target_att = new G4VisAttributes(G4Colour::Red());
  target_att->SetForceSolid(true);
  target_log->SetVisAttributes(target_att);
  G4VisAttributes* target_holder_att = new G4VisAttributes(G4Colour::Green());
  target_holder_att->SetForceSolid(true);
  targHold_log->SetVisAttributes(target_holder_att);
  //target_log->SetVisAttributes(G4VisAttributes::Invisible);  
  //why is this physically placing an object BUT then only returning a logical volume? Why is the placement not elsewhere?   
  //  target_phys = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),target_log,"target",outer_log,false,0);
 
}




