#ifndef TargetBuilder_H
#define TargetBuilder_H 1

//Geant4 includes
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"


class TargetBuilder
{

public:
  
  //constructor and destructor
  TargetBuilder( G4double targHoldR, G4double targHoldH, G4double targHoldTh);
  ~TargetBuilder(){;};

 //Builds the cell's logical volume

  G4LogicalVolume* GetLVPointer(void){return targHold_log;};

private:
 
  G4LogicalVolume* targHold_log;  //logical volume
  G4LogicalVolume* target_log; //inner target logcial volume
  G4Tubs* targHold_tube; //solid volume
  G4Tubs* target_tube; //inner target physical volume
};

#endif//TargetBuilder_H




