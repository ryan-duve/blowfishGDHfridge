//See BXLucid.hh for more details
#include "BXLucid.hh"

//Lucid includes
#include "G4LucidInclude.hh"

//Geant4 includes
#include <G4RunManagerKernel.hh>

//public function to initialize everything
G4int BXLucid::Initialise(void)
{
	G4int status = 0;
	
	//Initializes the Lucid setup
	lucidPtr = G4Lucid::GetLucidPointer();
	lucidPtr->SetExpName("BlowfishX Experiment Name");
	lucidPtr->SetExpDescription("GEANT 4 Simulation");
	lucidPtr->SetFilenamePrefix("deut.");

	status += InitialiseActual();
	status += InitialiseIdeal();

	return(status);
}

//private function to initialize actual variables
G4int BXLucid::InitialiseActual(void)
{
	//Options
	//const G4double adc_res = 0.3667*keV; //Resolution of the ADC
	const G4double adc_res = 2.0*MeV/2000.; //Resolution of the ADC
	const G4double tdc_res = 0.1*ns;  //Resolution of the TDC
	const G4int long_ped = 100; //Pedestal bin for the long ADC
	const G4int short_ped = 50; //Pedestal bin for the short ADC 
	const G4int ig_ped = 50; //Pedestal bin for the independent gate ADC

	//startup event
	//This event is written when a Lucid event starts.
	G4LucidEvent * startup_evt = new G4LucidEvent("startup");
	lucidPtr->AddLucidEvent( startup_evt );
	startup_evt -> AddLucidVariable(new G4LucidLong("control",64));
	startup_evt -> AddLucidVariable(new G4LucidLong("Ped_prescale"));
	startup_evt -> AddLucidVariable(new G4LucidLong("Gamma_prescale"));
	startup_evt -> AddLucidVariable(new G4LucidLong("Flux_mult"));
	startup_evt -> AddLucidVariable(new G4LucidLong("Paddle_mult"));
	startup_evt -> AddLucidVariable(new G4LucidLong("beam_params",1024));
	startup_evt -> AddLucidVariable(new G4LucidShort("Accel_on"));
	startup_evt -> AddLucidVariable(new G4LucidShort("HVread_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Xarm_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Ped_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("AltPed_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Gamma_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Flash_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Mon_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Mon_mult"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Flux_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("Paddle_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("GP_en"));
	startup_evt -> AddLucidVariable(new G4LucidShort("outword"));
	startup_evt -> AddLucidVariable(new G4LucidShort("tdc_full_scale_range",2));
	startup_evt -> AddLucidVariable(new G4LucidShort("threshold"));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_l_1",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_s_1",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_l_2",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_s_2",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_l_3",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_s_3",32));
	startup_evt -> AddLucidVariable(new G4LucidShort("pedestals_ig"));
	startup_evt -> AddLucidVariable(new G4LucidShort("hv_demand",96));
	startup_evt -> AddLucidVariable(new G4LucidShort("hv_measured",96));

	//Set the pedestals in the startup event to the actual pedestals
	for(G4int jj = 0; jj < 32; jj++)
	{
		startup_evt->GetLucidShort("pedestals_l_1")->Set(long_ped,jj);
		startup_evt->GetLucidShort("pedestals_l_2")->Set(long_ped,jj);
		startup_evt->GetLucidShort("pedestals_l_3")->Set(long_ped,jj);
		startup_evt->GetLucidShort("pedestals_s_1")->Set(short_ped,jj);
		startup_evt->GetLucidShort("pedestals_s_2")->Set(short_ped,jj);
		startup_evt->GetLucidShort("pedestals_s_3")->Set(short_ped,jj);
		startup_evt->GetLucidShort("pedestals_ig") ->Set(ig_ped,jj);
	}

	//scalerread symbol table
	//A scaler read event occurs periodically and a series of scalers
	//are read out with a series of counters.  In the real blowfish, the
	//scalers are hardware devices and the counters are software.
	G4LucidEvent * scalerread_evt = new G4LucidEvent("scalerread");
	lucidPtr->AddLucidEvent( scalerread_evt );
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_lamtrig"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_neutron"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_gamma_enable"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_pedestal"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_flasher"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_monitor"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_monitor_enable"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_flux"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_flux_enable"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_paddle"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_paddle_enable"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("count_scalerread"));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("cell_scaler1",32));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("cell_scaler2",32));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("cell_scaler3",32));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("scaler1",32));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("scaler2",32));
	scalerread_evt -> AddLucidVariable(new G4LucidLong("scaler3",32));

	//Disable the conditional clear for these counters so that they will persist
	//through an entire run. 
	scalerread_evt -> GetLucidLong("count_lamtrig")       -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_neutron")       -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_gamma_enable")  -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_pedestal")      -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_flasher")       -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_monitor")       -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_monitor_enable")-> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_flux")          -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_flux_enable")   -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_paddle")        -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_paddle_enable") -> DisableConditionalClear();
	scalerread_evt -> GetLucidLong("count_scalerread")    -> DisableConditionalClear();


	//lamtrig event
	//Needed by Blowfish's hardware, but not useful for the simulation
	G4LucidEvent * lamtrig_evt = new G4LucidEvent("lamtrig");
	lucidPtr->AddLucidEvent( lamtrig_evt );
	lamtrig_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_lamtrig"));
	lamtrig_evt -> AddLucidVariable(new G4LucidShort("lam_ioreg"));

	//neutron event
	//This is the main event.  All ADCs and TDCs are read.
	G4LucidEvent * neutron_evt = new G4LucidEvent("neutron");
	lucidPtr->AddLucidEvent( neutron_evt );
	neutron_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_neutron"));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_l_1",adc_res,long_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_s_1",adc_res,short_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_l_2",adc_res,long_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_s_2",adc_res,short_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_l_3",adc_res,long_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_s_3",adc_res,short_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV792("vmeadc_ig" ,adc_res,ig_ped));
	neutron_evt -> AddLucidVariable(new G4LucidV775("vmetdc_1"  ,tdc_res));
	neutron_evt -> AddLucidVariable(new G4LucidV775("vmetdc_2"  ,tdc_res));
	neutron_evt -> AddLucidVariable(new G4LucidV775("vmetdc_3"  ,tdc_res));
	neutron_evt -> AddLucidVariable(new G4LucidLong("count_gamma_enable"));
	neutron_evt -> AddLucidVariable(new G4LucidShort("Gamma_currently_enabled"));

	//pedestal event
	//Used to determine the pedestals for the ADCs.
	//The pedestals represent the zero of the ADCs.
	G4LucidEvent * pedestal_evt = new G4LucidEvent("pedestal");
	lucidPtr->AddLucidEvent( pedestal_evt );
	pedestal_evt -> AddLucidVariable(scalerread_evt ->GetLucidLong("count_pedestal"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_1"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_1"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_2"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_2"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_3"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_3"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_1"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_2"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_3"));
	pedestal_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_ig"));
	pedestal_evt -> AddLucidVariable(new G4LucidShort("flux_adc"));

	//flasher event
	//Occurs when the gain monitoring system flasher flashes
	G4LucidEvent * flasher_evt = new G4LucidEvent("flasher");
	lucidPtr->AddLucidEvent( flasher_evt );
	flasher_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_flasher"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_1"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_1"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_2"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_2"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_l_3"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_s_3"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_1"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_2"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV775("vmetdc_3"));
	flasher_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_ig"));

	//monitor event
	//Occurs when the gain monitoring system's monitor receives a hit
	G4LucidEvent * monitor_evt = new G4LucidEvent("monitor");
	lucidPtr->AddLucidEvent( monitor_evt );
	monitor_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_monitor"));
	monitor_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_ig"));
	monitor_evt -> AddLucidVariable(new G4LucidShort("coinreg"));

	//flux event
	//Used by the beam flux monitor
	G4LucidEvent * flux_evt = new G4LucidEvent("flux");
	lucidPtr->AddLucidEvent( flux_evt );
	flux_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_flux"));
	flux_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_ig"));
	flux_evt -> AddLucidVariable(new G4LucidADC("flux_adc",4096,adc_res,""));
	flux_evt -> AddLucidVariable(new G4LucidTDC("flux_tdc",2048,tdc_res,8));

	//paddle event
	//Used by the beam paddle
	G4LucidEvent * paddle_evt = new G4LucidEvent("paddle");
	lucidPtr->AddLucidEvent( paddle_evt );
	paddle_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_paddle"));
	paddle_evt -> AddLucidVariable(neutron_evt->GetLucidV792("vmeadc_ig"));
	paddle_evt -> AddLucidVariable(flux_evt->GetLucidTDC("flux_tdc"));

	
	//goodbye symbol table
	//Run at the end of a Lucid run
	G4LucidEvent * goodbye_evt = new G4LucidEvent("goodbye");
	lucidPtr->AddLucidEvent( goodbye_evt );
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_lamtrig"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_neutron"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_gamma_enable"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_pedestal"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_flasher"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_monitor"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_monitor_enable"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_flux"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_flux_enable"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_paddle"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_paddle_enable"));
	goodbye_evt -> AddLucidVariable(scalerread_evt->GetLucidLong("count_scalerread"));
	goodbye_evt -> AddLucidVariable(startup_evt->GetLucidShort("hv_demand"));
	goodbye_evt -> AddLucidVariable(startup_evt->GetLucidShort("hv_measured"));
	goodbye_evt -> AddLucidVariable(new G4LucidShort("last_lam_ioreg_error_val"));
	goodbye_evt -> AddLucidVariable(new G4LucidShort("HVread_en"));
	goodbye_evt -> AddLucidVariable(new G4LucidLong("lam_ioreg_errors"));


	return(0);

}//End of InitializeActual()

//private function to initialize ideal variables
G4int BXLucid::InitialiseIdeal(void)
{
	//This event is written at the start of a new run
	G4LucidEvent * ideal_startup = new G4LucidEvent("ideal_startup");
	lucidPtr->AddLucidEvent( ideal_startup );
	ideal_startup->AddLucidVariable( new G4LucidChar("physics_list",32) );
	ideal_startup->AddLucidVariable( new G4LucidChar("visualisation",8) );
	ideal_startup->AddLucidVariable( new G4LucidLong("g4_run_no") ); //Geant4 run number
	ideal_startup->AddLucidVariable( new G4LucidLong("lucid_run_no") ); //Geant4 run number
	ideal_startup->AddLucidVariable( new G4LucidLong("rand_seed") ); //Random Seed

	//G4 versoin string
	G4LucidChar * g4VersionChar = new G4LucidChar("g4_version",128);
	ideal_startup->AddLucidVariable( g4VersionChar );
	g4VersionChar->Set( G4RunManagerKernel::GetRunManagerKernel()->GetVersionString() );


	//This event is written when a neutron hit occurs
	lucidPtr->AddLucidEvent( new G4LucidEvent("ideal_neutron" ) );

	//This event is written at the end of a run
	G4LucidEvent * ideal_windup = new G4LucidEvent("ideal_windup" );
	lucidPtr->AddLucidEvent( ideal_windup );
	ideal_windup->AddLucidVariable( new G4LucidFloat("time_real_s") );
	ideal_windup->AddLucidVariable( new G4LucidFloat("time_system_s") );
	ideal_windup->AddLucidVariable( new G4LucidFloat("time_user_s") );
	ideal_windup->AddLucidVariable( new G4LucidLong("geantinos_emitted") );
	ideal_windup->AddLucidVariable( new G4LucidLong("neutrons_emitted") );
	ideal_windup->AddLucidVariable( new G4LucidLong("gammas_emitted") );
	ideal_windup->AddLucidVariable( new G4LucidLong("geantino_hits",88));

	return(0);

}//End of InitializeIdeal()

//EOF BXLucid.cc
