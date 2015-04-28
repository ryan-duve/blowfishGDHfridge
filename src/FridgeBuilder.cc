
//KEEP IN MIND
//cylinders are hollowed on side of mixing chamber, need to be blocked off
#include<iostream>
 
#include "FridgeBuilder.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"

//#include "constants.h"
#include "TargetBuilder.hh" 
#include "ShellBuilder.hh"
#include "PipeBuilder.hh"
#include "FridgeMaterials.hh"
//#include "MishMash.h"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
FridgeBuilder::FridgeBuilder()
  :bottle_shape(0),gas_bottle(0),
   outerGas(0), gas_one(0), gasOne_logic(0),
   copperCone(0), 
   gasTwo_logic(0),
   gasThree_logic(0),
   gasFour_logic(0),gasFour_physi(0),
   mixing_tube(0),sub_logic(0),
   gas_logic(0),
   mixing_physi(0),gas_physi(0),
   window(0),window_logic(0),window_physi(0),
   pipe_logic(0),pipe_physi(0),
   target_logic(0),target_physi(0),
   shellOneMatter(0),gasOneMatter(0),
   shellTwoMatter(0),gasTwoMatter(0),
   shellThreeMatter(0),gasThreeMatter(0),
   shellFourMatter(0),gasFourMatter(0),
   copperConeMatter(0),mixChMatter(0),
   mixGasMatter(0),mixTubeMatter(0),
   kaptonWindowMatter(0),pipeMatter(0),
   gasPipeMatter(0),rotate(0)
 
{
  //FridgeMaterials* mat = FridgeMaterials::getInstance();
  //mat->ConstructAllMaterials();
  
  rotate = new G4RotationMatrix; // no rotation needed

// the icc file includes all the constants needed
#include "FridgeConstants.icc"
G4bool Visible_gas = false;

  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
 
  ConstructMaterial();
  //------------Detector Geometry 
  // Outermost Gas Shell   
  ShellBuilder shellOne(shellOne_narrowRad, //narrow radius
			shellOne_wideRad, //wide radius
			shellOne_delta, //change in length of cone
			shellOne_thick, //cm thickness
			shellOne_narrowHeight, //narrow height
			shellOne_wideHeight, //wide height
			0, //offset
			shellOneMatter,
			gasOneMatter); 
  
  //gets pointer for mother LV 
  bottle_shape = shellOne.GetShellObject(); //UnionSolid 
  gas_bottle = shellOne.GetGasObject();     //UnionSolid
  //outermost_shellLV = shellOne.GetLVPointer();
  
  ///Gas cone to be added to end of gas LV
  outerGas  = new G4Cons("cone",  
			 0,     //inner radius
			 shellOne_wideRad,  //4.5 outer radius (small)  
			 0,             //inner radius
			 outerCone_radius,    //9.5outer radius (big)
			 (outerCone_delta)/2,           // cone half height
			 startingAngle,
			 spanningAngle); //cone piece
  
  gas_one = new G4UnionSolid( "gas_ending_funnel", 
			      gas_bottle,
			      outerGas,
			      rotate,
			      G4ThreeVector(0,
					    0,
					    shellOne_narrowHeight/2.+
					    shellOne_delta +
					    shellOne_wideHeight+
					    outerCone_delta/2.
					    )
			      ); //boolean solid
  gasOne_logic = new G4LogicalVolume(gas_one, gasOneMatter, "outerShellLV");
  
  //------------------Copper Cone--------------------/
  //creates outermost copper cone
  
  copperCone  = new G4Cons("cone",  
			   shellOne_wideRad-shellOne_thick,     //inner radius
			   shellOne_wideRad,  //mm outer radius (small)  
			   outerCone_radius-shellOne_thick,             //inner radius
			   outerCone_radius,    //mm outer radius (big)
			   outerCone_delta/2,           //change in angle of cone
			   startingAngle,
			   spanningAngle); //cone piece

  outer_shell = new G4UnionSolid( "outermost_shell",
                                  bottle_shape,
                                  copperCone,
                                  rotate,
                                  G4ThreeVector(0,
						0,
						shellOne_narrowHeight/2.+
						shellOne_delta +
						shellOne_wideHeight+
						outerCone_delta/2.)
				  ); //boolean solid
  outer_shellLV = new G4LogicalVolume(outer_shell, shellOneMatter, "outermost_shell");
  
  outer_shellPV =  new G4PVPlacement(0,
				     G4ThreeVector(0.,0.,0.),
				     outer_shellLV,
				     "coppercone",
				     gasOne_logic,
				     false,
				     0);

  // make all gasses Yellow when we want to see them
  if(Visible_gas)
	{
	G4VisAttributes* gasOne_logic_att = new G4VisAttributes(G4Colour::Yellow());
	gasOne_logic_att->SetForceSolid(true);
	gasOne_logic->SetVisAttributes(gasOne_logic_att);
	}
  else
	{
	gasOne_logic->SetVisAttributes(G4VisAttributes::Invisible);
	}

  G4VisAttributes* outer_shellLV_att = new G4VisAttributes(G4Colour::Red());
  //shell1attrb->SetForceWireframe(true);
  outer_shellLV_att->SetForceSolid(true);
  outer_shellLV->SetVisAttributes(outer_shellLV_att);
  //  outer_shellLV->SetVisAttributes(G4Colour::Blue());
  //  outer_shellLV->SetVisAttributes(G4VisAttributes::Invisible);

  
  //return;
  
  //---------------------1st  Cu/He mixture--------------------//
  //-------------------------------Tube1 (wide)---------------/
  
  mash_Tube1= new G4Tubs("MishMash",
			 tube1_inner,             //inner radius
			 tube1_outer,  //outer radius
			 tube1_height/2,  //height
			 startingAngle,
			 spanningAngle);//skinny cyllinder
  
  tube1_logic = new G4LogicalVolume(mash_Tube1, Mix75He25Cu, "mix_tube_wide");
  
  G4VisAttributes* mishattrb = new G4VisAttributes(G4Colour::Brown());
  mishattrb->SetForceSolid(true);
  tube1_logic->SetVisAttributes(mishattrb);
  //  tube1_logic->SetVisAttributes(G4VisAttributes::Invisible);
  
  tube1_physi = new G4PVPlacement(0,
				  G4ThreeVector(0.,0.,tube1_offset),
				  tube1_logic,
				  "MixTube1",
				  gasOne_logic,
				  false,
				  0);

   // return;

  //-------------------Vacuum nose--------------------/
  ShellBuilder shellTwo(shellTwo_narrowRad, //narrow radius
			shellTwo_wideRad, //wide radius
			shellTwo_delta, //height of cone
			shellTwo_thick, //thickness
			shellTwo_narrowHeight, //narrow height
			shellTwo_wideHeight, //wide height
			0, //cm offset
			shellTwoMatter,
			gasTwoMatter);

  
  //gasTwo_logic = shellTwo.GetGasLVPointer();
  mid_bottle = shellTwo.GetShellObject(); //UnionSolid 
  gas_mid = shellTwo.GetGasObject();     //UnionSolid
  
  //Middle gas cone to be added to end of gas LV
  middleConeGas  = new G4Cons("cone",
			      0,     //inner radius
			      shellTwo_wideRad,  //4.5cm outer radius (small)  
			      0,             //inner radius
			      middleCone_radius,    //9.5outer radius (big)<--8.6cm in icc file??
			      (middleCone_delta)/2,           
			      startingAngle,
			      spanningAngle); //cone piece
  
  gas_two = new G4UnionSolid( "gas_middle_funnel",
			      gas_mid,
			      middleConeGas,
			      rotate,
			      G4ThreeVector(0,
					    0,
					    shellTwo_narrowHeight/2.+
					    shellTwo_delta +
					    shellTwo_wideHeight+
					    middleCone_delta/2.			    
					    )
			      ); //boolean solid
  
  gasTwo_logic = new G4LogicalVolume(gas_two, gasTwoMatter, "middleGasLV")    ;

  if(Visible_gas)
	{
	G4VisAttributes* gasTwo_att = new G4VisAttributes(G4Colour::Yellow());
	gasTwo_att->SetForceSolid(true);
	gasTwo_logic->SetVisAttributes(gasTwo_att);
	}
  else
	{
	gasTwo_logic->SetVisAttributes(G4VisAttributes::Invisible);
	}
  
  //Middle Cone
  middleCone  = new G4Cons("cone",
			   shellTwo_wideRad-shellTwo_thick,   //inner radius
			   shellTwo_wideRad,  //mm outer radius (small)  
			   middleCone_radius-shellTwo_thick,     //inner radius
			   middleCone_radius,    //mm outer radius (big)
			   middleCone_delta/2,           //change in angle of cone
			   startingAngle,
			   spanningAngle); //cone piece

  middle_shell = new G4UnionSolid( "middle_shell",
				   mid_bottle,
				   middleCone,
				   rotate,
				   G4ThreeVector(0,
						 0,
						 shellTwo_narrowHeight/2.+
						 shellTwo_delta +
						 shellTwo_wideHeight+
						 middleCone_delta/2.)
				   ); //boolean solid 
  
  middle_shellLV = new G4LogicalVolume(middle_shell, shellTwoMatter, "middle_shell");
  
  G4VisAttributes* midshell_att = new G4VisAttributes(G4Colour::Magenta());
  midshell_att->SetForceSolid(true);
  middle_shellLV->SetVisAttributes(midshell_att);
  
  
  middle_shellPV =  new G4PVPlacement(0,
				      G4ThreeVector(0.,0.,0),
				      middle_shellLV,
				      "middle_coppercone",
				      gasTwo_logic,
				      false,
				      0);
  
  
  middle_gasPV =  new G4PVPlacement(0,
				    G4ThreeVector(0.,0.,gas_two_offset),
				    gasTwo_logic,
				    "middle_gascone",
				    gasOne_logic,
				    false,
				    0);


  //  return;
  //------------------Copper Shield--------------------//
  ShellBuilder shellThree(shellThree_narrowRad, //narrow radius
			  shellThree_wideRad, //wide radius
			  shellThree_delta, // change in length of cone
			  shellThree_thick, //thickness
			  shellThree_narrowHeight, //narrow height
			  shellThree_wideHeight, //wide height
			  0, //cm offset
			  shellThreeMatter,
			  gasThreeMatter);
  
  in_bottle = shellThree.GetShellObject(); //UnionSolid 
  gas_in = shellThree.GetGasObject();     //UnionSolid
  
  innerConeGas  = new G4Cons("cone",
			     0,     //inner radius
			     shellThree_wideRad,  //4.5 outer radius (small)  
			     0,             //inner radius
			     innerCone_radius,    //9.5outer radius (big)
			     (innerCone_delta)/2, //
			     startingAngle,
			     spanningAngle); //cone piece
  
  gas_three = new G4UnionSolid( "gas_inner_funnel",
				gas_in,
				innerConeGas,
				rotate,
				G4ThreeVector(0,
					      0,
					      shellThree_narrowHeight/2.+
					      shellThree_delta +
					      shellThree_wideHeight+
					      innerCone_delta/2.
					      )				
				); //boolean solid
  gasThree_logic = new G4LogicalVolume(gas_three, gasThreeMatter, "innerShellLV");

  if(Visible_gas)
	{
	G4VisAttributes* gasThree_att = new G4VisAttributes(G4Colour::Yellow());
	gasThree_att->SetForceSolid(true);
	gasThree_logic->SetVisAttributes(gasThree_att);
	}
  else
	{
	gasThree_logic->SetVisAttributes(G4VisAttributes::Invisible);
	}
  //innermost cone 
  innerCone  = new G4Cons("cone",
			  shellThree_wideRad-shellThree_thick,   //inner radius
			  shellThree_wideRad,  //mm outer radius (small)  
			  innerCone_radius-shellThree_thick,     //inner radius
			  innerCone_radius,    //mm outer radius (big)
			  innerCone_delta/2,           //change in angle of cone
			  startingAngle,
			  spanningAngle); //cone piece
  
  
  inner_shell = new G4UnionSolid( "inner_shell",
				  in_bottle,
				  innerCone,
				  rotate,
				  G4ThreeVector(0,
						0,
						shellThree_narrowHeight/2.+
						shellThree_delta +
						shellThree_wideHeight+
						innerCone_delta/2.)
				  ); //boolean solid 
  
  
  inner_shellLV = new G4LogicalVolume(inner_shell, copperConeMatter, "inner_shell");
  G4VisAttributes* inner_shell_att = new G4VisAttributes(G4Colour::Red());
  inner_shell_att->SetForceSolid(true);
  inner_shellLV->SetVisAttributes(inner_shell_att);
  //  inner_shellLV->SetVisAttributes(G4VisAttributes::Invisible);
  //
  inner_shellPV =  new G4PVPlacement(0,
				     G4ThreeVector(0.,0.,0.),
				     inner_shellLV,
				     "inner_coppercone",
				     gasThree_logic,
				     false,
				     0);

  inner_gasPV =  new G4PVPlacement(0,
				   G4ThreeVector(0.,0.,gas_three_offset),
				   gasThree_logic,
				   "inner_gascone",
				   gasTwo_logic,
				   false,
				   0);
  
  
  //  return;
  
  //----------------------------Shell Four
  
  ShellBuilder shellFour(shellFour_narrowRad, //narrow radius
			 shellFour_wideRad, // wide radius
			 shellFour_delta,//change in length of cone
			 shellFour_thick, //thickness
			 shellFour_narrowHeight, //narrow height
			 shellFour_wideHeight, //wide height
			 0, //cm offset
			 shellFourMatter,
			 gasFourMatter);
  
  four_bottle = shellFour.GetShellObject(); 
  gasFour_bottle  = shellFour.GetGasObject();     //UnionSolid
  
  fourthConeGas  = new G4Cons("fourthCone",
			      0,     //inner radius
			      shellFour_wideRad,  //4.5 outer radius (small)  
			      0,             //inner radius
			      fourthCone_radius,    //9.5outer radius (big)
			      (fourthCone_delta)/2, 
			      startingAngle,
			      spanningAngle); //cone piece
  
  
  gas_four = new G4UnionSolid( "gas_inner_funnel",
			       gasFour_bottle,
			       fourthConeGas,
			       rotate,
			       G4ThreeVector(0,
					     0,
					     shellFour_narrowHeight/2.+
					     shellFour_delta +
					     shellFour_wideHeight+
					     fourthCone_delta/2.
					     )
			       ); //boolean solid
  
  fourthCone  = new G4Cons("cone",
			   shellFour_wideRad-shellFour_thick,   //inner r    adius
			   shellFour_wideRad,  //mm outer radius (small)  
			   fourthCone_radius-shellFour_thick,     //inner radi    us
			   fourthCone_radius,    //mm outer radius (big)
			   fourthCone_delta/2,           //change in angle of cone
			   startingAngle,
			   spanningAngle); //cone piece
  
  
  fourth_shell = new G4UnionSolid( "inner_shell",
				   four_bottle,
				   fourthCone,
				   rotate,
				   G4ThreeVector(0,
						 0,
						 shellFour_narrowHeight/2.+
						 shellFour_delta +
						 shellFour_wideHeight +
						 fourthCone_delta/2.
						 )
				   ); //boolean solid
  
  fourthTube = new G4Tubs("fourth_tube", //name
			  fourthCone_radius-shellFour_thick,     //inner rad
			  fourthCone_radius,
			  tub_height/2, 
			  startingAngle,
			  spanningAngle);
  
  fourthGasTube =  new G4Tubs("fourth_tube", //name
			      0,     //inner rad
			      fourthCone_radius,
			      tub_height/2,
			      startingAngle,
			      spanningAngle);  

  fourth_object = new G4UnionSolid("inner_object",
				   fourth_shell,
				   fourthTube,
				   rotate,
				   G4ThreeVector(0,
						 0,
						 shellFour_narrowHeight/2.+
						 shellFour_delta +
						 shellFour_wideHeight +
						 fourthCone_delta +
						 tub_height/2.
						 )
				   ); //boolean solid

  fourth_gas_object =  new G4UnionSolid("inner_object",
					gas_four,
					fourthGasTube,
					rotate,
					G4ThreeVector(0,
						      0,
						      shellFour_narrowHeight/2.+
						      shellFour_delta +
						      shellFour_wideHeight +
						      fourthCone_delta +
						      tub_height/2.
						      )
					); //boolean solid
  
  
  gasFour_logic = new G4LogicalVolume(fourth_gas_object, gasFourMatter, "fourthGas_shell");

  if(Visible_gas)
	{
	G4VisAttributes* gasFour_att = new G4VisAttributes(G4Colour::Yellow());
	gasFour_att->SetForceSolid(true);
	gasFour_logic->SetVisAttributes(gasFour_att);
	}
  else
	{
	gasFour_logic->SetVisAttributes(G4VisAttributes::Invisible);
	}
  
  shellFour_logic = new G4LogicalVolume(fourth_object, copperConeMatter, "fourth_shell");

  G4VisAttributes* shellFour_att = new G4VisAttributes(G4Colour::Blue());
  shellFour_att->SetForceSolid(true);
  shellFour_logic->SetVisAttributes(shellFour_att);
  //  shellFour_logic->SetVisAttributes(G4VisAttributes::Invisible);
  
  shellFour_physi =  new G4PVPlacement(0,
				       G4ThreeVector(0.,0.,0),
				       shellFour_logic,
				       "fourth_coppercone",
				       gasFour_logic,
				       false,
				       0);
  
  
  gasFour_physi =  new G4PVPlacement(0,
				     G4ThreeVector(0.,0.,gas_four_offset),
				     gasFour_logic,
				     "gas Four",
				     gasThree_logic,
				     false,
				     0);
  //  return;
  //-------------------------------Tube3 (narrow)---------------/
  tube3_inner = mixing_wideRad; 
  
  mash_Tube3= new G4Tubs("MishMash3",
			 tube3_inner,             //inner radius
			 tube3_outer,  //outer radius
			 tube3_height/2,  //height
			 startingAngle,
			 spanningAngle);//skinny cyllinder
  
  tube3_logic = new G4LogicalVolume(mash_Tube3, 
				    Mix50He50Cu, 
				    "mix_tube3_narrow");
  
  G4VisAttributes* mishattrb2 = new G4VisAttributes(G4Colour::Green());
  mishattrb2->SetForceSolid(true);
  tube3_logic->SetVisAttributes(mishattrb2);
  
  
  tube3_physi = new G4PVPlacement(0,
				  G4ThreeVector(0.,0.,tube3_offset),
				  tube3_logic,
				  "MixTube3",
				  gasFour_logic,
				  false,
				  0);
  
  // return;
  
  //--------------------------------End MishMash Tube3------------/
  //----------------creates mixing chamber
  
  //creates mother shell for the mixing chamber
  ShellBuilder mixingChamber(mixing_narrowRad, //inner radius
			     mixing_wideRad, //outer radius
			     mixing_delta,   //pDz
			     mixing_thick,   //thickness
			     mixing_narrowHeight, //narrow height
			     mixing_wideHeight, //wide height
			     0,
			     mixChMatter, //material
			     mixGasMatter); 
  
  //Mother LV of mixing chamber, consisting of mixing chamber gas 
  gas_logic = mixingChamber.GetGasLVPointer();

  if(Visible_gas)
	{
	G4VisAttributes* gas_logic_att = new G4VisAttributes(G4Colour::Yellow());
	gas_logic_att->SetForceSolid(true);
	gas_logic->SetVisAttributes(gas_logic_att);
	}
  else
	{
	gas_logic->SetVisAttributes(G4VisAttributes::Invisible);
	}
  
  //places the gas inside of the fourth shell
  gas_physi =  new G4PVPlacement(0,
				 G4ThreeVector(0.,0.,mixing_off),
				 gas_logic,
				 "mixing_gas",
				 gasFour_logic,
				 false,
				 0);
  
  
  //get cylinder
  mixing_tube = new G4Tubs("MixingChamber_tube",
			   mixing_tube_rad-mixing_tube_thick,             //inner radius
			   mixing_tube_rad,  //outer radius
			   mixing_tube_height/2,
			   startingAngle,      
			   spanningAngle);//skinny cyllinder
  
  
  sub_logic = new G4LogicalVolume(mixing_tube, mixTubeMatter, "mixingCh");
  
  
  G4VisAttributes* sub_logic_att = new G4VisAttributes(G4Colour::Magenta());
  sub_logic_att->SetForceSolid(true);
  sub_logic->SetVisAttributes(sub_logic_att);
  //  sub_logic->SetVisAttributes(G4VisAttributes::Invisible);
  
  //physical volumes
  mixing_physi = new G4PVPlacement(0,
				   G4ThreeVector(0.,0.,mixing_tube_off),
				   sub_logic,
				   "mixingChamber_tube",
				   gas_logic,
				   false,
				   0);

  //return;
  //---------------------------- Window -----------------------------//
  window = new G4Tubs("kapton_tube",
		      0,             //inner radius
		      2.5*cm,  //outer radius
		      .1*cm,  //height
		      startingAngle,      
		      spanningAngle);//skinny cyllinder
  
  window_logic = new G4LogicalVolume(window, kaptonWindowMatter, "windowLV");
  
  G4VisAttributes* attrwind = new G4VisAttributes(G4Colour::Blue());
  attrwind->SetForceSolid(true);
  window_logic->SetVisAttributes(attrwind);

  // Put window right in front of mixing chamber
  // Calculating mix chamber height
  G4double mixChamTotH = (mixing_delta + mixing_narrowHeight/2. + mixing_wideHeight); 

  window_offset = mixChamTotH + mixing_off + 1.*mm; //
  
  window_physi = new G4PVPlacement(0,
				   G4ThreeVector(0.,0.,window_offset),
				   window_logic,
				   "Window",
				   gasFour_logic, 
				   false, 
				   0);

  //return;

  // Inner pipe  
  PipeBuilder pipe(pipeRadius, //radius
		   pipeThickness, //thickness
		   heightA, //heightA
		   heightB, //heightB
		   heightC, //heightC
		   heightD, //heightD
		   //heightE, //heightE
		   alpha_ang, //degree alpha rotation angle
		   beta_ang); //degree beta rotation angle
  
  pipe_logic = pipe.GetLVPointer();

  G4VisAttributes* attrpipe = new G4VisAttributes(G4Colour::Cyan());
  attrpipe->SetForceSolid(true);
  pipe_logic->SetVisAttributes(attrpipe);
  
  pipe_physi = new G4PVPlacement(0,
				 G4ThreeVector(0.,.85*cm,.4*cm),
				 pipe_logic,
				 "Pipe",	
				 gas_logic,
				 false,
				 0);

  //return;
  //---------------------------Target----------------------------//
    TargetBuilder target(targHoldR, targHoldH, targHoldTh); 

  target_logic = target.GetLVPointer();  // actually the target holder
  // attributes already set in TargetBuilder
  //   G4VisAttributes* attrtarg = new G4VisAttributes(G4Colour(0,1,0));
  //G4VisAttributes* attrtarg = new G4VisAttributes(G4Colour::Red());
  //attrtarg->SetForceSolid(true);
  //target_logic->SetVisAttributes(attrtarg);
  
  target_physi = new G4PVPlacement(0,
				   G4ThreeVector(0,0,0),
				   target_logic,
				   "Target Holder",
				   sub_logic,
				   false,
				   0);
  
  //////for checking
  /*
  // 4 shells
  gasOne_logic->SetVisAttributes(G4VisAttributes::Invisible);
  //  outer_shellLV->SetVisAttributes(G4VisAttributes::Invisible);
  gasTwo_logic->SetVisAttributes(G4VisAttributes::Invisible);
  //  middle_shellLV->SetVisAttributes(G4VisAttributes::Invisible);
  gasThree_logic->SetVisAttributes(G4VisAttributes::Invisible);
  //  inner_shellLV->SetVisAttributes(G4VisAttributes::Invisible);
  gasFour_logic->SetVisAttributes(G4VisAttributes::Invisible);
  //  shellFour_logic->SetVisAttributes(G4VisAttributes::Invisible);

  // artificial "mishmash"
  //tube1_logic->SetVisAttributes(G4VisAttributes::Invisible);
  //tube3_logic->SetVisAttributes(G4VisAttributes::Invisible);

  //mixing chamber 
  //  sub_logic->SetVisAttributes(G4VisAttributes::Invisible);
  gas_logic->SetVisAttributes(G4VisAttributes::Invisible);
  
  // kapton window
  //  window_logic->SetVisAttributes(G4VisAttributes::Invisible);

  // inside pipe
  //  pipe_logic->SetVisAttributes(G4VisAttributes::Invisible);
  
  // target
  //  target_logic->SetVisAttributes(G4VisAttributes::Invisible);
  */

  //////////// materials
  // shell 1
  G4cout<<"gasOne material "<< gasOne_logic->GetMaterial()->GetName() <<G4endl;
  G4cout<<"outer_shellLV material "<< outer_shellLV->GetMaterial()->GetName() <<G4endl;
  // shell 2
  G4cout<<"gasTwo material "<< gasTwo_logic->GetMaterial()->GetName() <<G4endl;
  G4cout<<"middle_shellLV material "<< middle_shellLV->GetMaterial()->GetName() <<G4endl;
  // shell 3
  G4cout<<"gasThree material "<< gasThree_logic->GetMaterial()->GetName() <<G4endl;
  G4cout<<"inner_shellLV material "<< inner_shellLV->GetMaterial()->GetName() <<G4endl;
  // shell 4
  G4cout<<"gasFour material "<< gasFour_logic->GetMaterial()->GetName() <<G4endl;
  G4cout<<"Shell four material "<< shellFour_logic->GetMaterial()->GetName() <<G4endl;
  // mixing chamber
  G4cout<<"Mix chamber 'gas' material "<< gas_logic->GetMaterial()->GetName() <<G4endl;
  G4cout<<"Mix chamber material "<< sub_logic->GetMaterial()->GetName() <<G4endl;
  // window
  G4cout<<"Kapton window material "<< window_logic->GetMaterial()->GetName() <<G4endl;
  // artificial tubes 
  G4cout<<"tube1 material "<< tube1_logic->GetMaterial()->GetName() <<G4endl;  
  G4cout<<"tube3 material "<< tube3_logic->GetMaterial()->GetName() <<G4endl;
}

G4double FridgeBuilder::GetOffset(void)
  {
// compute offset to make target center at (0,0,0)
  G4double target_shift = gas_two_offset
			+ gas_three_offset
			+ gas_four_offset
			+ mixing_off
			+ mixing_tube_off;
  return( target_shift);
  }

void FridgeBuilder::ConstructMaterial()
{
    
  //assigns various materials
  FridgeMaterials* mat = FridgeMaterials::getInstance();
  mat->ConstructAllMaterials();
  shellOneMatter = mat->getSS(); 
  shellTwoMatter = mat->getCu(); 
  shellThreeMatter = mat->getSS(); 
  shellFourMatter = mat->getSS();
  gasOneMatter = mat->getVac(); 
  gasTwoMatter = mat->getVac(); 
  gasThreeMatter = mat->getVac(); 
  gasFourMatter = mat->getGasHe4(); 
  copperConeMatter = mat->getSS(); 
  mixChMatter = mat->getPlas();  
  mixGasMatter = mat->getHeMix(); 
  mixTubeMatter = mat->getPlas(); //CHANGE TO PLASTIC!! 
  pipeMatter = mat->getAl(); 
  gasPipeMatter = mat->getLHe3(); 
  kaptonWindowMatter = mat->getKap(); 
  Mix75He25Cu = mat->getMix75He25Cu();
  Mix50He50Cu = mat->getMix50He50Cu();

  // Print all the materials defined.
  //
  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;



}
