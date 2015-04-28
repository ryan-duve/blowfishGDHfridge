/************************************************************
 * blowfishGDH.cc 
 *
 * Original author:
 * Ward Wurtz (waw113@mail.usask.ca)
 * Subatomic Physics Graduate Student
 * Supervisor: Rob Pywell
 *
 * Modified by Rob Pywell for the GDH experiment
 *
 * University of Saskatchewan
 * Saskatoon, SK CANADA
 *
 * Description:
 *
 * This program provides the base for building a simulation of the
 * Blowfish neutron detector array.  It defines the geometry and other
 * characteristics of Blowfish and the Blowfish detectors.  It is ment
 * as a template where you can add geometries for experiment-dependent
 * uses.  The 'X' means 'fill in the blank'.
 *
 * Credits:
 * 
 * Much of this code is from my supervisor, Dr. Pywell and the
 * examples produced by the Geant4 Collaboration and distributed
 * with GEANT4.  Lisence details for the GEANT4 collaboration code
 * can be found at http://geant4.web.cern.ch/geant4/license/
 * Since these details are vague, I assume that all code is released
 * under an LGPL or BSD-like license.
 * 
 ********************************************************************
 * DISCLAIMER                                                       *
 *                                                                  *
 * The following disclaimer summarizes all the specific disclaimers *
 * of contributors to this software. The specific disclaimers,which *
 * govern, are listed with their locations in:                      *
 *   http://cern.ch/geant4/license                                  *
 *                                                                  *
 * Neither the authors of this software system, nor their employing *
 * institutes,nor the agencies providing financial support for this *
 * work  make  any representation or  warranty, express or implied, *
 * regarding  this  software system or assume any liability for its *
 * use.                                                             *
 *                                                                  *
 * By copying,  distributing  or modifying the Program (or any work *
 * based  on  the Program)  you indicate  your  acceptance of  this *
 * statement, and all its terms.                                    *
 ********************************************************************/

//Geant4 includes
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "globals.hh"

//Pre-built physics lists
//#include "LHEP_PRECO_HP.hh" no longer exists in geant4 distributions
//#include "LHEP.hh"
#include "QGSP_BERT_HP.hh"

//Lucid Plugin
#include "G4Lucid.hh"
#include "G4LucidEvent.hh"
#include "G4LucidChar.hh"

//My includes
#include "BXLucid.hh"
#include "BXDetectorConstruction.hh"
#include "BXEventAction.hh"
#include "BXPrimaryGeneratorAction.hh"
//#include "BXPGATh232.hh"
//#include "BXPGATh228.hh"
//#include "BXPGANa22.hh"
//#include "BXPGACs137.hh"
//#include "BXPGACf252.hh"
//#include "BXPGAAmBe.hh"
//#include "BXPGAGeantino.hh"
//#include "BXPhysicsList.hh"
#include "BXRandomSeedMessenger.hh"
#include "BXRunAction.hh"

//For seed setting
#include <time.h>

//to use visualization
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc, char **argv)
{
	//Construct the default run manager
	G4RunManager* runManager = new G4RunManager;

	//Initialize G4Lucid
	BXLucid * blowfishLucid = new BXLucid();
	blowfishLucid->Initialise();
	G4LucidEvent * idealStartup = G4Lucid::GetLucidPointer()->GetLucidEvent("ideal_startup");

	//Initialises the random number generator 
	//The seed can also be set using the messenger initialized below.
	//HepRandom::setTheSeed(123456789);
	//int seed = time(NULL);
	//HepRandom::setTheSeed(seed);
	BXRandomSeedMessenger * rsm = new BXRandomSeedMessenger();
	
	//do we want to use custom physics list or LHEP_PRECO_HP physics list?
	#if 0 //Custom physics list
		runManager->SetUserInitialization(new BXPhysicsList);
		idealStartup->GetLucidChar("physics_list")->Set( "BXPhysicsList" );
	#endif
	#if 0 //Physics list for fast loading when debugging
		runManager->SetUserInitialization(new LHEP);
		idealStartup->GetLucidChar("physics_list")->Set( "LHEP" );
	#endif
	#if 1 //QGSP_BERT_HP physics list
		runManager->SetUserInitialization(new QGSP_BERT_HP);
		idealStartup->GetLucidChar("physics_list")->Set( "QGSP_BERT_HP" );
	#endif


  	//Visualization if available
	#ifdef G4VIS_USE
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialise();
	idealStartup->GetLucidChar("visualisation")->Set("on");
	#else
	idealStartup->GetLucidChar("visualisation")->Set("off");
	#endif

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();


	G4bool GDH_orientation = true;
  	//Set mandatory initialization and user action classes
  	runManager->SetUserInitialization(new BXDetectorConstruction(GDH_orientation));
  	runManager->SetUserAction(new BXPrimaryGeneratorAction(GDH_orientation));
  	runManager->SetUserAction(new BXRunAction);
	runManager->SetUserAction(new BXEventAction);

  	//Initialize G4 kernel
  	runManager->Initialize();
	
	//are there command line arguments?
	if(argc > 1)
	{
		// minimal information
		UImanager->ApplyCommand("/tracking/verbose 0"); 
		UImanager->ApplyCommand("/particle/verbose 0"); 
		UImanager->ApplyCommand("/process/verbose 0"); 
		UImanager->ApplyCommand("/hits/verbose 0"); 
		UImanager->ApplyCommand("/event/verbose 0"); 
		UImanager->ApplyCommand("/control/verbose 0"); 
		//execute macro here: first command line argument
		G4cout << "\nRunning macro file " << argv[1] << "...\n\n";
      		UImanager->ExecuteMacroFile(argv[1]);
	}
	else //no command line arguments
	{
  		// run initialisation macro
		//G4String initMacro = "mac/init.mac";
		//G4cout << "\nRunning macro file " << initMacro << "...\n";
 		//G4UImanager::GetUIpointer()->ExecuteMacroFile(initMacro);
		//G4cout << "Done running " << initMacro << G4endl << G4endl;
		// interactive mode : define UI session
#ifdef G4UI_USE
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
		UImanager->ApplyCommand("/control/execute vis.mac"); 
#endif
		if (ui->IsGUI()) UImanager->ApplyCommand("/control/execute gui.mac");
		ui->SessionStart();
		delete ui;
#endif

		/*
		//Open a tcsh session: will stay there until the user types "exit"
  		G4UIsession* session = new G4UIterminal(new G4UItcsh);
		session->SessionStart();
		delete session;
		*/
	}

	//terminate visulaization
	#ifdef G4VIS_USE
	delete visManager;
	#endif

	//ends Lucid
	delete blowfishLucid;

	//deletes messengers
	delete rsm;

	//job termination
  	delete runManager;
  	return 0;

}// end of main()

//end of blowfishX.cc

