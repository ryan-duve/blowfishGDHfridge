#ifndef myShellBuilder_H
#define myShellBuilder_H 1

//Geant4 includes
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4TwistedTubs.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4Material.hh"
#include "G4Para.hh"

class ShellBuilder
{

public:
  
  //constructor and destructor
  //ShellBuilder();     
  ~ShellBuilder(){;};

  //constructor
  ShellBuilder(G4double narrowR,
		G4double wideR, 
		G4double pD, 
		G4double thick, 
		G4double narrowH, 
		G4double wideH, 
		G4double off, 
		G4Material *sMat,
		G4Material *gMat);


  //setters
  void set_narrowRadius(G4double new_narrowRadius);
  void set_wideRadius(G4double new_wideRadius);
  void set_thickness(G4double new_thickness);
  void set_narrowHeight(G4double new_narrowHeight);
  void set_wideHeight(G4double new_wideHeight);
  void set_shellMat(G4Material* new_shellMat);
  void set_gasMat(G4Material* new_gasMat);

 //Builds the shell's logical volume
  G4LogicalVolume* GetLVPointer(void){return shell_log;};
  G4LogicalVolume* GetGasLVPointer(void){return gas_log;};
  G4UnionSolid* GetShellObject(void){return shell;}; 
  G4UnionSolid* GetGasObject(void){return gas_shell;};
  //creates materials for shells
  void DefineMaterials();

private:
  
  //logical volumes 
  G4LogicalVolume* shell_log;
  G4PVPlacement* shell_physi;  
  G4LogicalVolume* gas_log; 
 
  //geometry components
  G4Tubs* narrow_tube;
  G4Tubs* blankoff;
  G4UnionSolid* narrow_tube_blank;
  G4Tubs* gas_narrow;
  G4Tubs* wide_tube;  
  G4Tubs* gas_wide; 

  G4Cons* cone;
  G4Cons* gas_cone;  
  G4UnionSolid* funnel;
  G4UnionSolid* gas_funnel; 
 
  G4UnionSolid* shell; 
  G4UnionSolid* gas_shell; 

  //geometry constants
  G4double narrowRadius;
  G4double wideRadius;
  G4double pDz;   
  G4double thickness; 
  G4double narrowHeight; 
  G4double wideHeight; 
  G4double offset; 

  G4RotationMatrix* rotation; 

  //materials
  G4Material* shellMat; 
  G4Material* gasMat;   

  //offset variables
  G4double micro_offset; //creates a micrometer of width& height that the mother gas volume extends

  G4double startingAngle, spanningAngle;

};

#endif//myShellBuilder_H
