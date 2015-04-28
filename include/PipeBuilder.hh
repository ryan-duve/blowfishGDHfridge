#ifndef myPipeBuilder_H
#define myPipeBuilder_H 1

//Geant4 includes
#include "G4LogicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4UnionSolid.hh"
#include "G4Material.hh"


class PipeBuilder
{

public:
  
  //constructor and destructor
  PipeBuilder();     
  ~PipeBuilder(){;};

  PipeBuilder(G4double radius_in,G4double thick, G4double a, G4double b, G4double c, G4double d, G4double alp, G4double bet );

 //Returns pipe logical volume
  G4LogicalVolume* GetLVPointer(void){return pipe_log;};

  //creates materials for shells
  void DefineMaterials();

private:
  
  //logical volumes 
  G4LogicalVolume* pipe_log; 

  //geometry components
  G4Tubs* tubeA;
  G4CutTubs* tubeB; 
  G4Tubs* tubeC; 
  G4CutTubs* tubeD; 
 
  G4UnionSolid* sectionAB; 
  G4UnionSolid* sectionABC; 
  G4UnionSolid* sectionABCD; 

  //geometry constants
  G4double radius; 
  G4double thickness; 
  G4double heightA; 
  G4double heightB; 
  G4double heightC; 
  G4double heightD; 

  G4double alpha; 
  G4double beta; 

  G4RotationMatrix* rotation;
  G4RotationMatrix* rotation_B;

  //materials
  G4Material* pipeMat; 

};

#endif//myPipeBuilder_H
