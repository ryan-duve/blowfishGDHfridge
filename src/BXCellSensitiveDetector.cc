//See BXCellSensitiveDetector.hh for more details

#include "BXCellSensitiveDetector.hh"
#include "BXCellHit.hh"

//Geant4 includes
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4TouchableHandle.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

//Constructor
BXCellSensitiveDetector::BXCellSensitiveDetector(G4String name,G4String material)
	:G4VSensitiveDetector(name)
{
	//the name of the material
  	cellMaterial = material;

	//A class to compute the light output
	lightOutput = new LightOutput(material);
	
	//we muast add this string in order for
	//proper operation
	collectionName.insert("HitCollection");

	fPrintGuess = false; // false to suppress
	// printout for particles not in the lightoutput tables.

	// Parentage to find cell number
	fParentage = 3;
}

//Destructor
BXCellSensitiveDetector::~BXCellSensitiveDetector()
{
	delete lightOutput;
}

//Initialises the sensitive detector
void BXCellSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
	//make a new hit collection
	hitsCollection = new BXCellHitsCollection(SensitiveDetectorName,collectionName[0]); 

	// So we can access the hits collector from other classes
	G4String collName;
  	G4int HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
	HCE->AddHitsCollection(HCID,hitsCollection);

}

//Create a new hit class when Geant4 records a hit on a sensitive detector
G4bool BXCellSensitiveDetector::ProcessHits(G4Step*aStep, G4TouchableHistory*)
{
	//Sets up a new hit and add it to the hit collection
	BXCellHit * newHit = new BXCellHit();
  	hitsCollection -> insert( newHit );

	//objects that contain needed information
	const G4Track * aTrack = aStep->GetTrack();
	const G4VTouchable * aTouchable = aTrack->GetTouchable();
	const G4StepPoint * aPreStepPoint = aStep->GetPreStepPoint();

	//gets the information of the hit 
	G4double time  = aPreStepPoint->GetGlobalTime();        //Time since beginning of event
	G4double preEng= aPreStepPoint->GetKineticEnergy();     //Energy at the start of this step
	G4double dtime = aStep->GetDeltaTime(); 		//Time for step
	G4double edep  = aStep->GetTotalEnergyDeposit(); 	//Energy deposited
	G4int trackID  = aTrack->GetTrackID(); 			//ID of this track
	//const G4int ringReplicaNumber = 3; //How deep to search the geometry for the ring replicas
	//const G4int armReplicaNumber = 5;  //How deep to search the geometry for the arm replicas
	G4int cellNumber = aTouchable->GetReplicaNumber(fParentage);//Cell number (0 - 87)
	//G4int ringNumber = aTouchable->GetReplicaNumber(ringReplicaNumber);//Ring number
	//G4int armNumber  = aTouchable->GetReplicaNumber(armReplicaNumber);//Arm number
	G4int ringNumber = cellNumber/8;
	G4int armNumber = cellNumber%8;

	//Find the local hit poition for both pre and post step
	//We can use the same transformation for both as the PreStepPoint will always be our sensitive detector
 	const G4AffineTransform transformation = aPreStepPoint->GetTouchable()->GetHistory()->GetTopTransform();
 	G4ThreeVector globalPrePosition = aPreStepPoint->GetPosition();
 	G4ThreeVector localPrePosition = transformation.TransformPoint(globalPrePosition);
 	G4ThreeVector globalPostPosition = aStep->GetPostStepPoint()->GetPosition();
 	G4ThreeVector localPostPosition = transformation.TransformPoint(globalPostPosition);

	//particle's name
	G4ParticleDefinition * aParticle = aTrack->GetDefinition();
	G4String part = aParticle->GetParticleName();
	
	//Sorts out the particle type and gets the light output electron equivalent energy
	//Since geant4 does not recognise eVee as a unit, we use eV in its place.
	//However, they are not the same as one is a measure of energy and the other is a
	//measure of detector responce.
	G4double elight = 0.0;
	if (part == "geantino" || part == "neutron") { 
		elight = 0.0; }
	else if( part == "e-" || part == "e+" || part == "gamma") {
		elight = edep; }
	else if( part == "proton" || part == "deuteron" || part == "alpha" || part == "triton" || part == "He3") {
		elight = lightOutput->GetLight(preEng, edep, part); }
	else if( part == "mu+" || part == "mu-") {
		elight = lightOutput->GetLight(preEng, edep, "muon"); }
	else if( part == "pi+" || part == "pi-") {
		elight = lightOutput->GetLight(preEng, edep, "pion"); }
	else if( part.find("C12", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "C12"); }
	else if( part.find("C13", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "C13"); }
	else if( part.find("Be8", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "Be8"); }
	else if( part.find("Be9", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "Be9"); }
	else if( part.find("Be10", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "Be10"); }
	else if( part.find("O16", 0) != G4String::npos) {
		elight = lightOutput->GetLight(preEng, edep, "O16"); }
	else
      		{
		// make a guess for particles not in the lightoutput tables
		G4double charge = aParticle->GetPDGCharge();
		if(fPrintGuess)
			{
			G4cout << "Particle = " << part << " Charge: "<< charge;
			G4cout <<"  Mass = "<< aParticle->GetPDGMass()/MeV <<" MeV";
			G4cout << " Edep = "<< edep/MeV <<" MeV" <<G4endl;
			}
	  	if( charge >= 3 && charge < 5 ) {
			elight = lightOutput->GetLight(preEng, edep, "Be8"); }
	  	else if( charge >= 5 && charge < 7 ) {
			elight = lightOutput->GetLight(preEng, edep, "C12"); }
  		else if( charge >= 7 ) {
			elight = lightOutput->GetLight(preEng, edep, "O16"); }
  		else {
			elight = edep; }
      		}

	//sets all variables in the hit
  	newHit->SetEnergyDeposited( edep );
	newHit->SetLightOutput( elight );
	newHit->SetParticle(part);
	newHit->SetInitTime(time);
	newHit->SetTrackID(trackID);
	newHit->SetDeltaTime(dtime);
	newHit->SetRingNumber(ringNumber);
	newHit->SetArmNumber(armNumber);
	newHit->SetCellNumber(cellNumber);
	newHit->SetPreLocalPosition(localPrePosition);
	newHit->SetPostLocalPosition(localPostPosition);
	
	return true;

}//End of ProcessHits()

//EOF BXCellSensitiveDetector.cc
