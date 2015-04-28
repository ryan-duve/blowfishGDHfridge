#include <iostream>
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"

class FridgeMaterials 
{

 public:

  static FridgeMaterials *getInstance();
  
 private:
  
  //constructor destructor
  FridgeMaterials(){;};
  ~FridgeMaterials(){;};

  static FridgeMaterials *instance;

 public:
  // Constructing
  void ConstructAllMaterials();
  // Getting materials
  G4Material* getAl() {return Aluminum;} //returns Aluminum
  G4Material* getVac() {return Vaccum;}  //returns Vaccume
  G4Material* getdBut() {return dButanol;} //returns Deuterated Butanol
  G4Material* getPlas() {return Plastic;}
  G4Material* getLHe3() {return LHe3;}
  G4Material* getLHe4() {return LHe4;}
  G4Material* getGasHe4() {return gasHe4;} 
  G4Material* getKap() {return Kapton;} 
  G4Material* getSS() {return StainlessSteel;}
  G4Material* getCu() {return Cu;}
  G4Material* getMix75He25Cu() {return Mix75He25Cu; }
  G4Material* getMix50He50Cu() {return Mix50He50Cu; }
  G4Material* getHeMix() {return HeMix;}
  
 private:
  //constants for creating materials
  G4double z, a;
  G4double density,temperature;//,nel;
  G4int iz, n, natoms, ncomp;
  G4double abundance;
  
  //Materials that different methods require
  G4Material* Aluminum;
  G4Material* Vaccum;
  G4Material* Butanol; 
  G4Material* dButanol; 
  G4Material* StainlessSteel; 
  G4Material* LHe3;
  G4Material* LHe4;
  G4Material* gasHe4;
  G4Material* HeMix;
  G4Material* Cu; 
  G4Material* Kapton; 
  G4Material* Plastic; 
  G4Material* Mix75He25Cu;
  G4Material* Mix50He50Cu;
  
  //Elements that different methods require
  G4Element* O;
  G4Element* C;
  G4Element* H;
  G4Isotope* D;
  G4Element* elD;
  G4Element* Si;
  G4Element* Cr;
  G4Element* Mn;
  G4Element* Fe;
  G4Element* Ni;
  G4Element* elHe3;
  G4Element* elHe4; 
  G4Element* elCu;
  
};
