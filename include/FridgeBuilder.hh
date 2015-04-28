#ifndef myFridgeBuilder_H
#define myFridgeBuilder_H 1

#include "G4SystemOfUnits.hh"
//Geant4 includes
#include "G4LogicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4TwistedTubs.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4Material.hh"
#include "G4Para.hh"

class FridgeBuilder
{

public:
  
  //constructor and destructor
  FridgeBuilder();     
  ~FridgeBuilder(){;};

public: 
 //Return's logical volume
  G4LogicalVolume* GetFridge(void){return gasOne_logic;}; 
  void ConstructMaterial();
  G4double GetOffset(void);

private: 


     G4UnionSolid* bottle_shape; 
     G4UnionSolid* gas_bottle; 
     
     G4Cons* outerGas;
     G4UnionSolid* gas_one; 
     G4LogicalVolume* gasOne_logic;  
     
     G4Cons* copperCone; 
     G4UnionSolid* outer_shell; 
     G4LogicalVolume* outer_shellLV; 
     G4VPhysicalVolume* outer_shellPV; 

     G4Tubs* mash_Tube1;
     G4LogicalVolume* tube1_logic;
     G4VPhysicalVolume* tube1_physi;
    

     G4UnionSolid* mid_bottle;
     G4UnionSolid* gas_mid;

     G4Cons* middleConeGas;

     G4UnionSolid* gas_two; 
     G4LogicalVolume* gasTwo_logic; 
     
     G4Cons* middleCone;
     G4UnionSolid* middle_shell; 

     G4LogicalVolume* middle_shellLV; 
     G4VPhysicalVolume* middle_shellPV; 
     
     G4VPhysicalVolume* middle_gasPV;
     

     G4UnionSolid* in_bottle; 

 
//-------

//    G4Cons* outerCone; 
     
     G4Cons* innerCone;
     G4Cons* innerConeGas;
     
     G4UnionSolid* gas_in;

     G4LogicalVolume* gasThree_logic; 

     G4UnionSolid* four_bottle;
     G4UnionSolid* gasFour_bottle;

     G4Cons* fourthConeGas; 
     G4UnionSolid* gas_four;

     G4Cons* fourthCone; 
     G4UnionSolid* fourth_shell;
    
     G4Tubs* fourthTube;
     G4Tubs* fourthGasTube; 

     G4UnionSolid* fourth_object;
     G4UnionSolid* fourth_gas_object;
 
     G4LogicalVolume* gasFour_logic; 
     G4LogicalVolume* shellFour_logic;
     G4VPhysicalVolume* shellFour_physi;
     G4VPhysicalVolume* gasFour_physi; 
     

  //     G4LogicalVolume* outerGas_logic;

  //     G4VPhysicalVolume* gasTwo_physi; 

     G4UnionSolid* gas_three; 

  //    G4LogicalVolume* outerCone_logic; 

     G4UnionSolid* inner_shell; 



     G4LogicalVolume* inner_shellLV;
     G4VPhysicalVolume* inner_shellPV;
     G4VPhysicalVolume* inner_gasPV; 


  //     G4LogicalVolume*   mash_logic;    // pointer to mishmash LV
  //     G4VPhysicalVolume* mash_physi;    // pointer to mishmash physical

 
  //     G4VPhysicalVolume* gasThree_physi; 


     G4Tubs* mixing_tube; 
     G4LogicalVolume* sub_logic; 
       
  //    G4Tubs* gas_tube; 
  //    G4LogicalVolume* mixing_logic; 
     G4LogicalVolume* gas_logic;      
     G4VPhysicalVolume* mixing_physi;
     G4VPhysicalVolume* gas_physi;  
     
  //    G4Cons* cone; 
  //    G4Cons* gas_cone; 
  //    G4LogicalVolume* cone_logic; 
  //    G4LogicalVolume* gasCone_logic; 
  //    G4VPhysicalVolume* cone_physi; 
  //    G4VPhysicalVolume* gasCone_physi; 

  //    G4Tubs* outer_tube; 
  //    G4LogicalVolume* outer_logic; 
  //    G4VPhysicalVolume* outer_physi; 

    G4Tubs* window; 
    G4LogicalVolume* window_logic; 
    G4VPhysicalVolume* window_physi; 

    G4Tubs* mash_Tube3; 
    G4LogicalVolume* tube3_logic; 
    G4VPhysicalVolume* tube3_physi; 

    G4LogicalVolume* pipe_logic; 
    G4VPhysicalVolume* pipe_physi; 

     G4LogicalVolume* target_logic; 
     G4VPhysicalVolume* target_physi; 

  //     G4Material* targetMatter;  // pointer to the target  material
     G4Material* shellOneMatter; 
     G4Material* gasOneMatter; 
     G4Material* shellTwoMatter;
     G4Material* gasTwoMatter;
     G4Material* shellThreeMatter;
     G4Material* gasThreeMatter; 
     G4Material* shellFourMatter;
     G4Material* gasFourMatter;
     G4Material* copperConeMatter; 
     G4Material* mixChMatter; 
     G4Material* mixGasMatter; 
     G4Material* mixTubeMatter; 
     G4Material* kaptonWindowMatter; 
     G4Material* pipeMatter; 
     G4Material* gasPipeMatter; 
     G4Material* Mix75He25Cu;
     G4Material* Mix50He50Cu; 
     
  G4RotationMatrix* rotate;// = new G4RotationMatrix;

//  All the constants needed
//  Define in the constructor
 //extern G4double innerRadius;
G4double targHoldR; 
G4double targHoldH; 
G4double targHoldTh;
G4double startingAngle;
G4double spanningAngle;

G4double pipeRadius; 
G4double pipeThickness; 
G4double heightA; 
G4double heightB; 
G4double heightC; 
G4double heightD; 
//G4double heightE; 
G4double alpha_ang; 
G4double beta_ang; 

G4double shellOne_narrowRad;
G4double shellOne_wideRad;
G4double shellOne_delta;
G4double shellOne_thick;
G4double shellOne_narrowHeight;
G4double shellOne_wideHeight;

G4double shellTwo_narrowRad;
G4double shellTwo_wideRad;
G4double shellTwo_delta;
G4double shellTwo_thick;
G4double shellTwo_narrowHeight;
G4double shellTwo_wideHeight;

G4double shellThree_narrowRad;
G4double shellThree_wideRad;
G4double shellThree_delta;
G4double shellThree_thick;
G4double shellThree_narrowHeight;
G4double shellThree_wideHeight;


G4double shellFour_narrowRad;
G4double shellFour_wideRad;
G4double shellFour_delta;
G4double shellFour_thick;
G4double shellFour_narrowHeight;
G4double shellFour_wideHeight;

G4double mixing_narrowRad;
G4double mixing_wideRad;
G4double mixing_delta;
G4double mixing_thick; 
G4double mixing_narrowHeight; 
G4double mixing_wideHeight; 

G4double outerCone_radius;  
G4double outerCone_delta; 

G4double copperCone_radius;
G4double copperCone_delta;

G4double middleCone_radius;
G4double middleCone_delta;

G4double innerCone_radius;
G4double innerCone_delta;

G4double fourthCone_radius;
G4double fourthCone_delta; 


G4double tube1_inner;
G4double tube1_outer;
G4double tube1_height;

G4double tube3_inner;
G4double tube3_outer;
G4double tube3_height;

G4double tub_height; 
G4double outer_tube_rad;
G4double outer_tube_thick;
G4double mixing_tube_rad; 
G4double mixing_tube_thick;
G4double mixing_tube_height;
//

G4double gas_two_offset;
G4double gas_three_offset;
G4double gas_four_offset;
G4double mixing_off; 
G4double mixing_tube_off;
G4double window_offset;
G4double tube1_offset;
G4double tube3_offset; 
};

#endif//myFridgeBuilder_H
