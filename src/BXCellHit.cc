//See BXCellHit.hh for more detials

#include "BXCellHit.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

//Matches extern statement in BXCellHit.hh
G4Allocator<BXCellHit> BXCellHitAllocator;

//constructor
BXCellHit::BXCellHit()
{
	//Initially sets everything to zero
	edep = 0.0;
	lightOut = 0.0;
	time = 0.0;
	deltaTime = 0.0;
	trackID = -1;
	ringNo = -1;
	armNo = -1;
	particle = "";
	localPrePos  = G4ThreeVector(0.0,0.0,0.0);
	localPostPos = G4ThreeVector(0.0,0.0,0.0);
}

//print the information about the hit
void BXCellHit::Print(std::ostream & os)
{
	//Displays ringNo/armNo in human convinient numering
	os << "Cell (" << ringNo +1 <<"," <<armNo +1 <<"); ";
	os << particle << " (" << trackID << "); ";
	os << "Deposited " << G4BestUnit(edep,"Energy") << "; ";
	os << "Time " << G4BestUnit(time,"Time") << "; ";
	os << "Length " << G4BestUnit(deltaTime,"Time") << ";\n";
}

//overloading the operator in order to print hits
std::ostream &operator<<(std::ostream &os,BXCellHit &hit)
{
	hit.Print(os);
	return os;
}

//EOF
