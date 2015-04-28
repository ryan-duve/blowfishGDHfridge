#################################################
#     Looker for setting High Voltages and
#     determining gains
#################################################

define vmeadc_l_1_raw[32] integer*2
define vmeadc_s_1_raw[32] integer*2
define vmeadc_l_2_raw[32] integer*2
define vmeadc_s_2_raw[32] integer*2
define vmeadc_l_3_raw[32] integer*2
define vmeadc_s_3_raw[32] integer*2
define vmetdc_1_raw[32] integer*2
define vmetdc_2_raw[32] integer*2
define vmetdc_3_raw[32] integer*2
define vmeadc_ig_raw[32] integer*2

### Caen module data decomposition variables
define buffers integer*2
define notvalid integer*2
define icell integer*2
define adcbuffer_mult_l[4]   int*4
define adcbuffer_mult_s[4]   int*4
define adcbuffer_mult_ig     int*4
define tdcbuffer_mult[4]     int*4
define adcnotvalid_l[4]      int*4
define adcnotvalid_s[4]     int*4
define adcnotvalid_ig         int*4
define tdcnotvalid[4]        int*4

# Pedestal check temporary variables
define peddiff, pedshift integer*4

define tdc_align[89]                                    int*2
define cell_mult[89]					int*2
define flash_cell_mult[89]				int*2
define cell_adc_mult[89]				int*2
define flash_cell_adc_mult[89]				int*2
define adc_short[89]					int*2
define adc_long[89]					int*2
define adc_long_E[89]					real*4
define adc_ig[32]					int*2
define cell_tdc[89]					int*2
define Ncell_tdc[89]					int*2
define Fcell_tdc[89]					int*2
define Ncell_mult[89]					int*2
define Fcell_mult[89]					int*2
define flash_adc_short[89]				int*2
define flash_adc_long[89]				int*2
define flash_cell_tdc[89]				int*2
define flash_adc_ig[32]					int*2
define i,j						int*2
define iarm, iring int*4
define F_neut_rate[88]					real*4

define runno, runs[100], num_runs                       int*4
define done_Find_Gains					int*4
define timestart, timestop				int*4
define datestart, datestop				char*80
define monitor_bits                                     int*2

define zFilename					char*150
define zI1tmp, zI2tmp, zI3tmp				int*4
define zR1tmp, zR2tmp, zR3tmp				real*8
define zR4tmp, zR5tmp, zR6tmp				real*8
define zA4096tmp[4096], zA1024tmp[1024]			int*4
define cell_gain[89], cell_gain_err[89]			real*4
define cell_edge[89], cell_edge_err[89]			real*4
define edge_max, edge_min				real*4

define peak0, peak1 , smooth, hiband_ave, loband_ave	int*4
define arrsize, arr_offset, maxDiff			int*4
define psd_off_copy					int*4
define rot_var_copy					real*4
define F_neut_count[89], rand_count[89]			int*4


define l_hv_measured[89], l_hv_demand[89], l_hv_new[89] int*2

define Lucidloadvars(char*40)				int*4
define pow(real*8, real*8)				real*8

define chararray[20]					char*80
##########################################################
## Parameters that are read from files
##########################################################
#******** From blowfish.dat
# Misc control stuff
  define exp_dir			char*100
  define program_name			char*150
  define ped_dir			char*150
  define archive_dump                   int*2
  define clearit                        int*2
  define write_hv                       int*2
  define ped_online                     int*2
  define beam_param_l[1024]             int*4
  # if array size is changed update caget program
# TDC gamma flash search region
  define gamma_peak_lo, gamma_peak_hi	int*2
# PSD cut settings
  define psd_cut                        int*2
  define tdc_cut_lo, tdc_cut_hi         int*2
  define tdc_rand_lo, tdc_rand_hi         int*2

  define PSD_loband_lo, PSD_loband_hi 	int*2
  define PSD_hiband_lo, PSD_hiband_hi 	int*2
  define psd_base_ch			int*4
  define psd_m_targ			real*4

# Cell mappings for 2D plot
  define row[89],col[89]		int*2
#------------------------------------------------------
## ***** From Pedestals.dat
  define ped_current_l_1[32], ped_current_s_1[32]	int*2
  define ped_current_l_2[32], ped_current_s_2[32]	int*2
  define ped_current_l_3[32], ped_current_s_3[32]	int*2
  define ped_current_ig[32] int*2
#  define ped_current_targ_s, ped_current_targ_l	int*2
#  define ped_current_flux[12] int*2

## Cell Map variables from Cell_Map.dat
define ADC_Cell_to_mod[89]	integer*2
define ADC_Cell_to_chan[89]	integer*2
define TDC_Cell_to_mod[89]	integer*2
define TDC_Cell_to_chan[89]	integer*2
define SCA_Cell_to_mod[89]	integer*2
define SCA_Cell_to_chan[89]	integer*2
define Cell_to_HV[89]		integer*2

## From HV_Calib.dat
  define HVcalib[89]                    real*4
## From psdparams.dat
  define psd_off[89]                    int*4
  define rot_var[89]			real*4
  define psd_val_targ, psd_off_targ     int*2
  define rot_var_targ			real*4
## From tdc_offsets.dat
  define tdc_offset[89]			int*2

##  PSD parameters
  define psd_val[89]                    int*4

  define rebin_by, zero_offset		int*4

define neuts[4], rand[4]				int*4
define diff_neut[4], err_diff_sq[4], tdc_norm		real*4
define asym[2], err[2]					real*4

#############################
define Looker_Counters group
#############################

define looker_counter_group group
  define l_count_adc_gooddata, l_count_adc_nodata, l_count_adc_baddata integer*4
  define l_count_tdc_gooddata, l_count_tdc_nodata, l_count_tdc_baddata integer*4
  define l_count_pedadc_gooddata, l_count_pedadc_nodata, l_count_pedadc_baddata integer*4
  define l_count_lamtrig				int*4
  define l_count_pedestal, l_count_neutron      int*4
  define l_count_flasher, l_count_monitor			int*4
  define l_count_flux, l_count_paddle				int*4
  define r_count_lamtrig				int*4
  define r_count_pedestal, r_count_neutron			int*4
  define r_count_flasher, r_count_monitor			int*4
  define r_count_flux, r_count_paddle				int*4
  define r_count_gamma_enable, l_count_gamma_enable		int*4
#  define r_count_flash_enable, l_count_flash_enable		int*4
#  define r_count_mon_enable, l_count_mon_enable		int*4
#  define r_count_flux_enable, l_count_flux_enable		int*4
  define r_count_scaler,  l_count_scaler	int*4
endgroup

define scaler_group group
  define icell_scaler1[32]   int*4
  define icell_scaler2[32]   int*4
  define icell_scaler3[32]   int*4
  define tcell_scaler1[32]   int*4
  define tcell_scaler2[32]   int*4
  define tcell_scaler3[32]   int*4
  define icell_scaler[97]    int*4
  define tcell_scaler[97]    int*4

  define iscaler1[32]   int*4
  define iscaler2[32]   int*4
  define iscaler3[32]   int*4
  define tscaler1[32]   int*4
  define tscaler2[32]   int*4
  define tscaler3[32]   int*4

  define tclock_scaler[3]   int*4
  define iclock_scaler[3]   int*4
  define real_time, live_time	real*4
  define ireal_time, ilive_time real*4

  define irate1[32]		real*4
  define irate2[32]		real*4
  define irate3[32]		real*4
  define trate1[32]		real*4
  define trate2[32]		real*4
  define trate3[32]		real*4

  define tcell_rate1[32]	real*4
  define tcell_rate2[32]	real*4
  define tcell_rate3[32]	real*4
  define icell_rate1[32]	real*4
  define icell_rate2[32]	real*4
  define icell_rate3[32]	real*4
  define icell_rate[97]    real*4
  define tcell_rate[97]    real*4

  define itarget_count_live, ttarget_count_live	int*4
  define itarget_count_real, ttarget_count_real	int*4
  define itarget_rate_live, ttarget_rate_live	real*4
  define itarget_rate_real, ttarget_rate_real	real*4
endgroup

#############################
endgroup # Looker_Counters
#############################

#############################
define Looker_Histos group
#############################

define ped_data_group group
  define ped_cent_l_1[32], ped_error_l_1[32], ped_sigma_l_1[32], ped_num_l_1[32] real*4
  define ped_cent_s_1[32], ped_error_s_1[32], ped_sigma_s_1[32], ped_num_s_1[32] real*4
  define ped_cent_l_2[32], ped_error_l_2[32], ped_sigma_l_2[32], ped_num_l_2[32] real*4
  define ped_cent_s_2[32], ped_error_s_2[32], ped_sigma_s_2[32], ped_num_s_2[32] real*4
  define ped_cent_l_3[32], ped_error_l_3[32], ped_sigma_l_3[32], ped_num_l_3[32] real*4
  define ped_cent_s_3[32], ped_error_s_3[32], ped_sigma_s_3[32], ped_num_s_3[32] real*4
  define ped_cent_ig[32], ped_error_ig[32], ped_sigma_ig[32], ped_num_ig[32] real*4
#  define ped_cent_targ_s, ped_error_targ_s, ped_sigma_targ_s, ped_num_targ_s real*4
#  define ped_cent_targ_l, ped_error_targ_l, ped_sigma_targ_l, ped_num_targ_l real*4
#  define ped_cent_flux[12], ped_error_flux[12], ped_sigma_flux[12], ped_num_flux[12] real*4
  define ped_ctmp, ped_etmp, ped_stmp, ped_ntmp				real*4
  define ped_tmp		int*4
  define max_chan_l_1, max_cnt_l_1	int*2
  define max_chan_s_1, max_cnt_s_1	int*2
  define max_chan_l_2, max_cnt_l_2	int*2
  define max_chan_s_2, max_cnt_s_2	int*2
  define max_chan_l_3, max_cnt_l_3	int*2
  define max_chan_s_3, max_cnt_s_3	int*2
  define max_chan_ig, max_cnt_ig	int*2
  define max_chan_targ_s, max_cnt_targ_s	int*2
  define max_chan_targ_l, max_cnt_targ_l	int*2
  define max_chan_flux, max_cnt_flux	int*2
endgroup

define rate_histograms group
  define rate_flux      histogram from 0 to 1000 (1000 bins)
  define rate_paddle      histogram from 0 to 1000 (1000 bins)
  define rate_target      histogram from 0 to 1000 (1000 bins)
endgroup
define neut_count_histograms group
  define tmparr0[11], tmparr1[11]				int*4
  define asym_hist[2] histogram from 0 to 11 (11 bins)
endgroup
define raw_histograms group
#  define raw_target_tdc       histogram from 0 to 2048 (2048 bins)
#  define raw_target_adc[2]    histogram from 0 to 1024 (1024 bins)
#  define raw_target_adc_tdc[2]  histogram from 4 to 1024 (255 bins) and
#					from 4 to 4096 (255 bins)
#  define raw_target_psd_ph    histogram from -200 to 200 (100 bins) and
#				  from 4 to 4096 (255 bins)
#  define raw_target_psd_tdc   histogram from -200 to 200 (100 bins) and
#				  from 4 to 4096 (255 bins)
#  define raw_test_psd_tdc   histogram from -200 to 200 (100 bins) and
#				  from 4 to 4096 (255 bins)
  define raw_adc_long_1[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_short_1[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_long_2[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_short_2[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_long_3[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_short_3[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_ig[32] histogram from 1 to 4096 (4095 bins)
  define raw_tdc[89] histogram from 1 to 4095 (4094 bins)
  define raw_tdc_gamma[89] histogram from 1 to 4095 (4094 bins)
  define raw_tdc_neutron[89] histogram from 1 to 4095 (4094 bins)
  define raw_tdc_1[32] histogram from 1 to 4096 (4095 bins)
  define raw_tdc_2[32] histogram from 1 to 4096 (4095 bins)
  define raw_tdc_3[32] histogram from 1 to 4096 (4095 bins)
  define raw_adc_short[89] histogram from 4 to 4096 (1023 bins)
  define raw_adc_long[89] histogram from 4 to 4096 (1023 bins)
  define coin_reg histogram from -1 to 16 (17 bins)
  ## PSD hisotgrams
  define psd_ph[89] histogram from -200 to 200 (100 bins) and
                                  from 0 to 4096 (256 bins)
  define psd[89] histogram from -200 to 200 (400 bins)
  define psd_loband[89] histogram from -200 to 100 (300 bins)
  define psd_hiband[89] histogram from -200 to 100 (300 bins)
  define psd_loband_sm[89] histogram from -200 to 100 (300 bins)
  define psd_hiband_sm[89] histogram from -200 to 100 (300 bins)
  
  define raw_cell_mult histogram from 0 to 89 (89 bins)
  define raw_adc_cell_mult histogram from 0 to 89 (89 bins)
  define raw_cell_mult_map histogram from 0 to 40 (40 bins)
				and from 0 to 89 (89 bins)
  define raw_cell_hits histogram from 0 to 89 (89 bins)
  define raw_tdc_align[89] histogram from 500 to 3200 (2700 bins)
  define raw_tdc_align_gamma[89] histogram from 500 to 3200 (2700 bins)
  define raw_cell_2d[2] histogram from 0 to 16 (16 bins) and
                              	from 0 to 16 (16 bins)
  define raw_adc_long_E[89] histogram from 0 to 3 (300 bins)

endgroup

define N_histograms group
# N = PSD neutron cut
  define N_cell_mult histogram from 0 to 89 (89 bins)
  define N_cell_hits histogram from 0 to 89 (89 bins)
  define N_tdc_arm[9] histogram from 500 to 3200 (2700 bins)
  define N_tdc_ring[12] histogram from 500 to 3200 (2700 bins)
  define N_tdc_align[89] histogram from 500 to 3200 (2700 bins)
  define N_cell_2d[2] histogram from 0 to 16 (16 bins) and
	from 0 to 16 (16 bins)
  define N_adc_tdc[89] histogram from 700 to 3200 (250 bins) and
	from 40 to 4040 (100 bins)
endgroup

define F_histograms group
# F = "full" neutron cut, N+T
  define F_cell_mult histogram from 0 to 89 (89 bins)
  define F_cell_hits histogram from 0 to 89 (89 bins)
  define F_cell_2d[2] histogram from 0 to 16 (16 bins) and
	from 0 to 16 (16 bins)
  define F_neut_sub_2d[2] histogram from 0 to 16 (16 bins) and
	from 0 to 16 (16 bins)
  define F_neut_sub_arm histogram from 0 to 9 (9 bins)
  define F_adc_long[89] histogram from 4 to 4096 (1023 bins)
endgroup

define multiplicity_1_histograms group
  define m1_cell_2d[2] histogram from 0 to 16 (16 bins) and
	from 0 to 16 (16 bins)
  define m1_cell_hits histogram from 0 to 89 (89 bins)
  define m1_psd_ph[89] histogram from -200 to 200 (100 bins) and
                                  from 0 to 4096 (256 bins)
  define m1_psd[89] histogram from -200 to 200 (400 bins)
  define m1_long_short[89] histogram from 0 to 4096 (256 bins)
			and from 0 to 4096 (256 bins)
endgroup

define flash_histograms group
  define flash_multiplicity histogram from 0 to 89 (89 bins)
  define flash_long_1[32] histogram from 0 to 4096 (4096 bins)
  define flash_short_1[32] histogram from 0 to 4096 (4096 bins)
  define flash_long_2[32] histogram from 0 to 4096 (4096 bins)
  define flash_short_2[32] histogram from 0 to 4096 (4096 bins)
  define flash_long_3[32] histogram from 0 to 4096 (4096 bins)
  define flash_short_3[32] histogram from 0 to 4096 (4096 bins)
  define flash_short[89] histogram from 0 to 4096 (1024 bins)
  define flash_long[89] histogram from 0 to 4096 (1024 bins)
  define flash_pulser1[23] histogram from 0 to 4096 (1024 bins)
  define flash_pulser2[23] histogram from 0 to 4096 (1024 bins)
  define flash_pulser3[23] histogram from 0 to 4096 (1024 bins)
  define flash_pulser4[23] histogram from 0 to 4096 (1024 bins)
  define flash_volt histogram from 0 to 4096 (4096 bins)
  define flash_monitor[7] histogram from 0 to 4096 (4096 bins)
  define flash_sourcemon_ig_raw[32] histogram from 0 to 4096 (4096 bins)
  define flash_sourcemon[7] histogram from 0 to 4096 (1024 bins)
  define flash_sourcemon_bits histogram from 1 to 7 (6 bins)
endgroup

define flux_histogram group
  define flux_ig_raw[32] histogram from 1 to 4096 (4095 bins)
  define flux_tdc_raw[8] histogram from 0 to 1024 (1024 bins)
  define flux_adc_raw histogram from 0 to 8192 (8192 bins)
endgroup

define paddle_hisotram group
  define paddle_ig_raw[32] histogram from 1 to 4096 (4095 bins)
  define paddle_tdc_raw[8] histogram from 0 to 1024 (1024 bins)
  define paddle_veto histogram from 1 to 4096 (4095 bins)
  define paddle_2 histogram from 1 to 4096 (4095 bins)
  define paddle_3 histogram from 1 to 4096 (4095 bins)
  define paddle_2_3 histogram from 1 to 4096 (256 bins)
                          and from 1 to 4096 (256 bins)
endgroup


define monitor_var_group group
  define source_peak[7], source_peakerr[7]	real*4
  define source_stdev[7], source_stdeverr[7]	real*4
  define volt_peak, volt_peakerr	real*4
  define volt_stdev, volt_stdeverr	real*4
  define monitor_peak[7], monitor_peakerr[7]	real*4
  define monitor_stdev[7], monitor_stdeverr[7]	real*4
  define flash_long_peak[89], flash_long_peakerr[89]	real*4
  define flash_long_stdev[89], flash_long_stdeverr[89]	real*4
  define flash_short_peak[89], flash_short_peakerr[89]	real*4
  define flash_short_stdev[89], flash_short_stdeverr[89]	real*4
endgroup

#############################
define ped_histograms group
#############################
  define ped_sub_l_1[32] histogram from -50 to 50 (100 bins)
  define ped_sub_s_1[32] histogram from -50 to 50 (100 bins)
  define ped_sub_l_2[32] histogram from -50 to 50 (100 bins)
  define ped_sub_s_2[32] histogram from -50 to 50 (100 bins)
  define ped_sub_l_3[32] histogram from -50 to 50 (100 bins)
  define ped_sub_s_3[32] histogram from -50 to 50 (100 bins)
  define ped_sub_ig[32] histogram from -50 to 50 (100 bins)
  define ped_raw_l_1[32] histogram from 0 to 300 (300 bins)
  define ped_raw_s_1[32] histogram from 0 to 300 (300 bins)
  define ped_raw_l_2[32] histogram from 0 to 300 (300 bins)
  define ped_raw_s_2[32] histogram from 0 to 300 (300 bins)
  define ped_raw_l_3[32] histogram from 0 to 300 (300 bins)
  define ped_raw_s_3[32] histogram from 0 to 300 (300 bins)
  define ped_raw_ig[32] histogram from 0 to 300 (300 bins)
#  define ped_raw_targ_s histogram from 0 to 300 (300 bins)
#  define ped_raw_targ_l histogram from 0 to 300 (300 bins)
#  define ped_sub_targ_s histogram from -50 to 50 (100 bins)
#  define ped_sub_targ_l histogram from -50 to 50 (100 bins)
#  define ped_raw_flux[12] histogram from 0 to 300 (300 bins)
#  define ped_sub_flux[12] histogram from -50 to 50 (100 bins)
endgroup

#############################
endgroup  # Looker_Histos
#############################

# -------------------------------------------------------------------
# Start event definitions below
# -------------------------------------------------------------------

########################################
beginrun:
########################################

runno = LUCIDrun

if Lucidloadvars("blowfish.dat") < 0
  print "*** ERROR READING 'blowfish.dat' ***"
endif
# exp_dir (the experiment home directory) is read from blowfish.dat

call stringcat(program_name, exp_dir, "/bin/dumpcheck")
print runno to program program_name  # clean up dump directory
print runno to "dump/.start"
print "Starting run ",runno to "dump/run.info"
print "" to "/dev/null"

# Make the files to be read by Lucidloadvars
#call stringcat(program_name, exp_dir, "/bin/makelookerfiles")
#print runno to program program_name

print "------------- Beginning run ", runno, " -------------"
print ""

print " --> Cell_Map.dat ..."
if Lucidloadvars("Cell_Map.dat") < 0
  print "*** ERROR READING 'Cell_Map.dat' ***"
endif

print " --> tdc_offsets.dat ..."
if Lucidloadvars("tdc_offsets.dat") < 0
  print "*** ERROR READING 'tdc_offsets.dat' ***"
endif
print " --> psdparams.dat ..."
if Lucidloadvars("psdparams.dat") < 0
  print "*** ERROR READING 'psdparams.dat' ***"
endif
print " --> gains.dat ..."
if Lucidloadvars("gains.dat") < 0
  print "*** ERROR READING 'gains.dat' ***"
endif


if (clearit == 1) then
  print "Initializing histograms and counters..."
  runs = 0
  runs[0] = runno
  num_runs = 1
  Looker_Histos   = 0
  Looker_Counters = 0
else
  print ""
  print "---> NOT <--- Initializing histograms or counters..."
  # So histograms will possibly be an accumulation of runs
  if(num_runs < 99)
    runs[num_runs] = runno
    num_runs += 1
    print " --> More than one data file is histogrammed."
    call print_run_nums(runs, "")
  else
    print "ERROR: Too many runs: Maximum num_runs = 99"
  endif
endif

#-------------- end of beginrun event ------------------------


########################################
event startup:
########################################

print ""
print "Analysing data... from run ",runno
#timestart = LUCIDtime
#call convert_time(timestart, datestart)
#print "     Started on ",datestart

if( Accel_on == 1)    print "    Accelerator ON mode"
else                  print "    Accelerator OFF mode"        endif
if( HVread_en == 1)   print "    High Voltages read"
else                  print "    High Voltages NOT read" endif
if( Xarm_en == 1)     print "    X-arm enabled"
else                  print "    X-arm disabled" endif
if( Ped_en == 1)      print "    Pedestals enabled every ",Ped_prescale," N-trig events"
else                  print "    Pedestals disabled" endif
if( AltPed_en == 1)   print "    Alternate pedestal source used"
else		      print "    Pedestals triggered by N-OR" endif
if( Gamma_en == 1)    print "    Gamma window enabled every ",Gamma_prescale," N-trig events"
else		      print "    Gamma window disabled" endif
if( Flash_en == 1)    print "    Flashers enabled"
else		      print "    Flashers disabled" endif
if( Mon_en == 1)      print "    Flasher Monitor events enabled"
else		      print "    Flasher Monitor events disabled" endif
		      print "    Flasher Monitor multiplying factor = ",Mon_mult
if( Flux_en == 1)     print "    Flux Monitor events enabled"
		      print "    Flux time multiplying factor = ",Flux_mult
else		      print "    Flux Monitor events disabled" endif
if( Paddle_en == 1)   print "    Paddle Monitor events enabled"
		      print "    Paddle time multiplying factor = ",Paddle_mult
else		      print "    Paddle Monitor events disabled" endif
if( GP_en == 1)       print "    DAQ expecting GIANT Pulse mode from ring"
else                  print "    DAQ expecting regular pulse mode from ring" endif
print ""

# for dump file
print "**** Run ",runno," ****" to "dump/run.info"
if( Accel_on == 1)    print "    Accelerator ON mode" to "dump/run.info"
else                  print "    Accelerator OFF mode" to "dump/run.info"        endif
if( HVread_en == 1)   print "    High Voltages read" to "dump/run.info"
else                  print "    High Voltages NOT read" to "dump/run.info" endif
if( Xarm_en == 1)     print "    X-arm enabled" to "dump/run.info"
else                  print "    X-arm disabled" to "dump/run.info" endif
if( Ped_en == 1)      print "    Pedestals enabled every ",Ped_prescale," N-trig events" to "dump/run.info"
else                  print "    Pedestals disabled" to "dump/run.info" endif
if( AltPed_en == 1)   print "    Alternate pedestal source used" to "dump/run.info"
else		      print "    Pedestals triggered by N-OR" to "dump/run.info" endif
if( Gamma_en == 1)    print "    Gamma window enabled every ",Gamma_prescale," N-trig events" to "dump/run.info"
else		      print "    Gamma window disabled" to "dump/run.info" endif
if( Flash_en == 1)    print "    Flashers enabled" to "dump/run.info"
else		      print "    Flashers disabled" to "dump/run.info" endif
if( Mon_en == 1)      print "    Flasher Monitor events enabled" to "dump/run.info"
else		      print "    Flasher Monitor events disabled" to "dump/run.info" endif
		      print "    Flasher Monitor multiplying factor = ",Mon_mult to "dump/run.info"
if( Flux_en == 1)     print "    Flux Monitor events enabled" to "dump/run.info"
		      print "    Flux time multiplying factor = ",Flux_mult to "dump/run.info"
else		      print "    Flux Monitor events disabled" to "dump/run.info" endif
if( Paddle_en == 1)   print "    Paddle Monitor events enabled" to "dump/run.info"
		      print "    Paddle time multiplying factor = ",Paddle_mult to "dump/run.info"
else		      print "    Paddle Monitor events disabled" to "dump/run.info" endif
if( GP_en == 1)       print "    DAQ expecting GIANT Pulse mode from ring" to "dump/run.info"
else                  print "    DAQ expecting regular pulse mode from ring" to "dump/run.info" endif

beam_param_l = beam_params
#call decode_caget(beam_param_l, 1024)

# ped_online is read from blowfish.dat
if(ped_online != 0)
	# use the online pedestals
	ped_current_l_1 = pedestals_l_1
	ped_current_s_1 = pedestals_s_1
	ped_current_l_2 = pedestals_l_2
	ped_current_s_2 = pedestals_s_2
	ped_current_l_3 = pedestals_l_3
	ped_current_s_3 = pedestals_s_3
	ped_current_ig = pedestals_ig
	
#	ped_current_targ_s = pedestals_targ_s
#	ped_current_targ_l = pedestals_targ_l
#	
#	ped_current_flux   = pedestals_flux
else
	# use pedestals read from Pedestals.dat
	print "Using pedestals from 'Pedestals.dat'"
	if Lucidloadvars("Pedestals.dat") < 0
		print "*** ERROR READING 'Pedestals.dat' ***"
	endif
endif

## Make sure HV supply isn't screwed up
repeat i from 1 to 88
  zI1tmp = hv_measured[i]-hv_demand[i]
  if(zI1tmp < 0 ) zI1tmp = -zI1tmp endif
  if( zI1tmp > 5 && hv_demand[i] != 0) then
    print " -!!-> hv_demand[",i,"] = ",hv_demand[i],
             "    hv_measured[",i,"] = ",hv_measured[i]
  endif
endrepeat
print " Done checking if hv(measured) = hv(demand)."

# Save HV for looker use - referenced to cell number
repeat icell from 1 to 88
	l_hv_measured[icell] = hv_measured[Cell_to_HV[icell]]
	l_hv_demand[icell] = hv_demand[Cell_to_HV[icell]]
endrepeat

print ""
#-------------- end of startup event ------------------------

########################################
event lamtrig(some):
########################################

l_count_lamtrig += 1
r_count_lamtrig = count_lamtrig

repeat i from 0 to 8
        if( ( ( lam_ioreg >> i) & 1) == 1) then
                increment coin_reg using i
        endif
endrepeat
if( lam_ioreg == 0) then
        increment coin_reg using -1
endif

#-------------- end of lamtrig event ------------------------

########################################
event flux(some):
########################################
l_count_flux += 1
r_count_flux = count_flux

call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

increment flux_ig_raw using vmeadc_ig_raw
adc_ig = vmeadc_ig_raw - ped_current_ig
# flux adc is an Ortec 513
increment flux_adc_raw using flux_adc
increment flux_tdc_raw using flux_tdc

#-------------- end of flux event ------------------------

########################################
event paddle(some):
########################################
l_count_paddle += 1
r_count_paddle = count_paddle

call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

increment paddle_ig_raw using vmeadc_ig_raw
adc_ig = vmeadc_ig_raw - ped_current_ig
increment paddle_veto using adc_ig[13]
increment paddle_2 using adc_ig[14]
increment paddle_3 using adc_ig[15]
increment paddle_2_3 using adc_ig[14], adc_ig[15]
increment paddle_tdc_raw using flux_tdc

#-------------- end of paddle event ------------------------
########################################
event pedestal(some):
########################################

l_count_pedestal += 1
r_count_pedestal = count_pedestal

########################################################################
#       Looker code for decoding the caen module data
#	Chabot compression (Headers included)
#
#######################################################################
call decode_vme(vmeadc_l_1, sizeof(vmeadc_l_1), vmeadc_l_1_raw, 32, buffers, notvalid)
adcnotvalid_l[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_1, sizeof(vmeadc_s_1), vmeadc_s_1_raw, 32, buffers, notvalid)
adcnotvalid_s[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_2, sizeof(vmeadc_l_2), vmeadc_l_2_raw, 32, buffers, notvalid)
adcnotvalid_l[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_2, sizeof(vmeadc_s_2), vmeadc_s_2_raw, 32, buffers, notvalid)
adcnotvalid_s[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_3, sizeof(vmeadc_l_3), vmeadc_l_3_raw, 32, buffers, notvalid)
adcnotvalid_l[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_3, sizeof(vmeadc_s_3), vmeadc_s_3_raw, 32, buffers, notvalid)
adcnotvalid_s[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

repeat i from 0 to 31
	if( vmeadc_l_1_raw[i] > 0 )
                increment ped_raw_l_1[i] using vmeadc_l_1_raw[i]
                increment ped_sub_l_1[i] using vmeadc_l_1_raw[i] - ped_current_l_1[i]
	endif
	if( vmeadc_s_1_raw[i] > 0 )
                increment ped_raw_s_1[i] using vmeadc_s_1_raw[i]
                increment ped_sub_s_1[i] using vmeadc_s_1_raw[i] - ped_current_s_1[i]
	endif
	if( vmeadc_l_2_raw[i] > 0 )
                increment ped_raw_l_2[i] using vmeadc_l_2_raw[i]
                increment ped_sub_l_2[i] using vmeadc_l_2_raw[i] - ped_current_l_2[i]
	endif
	if( vmeadc_s_2_raw[i] > 0 )
                increment ped_raw_s_2[i] using vmeadc_s_2_raw[i]
                increment ped_sub_s_2[i] using vmeadc_s_2_raw[i] - ped_current_s_2[i]
	endif
	if( vmeadc_l_3_raw[i] > 0 )
                increment ped_raw_l_3[i] using vmeadc_l_3_raw[i]
                increment ped_sub_l_3[i] using vmeadc_l_3_raw[i] - ped_current_l_3[i]
	endif
	if( vmeadc_s_3_raw[i] > 0 )
                increment ped_raw_s_3[i] using vmeadc_s_3_raw[i]
                increment ped_sub_s_3[i] using vmeadc_s_3_raw[i] - ped_current_s_3[i]
	endif
	if( vmeadc_ig_raw[i] > 0 )
                increment ped_raw_ig[i] using vmeadc_ig_raw[i]
                increment ped_sub_ig[i] using vmeadc_ig_raw[i] - ped_current_ig[i]
	endif
endrepeat
##############################################################################
# increment ped_raw_targ_s using targ_adc_s
# increment ped_sub_targ_s using targ_adc_s - ped_current_targ_s
# increment ped_raw_targ_l using targ_adc_l
# increment ped_sub_targ_l using targ_adc_l - ped_current_targ_l

# increment ped_raw_flux using flux_adc
# increment ped_sub_flux using flux_adc - ped_current_flux
#-------------- end of pedestal event ------------------------

########################################
event neutron(some):
########################################

l_count_neutron += 1
r_count_neutron = count_neutron

if(Gamma_currently_enabled == 1) l_count_gamma_enable += 1 endif
r_count_gamma_enable = count_gamma_enable

########################################################################
#       Looker code for decoding the caen module data
#	Chabot compression (Headers included)
#
#######################################################################
call decode_vme(vmeadc_l_1, sizeof(vmeadc_l_1), vmeadc_l_1_raw, 32, buffers, notvalid)
adcnotvalid_l[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_1, sizeof(vmeadc_s_1), vmeadc_s_1_raw, 32, buffers, notvalid)
adcnotvalid_s[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_2, sizeof(vmeadc_l_2), vmeadc_l_2_raw, 32, buffers, notvalid)
adcnotvalid_l[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_2, sizeof(vmeadc_s_2), vmeadc_s_2_raw, 32, buffers, notvalid)
adcnotvalid_s[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_3, sizeof(vmeadc_l_3), vmeadc_l_3_raw, 32, buffers, notvalid)
adcnotvalid_l[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_3, sizeof(vmeadc_s_3), vmeadc_s_3_raw, 32, buffers, notvalid)
adcnotvalid_s[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_1, sizeof(vmetdc_1), vmetdc_1_raw, 32, buffers, notvalid)
tdcnotvalid[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_2, sizeof(vmetdc_2), vmetdc_2_raw, 32, buffers, notvalid)
tdcnotvalid[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_3, sizeof(vmetdc_3), vmetdc_3_raw, 32, buffers, notvalid)
tdcnotvalid[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

# Raw histograms
  adc_long  = 0
  adc_short = 0
  cell_tdc  = 0
  increment raw_adc_long_1 using vmeadc_l_1_raw
  increment raw_adc_long_2 using vmeadc_l_2_raw
  increment raw_adc_long_3 using vmeadc_l_3_raw
  increment raw_adc_short_1 using vmeadc_s_1_raw
  increment raw_adc_short_2 using vmeadc_s_2_raw
  increment raw_adc_short_3 using vmeadc_s_3_raw
  increment raw_tdc_1 using vmetdc_1_raw
  increment raw_tdc_2 using vmetdc_2_raw
  increment raw_tdc_3 using vmetdc_3_raw
  increment raw_adc_ig using vmeadc_ig_raw

# Mapping to cells
repeat icell from 1 to 88
   if(ADC_Cell_to_mod[icell] == 1)
      adc_short[icell] = vmeadc_s_1_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_1[ADC_Cell_to_chan[icell]]
      adc_long[icell] = vmeadc_l_1_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_1[ADC_Cell_to_chan[icell]]
   endif
   if(ADC_Cell_to_mod[icell] == 2)
      adc_short[icell] = vmeadc_s_2_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_2[ADC_Cell_to_chan[icell]]
      adc_long[icell] = vmeadc_l_2_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_2[ADC_Cell_to_chan[icell]]
   endif
   if(ADC_Cell_to_mod[icell] == 3)
      adc_short[icell] = vmeadc_s_3_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_3[ADC_Cell_to_chan[icell]]
      adc_long[icell] = vmeadc_l_3_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_3[ADC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 1)
      cell_tdc[icell] = vmetdc_1_raw[TDC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 2)
      cell_tdc[icell] = vmetdc_2_raw[TDC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 3)
      cell_tdc[icell] = vmetdc_3_raw[TDC_Cell_to_chan[icell]]
   endif
endrepeat
adc_ig = vmeadc_ig_raw - ped_current_ig
increment raw_tdc using cell_tdc
if( Gamma_currently_enabled == 1)
  increment raw_tdc_gamma using cell_tdc
else
  increment raw_tdc_neutron using cell_tdc
endif
###  Get Cell multiplicity and calculate PSD ###
cell_mult = 0
cell_adc_mult = 0
repeat i from 1 to 88
    if( cell_tdc[i] > 0 && cell_tdc[i] < 4095 )
      cell_mult[0] += 1
      cell_mult[cell_mult[0]] = i
    endif
    if( adc_long[i] > 150 )
      cell_adc_mult[0] += 1
      cell_adc_mult[cell_mult[0]] = i
    endif
endrepeat
#######################################################################

  increment raw_adc_cell_mult using cell_adc_mult[0]

  #--------------------------------------
  #TDC alignment variable and cell hit detection
  #--------------------------------------
increment raw_cell_mult using cell_mult[0]
repeat i from 1 to cell_mult[0]
    increment raw_cell_mult_map using cell_mult[0] and cell_mult[i]
endrepeat

  #------------------------------
  ## Run over all cells with a hit in them (no cuts applied)
  #------------------------------
  repeat i from 1 to cell_mult[0]
    icell = cell_mult[i]
    tdc_align[icell] = cell_tdc[icell] - tdc_offset[icell] + 1000
    increment raw_tdc_align[0] using tdc_align[icell]
    increment raw_tdc_align[icell] using tdc_align[icell]
    increment raw_cell_2d[icell/49] using col[icell], row[icell]
    increment raw_cell_hits using icell
    if(Gamma_currently_enabled == 1)
      increment raw_tdc_align_gamma[0] using tdc_align[icell]
      increment raw_tdc_align_gamma[icell] using tdc_align[icell]
    endif
    increment raw_adc_short[icell] using adc_short[icell]
    increment raw_adc_long[icell] using adc_long[icell]

    # PSD stuff
    if( adc_long[icell] > 0  &&  adc_short[icell] > 0 )
      psd_val[icell]   = adc_long[icell] - adc_short[icell] +
                           psd_off[icell] - rot_var[icell]*adc_long[icell]
      increment psd_ph[0] using psd_val[icell], adc_long[icell]
      increment psd_ph[icell] using psd_val[icell], adc_long[icell]
      increment psd[0] using psd_val[icell]
      increment psd[icell] using psd_val[icell]
      if(adc_long[icell] >= PSD_loband_lo && adc_long[icell] < PSD_loband_hi) 
          increment psd_loband[0] using psd_val[icell]
          increment psd_loband[icell] using psd_val[icell]
        endif
        if(adc_long[icell] >= PSD_hiband_lo && adc_long[icell] < PSD_hiband_hi) 
          increment psd_hiband[0] using psd_val[icell]
          increment psd_hiband[icell] using psd_val[icell]
        endif

    endif

  endrepeat
  #--------------------------------------
  #setup cell multiplicities for cuts
  #--------------------------------------
  Ncell_mult = 0
  Fcell_mult = 0
  repeat i from 1 to cell_mult[0]
    icell = cell_mult[i]
    ## Apply ADC energy calibration
    adc_long_E[icell]  = adc_long[icell]  * cell_gain[icell]
    increment raw_adc_long_E[icell] using adc_long_E[icell]
    increment raw_adc_long_E[0] using adc_long_E[icell]

    if( psd_val[icell] >= psd_cut ) then
        Ncell_mult[0] += 1
        Ncell_mult[Ncell_mult[0]] = icell
        if( tdc_align[icell] >= tdc_cut_lo && tdc_align[icell] < tdc_cut_hi )
           Fcell_mult[0] += 1
           Fcell_mult[Fcell_mult[0]] = icell
        endif
    endif
  endrepeat
  increment N_cell_mult using Ncell_mult[0]
  increment F_cell_mult using Fcell_mult[0]

  #--------------------------------------
  #Neutron PSD cut applied
  #--------------------------------------
  repeat i from 1 to Ncell_mult[0]
    icell = Ncell_mult[i]
    increment N_cell_2d[icell/49] using col[icell],row[icell]
    increment N_cell_hits using icell
    increment N_tdc_align[0] using tdc_align[icell]
    increment N_tdc_align[icell] using tdc_align[icell]
    increment N_adc_tdc[0] using tdc_align[icell] and adc_long[icell]
    increment N_adc_tdc[icell] using tdc_align[icell] and adc_long[icell]

    increment N_tdc_arm[0] using tdc_align[icell]
  # cell group histogram
    iarm=(icell-1)%8 + 1
    increment N_tdc_arm[iarm] using tdc_align[icell]
    increment N_tdc_arm[0] using tdc_align[icell]
    iring = (icell-1)/8 + 1
    increment N_tdc_ring[iring] using tdc_align[icell]
    increment N_tdc_ring[0] using tdc_align[icell]

    ## randoms have to pass the psd cut (but not, of course, the neut timing cut)
    if( (tdc_align[icell] >= tdc_rand_lo) && (tdc_align[icell] <= tdc_rand_hi) ) then
      rand_count[icell] += 1
    endif
  endrepeat

  #--------------------------------------
  ##final (psd, cell tdc)
  #--------------------------------------
  repeat i from 1 to Fcell_mult[0]
    icell = Fcell_mult[i]
    increment F_cell_2d[icell/49] using col[icell],row[icell]
    increment F_cell_hits using icell
    F_neut_count[icell] += 1
    increment F_adc_long[0]     using adc_long[icell]
    increment F_adc_long[icell] using adc_long[icell]
  endrepeat

### Multiplicity 1 from here on
#------------------------------
if cell_mult[0] > 1
    reject
endif
  icell = cell_mult[1]

  if( adc_long[icell] > 0 && adc_short[icell] > 0 )
      increment m1_long_short[icell] using adc_long[icell], adc_short[icell]
      increment m1_psd_ph[0] using psd_val[icell], adc_long[icell]
      increment m1_psd_ph[icell] using psd_val[icell], adc_long[icell]
      increment m1_psd[0] using psd_val[icell]
      increment m1_psd[icell] using psd_val[icell]
  endif

  increment m1_cell_2d[icell/49] using col[icell], row[icell]
  increment m1_cell_hits using icell


#-------------- end of neutron event ------------------------

########################################
event flasher(some):
########################################

l_count_flasher += 1
r_count_flasher = count_flasher

########################################################################
#       Looker code for decoding the caen module data
#	Chabot compression (Headers included)
#
#######################################################################
call decode_vme(vmeadc_l_1, sizeof(vmeadc_l_1), vmeadc_l_1_raw, 32, buffers, notvalid)
adcnotvalid_l[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_1, sizeof(vmeadc_s_1), vmeadc_s_1_raw, 32, buffers, notvalid)
adcnotvalid_s[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_2, sizeof(vmeadc_l_2), vmeadc_l_2_raw, 32, buffers, notvalid)
adcnotvalid_l[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_2, sizeof(vmeadc_s_2), vmeadc_s_2_raw, 32, buffers, notvalid)
adcnotvalid_s[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_l_3, sizeof(vmeadc_l_3), vmeadc_l_3_raw, 32, buffers, notvalid)
adcnotvalid_l[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_s_3, sizeof(vmeadc_s_3), vmeadc_s_3_raw, 32, buffers, notvalid)
adcnotvalid_s[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_1, sizeof(vmetdc_1), vmetdc_1_raw, 32, buffers, notvalid)
tdcnotvalid[1] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_2, sizeof(vmetdc_2), vmetdc_2_raw, 32, buffers, notvalid)
tdcnotvalid[2] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmetdc_3, sizeof(vmetdc_3), vmetdc_3_raw, 32, buffers, notvalid)
tdcnotvalid[3] += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

# Mapping to cells
repeat icell from 1 to 88
   if(ADC_Cell_to_mod[icell] == 1)
      flash_adc_short[icell] = vmeadc_s_1_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_1[ADC_Cell_to_chan[icell]]
      flash_adc_long[icell] = vmeadc_l_1_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_1[ADC_Cell_to_chan[icell]]
   endif
   if(ADC_Cell_to_mod[icell] == 2)
      flash_adc_short[icell] = vmeadc_s_2_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_2[ADC_Cell_to_chan[icell]]
      flash_adc_long[icell] = vmeadc_l_2_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_2[ADC_Cell_to_chan[icell]]
   endif
   if(ADC_Cell_to_mod[icell] == 3)
      flash_adc_short[icell] = vmeadc_s_3_raw[ADC_Cell_to_chan[icell]]
			- ped_current_s_3[ADC_Cell_to_chan[icell]]
      flash_adc_long[icell] = vmeadc_l_3_raw[ADC_Cell_to_chan[icell]]
			- ped_current_l_3[ADC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 1)
      flash_cell_tdc[icell] = vmetdc_1_raw[TDC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 2)
      flash_cell_tdc[icell] = vmetdc_2_raw[TDC_Cell_to_chan[icell]]
   endif
   if(TDC_Cell_to_mod[icell] == 3)
      flash_cell_tdc[icell] = vmetdc_3_raw[TDC_Cell_to_chan[icell]]
   endif
endrepeat
flash_adc_ig = vmeadc_ig_raw - ped_current_ig

###  Get Cell multiplicity ###
flash_cell_mult = 0
flash_cell_adc_mult = 0
repeat i from 1 to 88
    if( flash_cell_tdc[i] > 0 && flash_cell_tdc[i] < 4095 )
      flash_cell_mult[0] += 1
      flash_cell_mult[cell_mult[0]] = i
    endif
    if( flash_adc_long[i] > 150 )
      flash_cell_adc_mult[0] += 1
      flash_cell_adc_mult[cell_mult[0]] = i
    endif
endrepeat

  increment flash_multiplicity using flash_cell_mult[0]
  repeat i from 0 to 5
    increment flash_monitor[i+1] using flash_adc_ig[i]
  endrepeat 
  increment flash_volt using flash_adc_ig[6]
  
  increment flash_long_1  using vmeadc_l_1_raw
  increment flash_short_1 using vmeadc_s_1_raw
  increment flash_long_2  using vmeadc_l_2_raw
  increment flash_short_2 using vmeadc_s_2_raw
  increment flash_long_3  using vmeadc_l_3_raw
  increment flash_short_3 using vmeadc_s_3_raw
  increment flash_long using flash_adc_long
  increment flash_short using flash_adc_short
  repeat j from 1 to 11
    increment flash_pulser1[j] using flash_adc_long[(j-1)*8+1]
    increment flash_pulser1[j+11] using flash_adc_long[(j-1)*8+2]
    increment flash_pulser2[j] using flash_adc_long[(j-1)*8+3]
    increment flash_pulser2[j+11] using flash_adc_long[(j-1)*8+4]
    increment flash_pulser3[j] using flash_adc_long[(j-1)*8+5]
    increment flash_pulser3[j+11] using flash_adc_long[(j-1)*8+6]
    increment flash_pulser4[j] using flash_adc_long[(j-1)*8+7]
    increment flash_pulser4[j+11] using flash_adc_long[(j-1)*8+8]
  endrepeat

########################################
event monitor:
########################################

l_count_monitor += 1
r_count_monitor=count_monitor

########################################################################
#
#       Looker code for decoding the caen module data
#
call decode_vme(vmeadc_ig, sizeof(vmeadc_ig), vmeadc_ig_raw, 32, buffers, notvalid)
adcnotvalid_ig += notvalid
if(buffers > 0) adcbuffer_mult_ig += buffers-1 endif

monitor_bits = coinreg >> 7
flash_adc_ig = vmeadc_ig_raw - ped_current_ig
increment flash_sourcemon_ig_raw using vmeadc_ig_raw
repeat i from 1 to 6
	if( flash_adc_ig[i-1] > 50)
		increment flash_sourcemon[i] using flash_adc_ig[i-1]
	endif
        if( ((monitor_bits >> i) & 1) == 1)
                increment flash_sourcemon_bits using i
        endif
endrepeat
#########################################################################

########################################
event scalerread:
########################################
l_count_scaler += 1
r_count_scaler = count_scalerread

r_count_lamtrig = count_lamtrig
r_count_neutron = count_neutron
r_count_pedestal = count_pedestal
r_count_flasher = count_flasher
r_count_monitor = count_monitor
r_count_flux = count_flux
r_count_paddle = count_paddle

iscaler1 = scaler1
iscaler2 = scaler2
iscaler3 = scaler3
tscaler1 += scaler1
tscaler2 += scaler2
tscaler3 += scaler3

icell_scaler1 = cell_scaler1
icell_scaler2 = cell_scaler2
icell_scaler3 = cell_scaler3
tcell_scaler1 += cell_scaler1
tcell_scaler2 += cell_scaler2
tcell_scaler3 += cell_scaler3

iclock_scaler[0] = scaler1[15]
iclock_scaler[1] = scaler2[15]
iclock_scaler[2] = scaler3[15]
tclock_scaler[0] += scaler1[15]
tclock_scaler[1] += scaler2[15]
tclock_scaler[2] += scaler3[15]

ilive_time = iclock_scaler[1]/1000.
ireal_time = iclock_scaler[0]/1000.
live_time = tclock_scaler[1]/1000.
real_time = tclock_scaler[0]/1000.

if( ireal_time == 0 )
  ireal_time = 999999999.
endif
if( real_time == 0 )
  real_time = 999999999.
endif

irate1 = iscaler1 / ireal_time
irate2 = iscaler2 / ireal_time
irate3 = iscaler3 / ireal_time
trate1 = tscaler1 / real_time
trate2 = tscaler2 / real_time
trate3 = tscaler3 / real_time

icell_rate1 = icell_scaler1 / ireal_time
icell_rate2 = icell_scaler2 / ireal_time
icell_rate3 = icell_scaler3 / ireal_time
tcell_rate1 = tcell_scaler1 / real_time
tcell_rate2 = tcell_scaler2 / real_time
tcell_rate3 = tcell_scaler3 / real_time

# Cell mapping
repeat icell from 1 to 88
	if(SCA_Cell_to_mod[icell] == 1)
        	icell_scaler[icell] = icell_scaler1[SCA_Cell_to_chan[icell]]
        	tcell_scaler[icell] = tcell_scaler1[SCA_Cell_to_chan[icell]]
        	icell_rate[icell]   = icell_rate1[SCA_Cell_to_chan[icell]]
        	tcell_rate[icell]   = tcell_rate1[SCA_Cell_to_chan[icell]]
	endif
	if(SCA_Cell_to_mod[icell] == 2)
        	icell_scaler[icell] = icell_scaler2[SCA_Cell_to_chan[icell]]
        	tcell_scaler[icell] = tcell_scaler2[SCA_Cell_to_chan[icell]]
        	icell_rate[icell]   = icell_rate2[SCA_Cell_to_chan[icell]]
        	tcell_rate[icell]   = tcell_rate2[SCA_Cell_to_chan[icell]]
	endif
	if(SCA_Cell_to_mod[icell] == 3)
        	icell_scaler[icell] = icell_scaler3[SCA_Cell_to_chan[icell]]
        	tcell_scaler[icell] = tcell_scaler3[SCA_Cell_to_chan[icell]]
        	icell_rate[icell]   = icell_rate3[SCA_Cell_to_chan[icell]]
        	tcell_rate[icell]   = tcell_rate3[SCA_Cell_to_chan[icell]]
	endif
endrepeat

## Break out target scaler data
itarget_count_live = iscaler1[5]
ttarget_count_live = tscaler1[5]
itarget_rate_live  = irate1[5]
ttarget_rate_live  = trate1[5]
itarget_count_real = iscaler2[5]
ttarget_count_real = tscaler2[5]
itarget_rate_real  = irate2[5]
ttarget_rate_real  = trate2[5]

## Build rate strip chart histos
zA1024tmp = rate_target
zA1024tmp[l_count_scaler%1000] = itarget_rate_live
rate_target = zA1024tmp

zA1024tmp = rate_paddle
zA1024tmp[l_count_scaler%1000] = irate1[13]
rate_paddle = zA1024tmp

zA1024tmp = rate_flux
zA1024tmp[l_count_scaler%1000] = irate2[8]
rate_flux = zA1024tmp


# ------------ end of scalerread event ---------------------- 
########################################
event goodbye:
########################################
print ""
#timestop = LUCIDtime
#call convert_time(timestop, datestop)
#print "     Run ",runno," ended on ",datestop

## Make sure HV supply did not shift during run
repeat i from 1 to 88
  zI1tmp = hv_measured[i]-hv_demand[i]
  if(zI1tmp < 0 ) zI1tmp = -zI1tmp endif
  if( zI1tmp > 5 && hv_demand[i] != 0) then
    print " -!!-> hv_demand[",i,"] = ",hv_demand[i],
             "    hv_measured[",i,"] = ",hv_measured[i]
  endif
  zI1tmp = hv_measured[Cell_to_HV[i]]-l_hv_measured[i]
  if(zI1tmp < 0 ) zI1tmp = -zI1tmp endif
  if( zI1tmp > 2 && hv_demand[i] != 0) then
    print " -!!-> HV channel ",Cell_to_HV[i]," @ startrun = ",l_hv_measured[i],
             "    @ endrun = ",hv_measured[Cell_to_HV[i]]
  endif
endrepeat
print " Done checking if HV(measured) = HV(demand)"
print "              and HV(beginrun) = HV(endrun)."
########################################
endrun:
########################################

print ""
print "*** End of Run Status: ***"
print "                    Looker	Reader"
print "count_neutron     = ", l_count_neutron, "	   ", r_count_neutron
print "count_pedestal    = ", l_count_pedestal, "	   ", r_count_pedestal
print "count_flasher     = ", l_count_flasher, "	   ", r_count_flasher
print "count_monitor    = ", l_count_monitor, "	   ", r_count_monitor
print "count_flux        = ", l_count_flux, "	   ", r_count_flux
print "count_gamma_enable = ", l_count_gamma_enable, "	   ", r_count_gamma_enable
#print "count_flash_enable = ", l_count_flash_enable, "	   ", r_count_flash_enable
#print "count_mon_enable = ", l_count_mon_enable, "	   ", r_count_mon_enable
#print "count_flux_enable = ", l_count_flux_enable, "	   ", r_count_flux_enable
print ""
print "Real time (s):       ", real_time
print "Live time (s):       ", live_time
print "Live   fraction (%):   ", 100.*live_time/real_time
if ( r_count_lamtrig > 0 ) then 
  print "Looker fraction (%): ", 100.*l_count_lamtrig/r_count_lamtrig
endif
print ""
print "-- Scalers:"
print "Target count (real time): ", ttarget_count_real, "	(", itarget_count_real, ")"
print "             (live time): ", ttarget_count_live, "	(", itarget_count_live, ")"
print "Beam Paddle  (real time): ", tscaler1[13], "	(", iscaler1[13], ")"
print "             (live time): ", tscaler2[13], "	(", iscaler2[13], ")"
print "-- Rates:"
print "Target rate  (real time): ", ttarget_rate_real, "	(", itarget_rate_real, ")"
print "             (live time): ", ttarget_rate_live, "	(", itarget_rate_live, ")"
print "Beam Paddle  (real time): ", trate1[13], "	(", irate1[13], ")"
print "             (live time): ", trate2[13], "	(", irate2[13], ")"
print ""
# ---------------------------------------------------------
zI1tmp = adcbuffer_mult_ig
zI2tmp = adcnotvalid_ig
repeat i from 1 to 3
  zI1tmp +=  adcbuffer_mult_l[i] + adcbuffer_mult_s[i] + tdcbuffer_mult[i]
  zI2tmp +=  adcnotvalid_l[i] + adcnotvalid_s[i] + tdcnotvalid[i]
endrepeat
if(zI1tmp > 0)
  print "Unexpected more than one buffer in:"
  print "   ADC_l 1:",adcbuffer_mult_l[1]," 2:",adcbuffer_mult_l[2]," 3:",adcbuffer_mult_l[3]
  print "   ADC_s 1:",adcbuffer_mult_s[1]," 2:",adcbuffer_mult_s[2]," 3:",adcbuffer_mult_s[3]
  print "   TDC   1:",tdcbuffer_mult[1]," 2:",tdcbuffer_mult[2]," 3:",tdcbuffer_mult[3] 
  print "   ADC_ig :",adcbuffer_mult_ig
endif
if(zI2tmp > 0)
  print "Unexpected not valid data in:"
  print "   ADC_l 1:",adcnotvalid_l[1]," 2:",adcnotvalid_l[2]," 3:",adcnotvalid_l[3]
  print "   ADC_s 1:",adcnotvalid_s[1]," 2:",adcnotvalid_s[2]," 3:",adcnotvalid_s[3]
  print "   TDC   1:",tdcnotvalid[1]," 2:",tdcnotvalid[2]," 3:",tdcnotvalid[3] 
  print "   ADC_ig :",adcnotvalid_ig
endif
# ---------------------------------------------------------
 
call print_run_nums(runs,"")

print ""
print "  Checking for pedestal shifts (greater than +-2 channels)..."
repeat i from 0 to 31
  call checkped(ped_sub_s_1[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_s_1[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_s_1[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_l_1[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_l_1[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_l_1[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_s_2[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_s_2[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_s_2[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_l_2[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_l_2[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_l_2[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_s_3[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_s_3[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_s_3[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_l_3[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_l_3[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_l_3[",i,"] pedestal shifted by ",pedshift endif
  call checkped(ped_sub_ig[i], l_count_pedestal, pedshift, peddiff)
  if(peddiff > 0) print "ped_sub_ig[",i,"] sum < l_count_pedestal by ",peddiff endif
  if(pedshift != 0) print "ped_sub_ig[",i,"] pedestal shifted by ",pedshift endif
endrepeat

######
## Generate dump files for this run

print ""
print "--> Generating dump files..."
print "" to "dump/run.info"
print "*** End of Run Status: ***" to "dump/run.info"
print "Events:" to "dump/run.info"
print "lamtrig      Reader: ", r_count_lamtrig,"	Looker: ",l_count_lamtrig to "dump/run.info"
print "neutron      Reader: ", r_count_neutron,"	Looker: ",l_count_neutron to "dump/run.info"
print "pedestal     Reader: ", r_count_pedestal,"	Looker: ",l_count_pedestal to "dump/run.info"
print "flasher      Reader: ", r_count_flasher,"	Looker: ",l_count_flasher to "dump/run.info"
print "monitor      Reader: ", r_count_monitor,"	Looker: ",l_count_monitor to "dump/run.info"
print "flux         Reader: ", r_count_flux,"	Looker: ",l_count_flux to "dump/run.info"
print "paddle       Reader: ", r_count_paddle,"	Looker: ",l_count_paddle to "dump/run.info"
print "scalerread   Reader: ", r_count_scaler,"	Looker: ",l_count_scaler to "dump/run.info"
print "" to "dump/run.info"
print "Real time (s):       ", real_time to "dump/run.info"
print "Live time (s):       ", live_time to "dump/run.info"
print "Live   fraction (%): ", 100.*live_time/real_time to "dump/run.info"
if ( r_count_lamtrig > 0 ) then 
  print "Looker fraction (%): ", 100.*l_count_lamtrig/r_count_lamtrig to "dump/run.info"
endif

## Done dumping files
#######
print "" to "/dev/null"

## Done dumping files
if(archive_dump == 1) then		# move dump files to archive
  print "--> Archiving dump files..."
  call stringcat(program_name, exp_dir, "/bin/dumpsave")
  print runno to program program_name
endif
#######

print ""
print "          ---- Completed run ", runno, " ----"
print "          Started on ", datestart
print "          Ended on   ", datestop
print "          Run time   ", (timestop - timestart)," sec."

print "" to "/dev/null"
# -------------------- end of endrun event

########################################
event ideal_windup:
########################################

#compute the solid angle for the detectors based on a geantino run
#Prints both to the screen and to solid_angle.txt
if(geantinos_emitted > 0) then
	print "Cell Solid Angles"
	print "Cell Solid Angles for Blowfish Cells" to "solid_angle.txt"
	print "Data gerated by Geant4 geantino and output by Lucid" to "solid_angle.txt"
	print "Cell, Solid Angle (srad), Error (srad)" to "solid_angle.txt"
	#zR4tmp is used to compute the average solid angle over all of the cells
	zR4tmp = 0
	zR3tmp = geantinos_emitted
	repeat i from 1 to 88
		zR4tmp += geantino_hits[i-1]
		zR1tmp = geantino_hits[i-1]/zR3tmp*4.0*3.14159265359
		zR2tmp = pow(geantino_hits[i-1],0.5)/zR3tmp*4.0*3.14159265359
		print " Cell ", i, "  ", zR1tmp, " +/- ", zR2tmp, " srad"
		print i," ", zR1tmp," ", zR2tmp to "solid_angle.txt"
	endrepeat
	zR1tmp = zR4tmp/zR3tmp*4.0*3.14159265359/88.0
	zR2tmp = pow(zR4tmp,0.5)/zR3tmp*4.0*3.14159265359/88.0
	print " Average  ", zR1tmp, " +/- ", zR2tmp, " srad"
endif

# -------------------- end of ideal_windup event
#========================================================================
# Add commands in this section
#========================================================================
########################################
command "Run Params":
########################################

print " "
print "Run Parameters from Control System"
call decode_caget(beam_param_l, 1024)
print " "

########################################
command "Clear":
########################################

print "-------- Clearing all histograms --------"

Looker_Histos = 0
raw_histograms  = 0
ped_histograms  = 0
scaler_group    = 0
#looker_counter = 0

# -------------------- end of Clear command --------------------

########################################
command "Reload Params":
########################################

print ""
print "-------- Reloading parameter files --------"
print "	--> blowfish.dat ..."
if Lucidloadvars("blowfish.dat") < 0
  print "*** ERROR READING 'blowfish.dat' ***"
endif

print "	--> psdparams.dat ..."
if Lucidloadvars("psdparams.dat") < 0
  print "*** ERROR READING 'psdparams.dat' ***"
endif

print "	--> tdcoffsets.dat ..."
if Lucidloadvars("tdc_offsets.dat") < 0
  print "*** ERROR READING 'tdc_offsets.dat' ***"
endif

print " ----> You probably want to clear the histos now..."
print ""

# -------------------- end of Reload cuts command --------------------

########################################
command "Scalers":
########################################
 
print "-------- Scalers command -------- [ Output:   average  (inst) ] --------"
print "Real time (s): ", real_time, "	Live time (s): ", live_time
if( ireal_time == 0 )
  ireal_time = 999999999.
endif
if( real_time > 0 ) 
  print "Live fraction (%): ", 100.*live_time/real_time, " (", 100.*ilive_time/ireal_time, ")"
endif
print " "
print "                Uninhibited		Inhibited"
print "Beam Paddle   : ", tscaler1[13], "	(", iscaler1[13], ")	", tscaler2[13], "	(", iscaler2[13], ")"
print "ADC gates     : ", tscaler1[3], "	(", iscaler1[3], ")	"
print "TDC start     : ", tscaler1[4], "	(", iscaler1[4], ")	"
print "Inhibits      : ", tscaler1[25], "	(", iscaler1[25], ")	"
print "Triggers      : ", tscaler1[24], "	(", iscaler1[24], ")	"
print "X * N-OR      : ", tscaler1[1], "	(", iscaler1[1], ")	"
print "N trig        : ", tscaler1[2], "	(", iscaler1[2], ")	"
print "X trig        : ", tscaler1[5], "	(", iscaler1[5], ")	"
#print "Bunch         : ", tscaler1[8], "	(", iscaler1[8], ")	"
#print "Bunch retimd  : ", tscaler1[22], "	(", iscaler1[22], ")	", tscaler2[22], "	(", iscaler2[22], ")"
print "Flux-trig     : ", tscaler1[10],"	(", iscaler1[10],")	", tscaler2[10], "	(", iscaler2[10], ")"
print " "
print "Neutron cells (uninhibited)"
call print_array_int(1, 88, tcell_scaler, "")
# -------------------- end of Scalers command


########################################
command "Rates":
########################################
 
print ""
print "-------- Rates command (Hz) --------"
print "Real time (s): ", real_time, "	Live time (s): ", live_time
if( real_time > 0 ) 
  print "Live fraction (%): ", (live_time/real_time)*100, " (", (ilive_time/ireal_time)*100, ")"
endif
 
print " "
print "[ Output:   average  (inst) ] -------- "
print "                Uninhibited         Inhibited"
print "Beam Paddle   : ", trate1[13], "	(", irate1[13], ")	", trate2[13], "	(", irate2[13], ")"
print "ADC gates     : ", trate1[3], "	(", irate1[3], ")	", trate2[3], "	(", irate2[3], ")"
print "TDC start     : ", trate1[4], "	(", irate1[4], ")	", trate2[4], "	(", irate2[4], ")"
print "Inhibits      : ", trate1[25], "	(", irate1[25], ")	", trate2[25], "	(", irate2[25], ")"
#print "Bunch pickoff : ", trate1[8], "	(", irate1[8], ")	", trate2[8], "	(", irate2[8], ")"
#print "Bunch retimed : ", trate1[22], "	(", irate1[22], ")	", trate2[22], "	(", irate2[22], ")"
print "N-OR          : ", trate1[1], "	(", irate1[1], ")	", trate2[1], "	(", irate2[1], ")"
print "N trig        : ", trate1[2], "	(", irate1[2], ")	", trate2[2], "	(", irate2[2], ")"
print "Flux-raw      : ", trate1[7],"	(", irate1[7],")	", trate2[7], "	(", irate2[7], ")"
print "Flux-trig     : ", trate1[10],"	(", irate1[10],")	", trate2[10], "	(", irate2[10], ")"

print "N-trig        : ", trate1[2],"	(", irate1[2],")	", trate2[2], "	(", irate2[2], ")"
print "P-trig        : ", trate1[11],"	(", irate1[11],")	", trate2[11], "	(", irate2[11], ")"
print "N-win         : ", trate1[18],"	(", irate1[18],")	", trate2[18], "	(", irate2[18], ")"
print "G-win         : ", trate1[19],"	(", irate1[19],")	", trate2[19], "	(", irate2[19], ")"
#print "Master trigger: ", trate1[24],"	(", irate1[24],")	", trate2[24], "	(", irate2[24], ")"

print " "
print "Neutron cells (average)"
call print_array_real(1, 88, tcell_rate, "")
print " "
print "Neutron cells (inst)"
call print_array_real(1, 88, icell_rate, "")
# -------------------- end of Rates command

########################################
command "Status":
########################################
if( ireal_time == 0 )
  ireal_time = 999999999.
endif
if( real_time == 0 )
  real_time = 999999999.
endif

print ""
print "-------- Looker Status: --------"
print "Real time (s)     : ", real_time
print "Live time (s)     : ", live_time
print "Live fraction (%) : ", (live_time/real_time)*100, " (", (ilive_time/ireal_time)*100, ")"
if ( r_count_lamtrig > 0 ) then 
  print ""
  print "Looker fraction : ", 100.*l_count_lamtrig/r_count_lamtrig
endif
print ""
print "  Events    (Looker   Reader   Reader-Rate [Hz])"
print "neutron       L= ", l_count_neutron, " R= ", r_count_neutron,
	" Rate= ",r_count_neutron/real_time
print "gamma_enabled L= ", l_count_gamma_enable, "  R= ", r_count_gamma_enable,
	" Rate= ",r_count_gamma_enable/real_time
print "pedestal      L= ", l_count_pedestal, "  R= ", r_count_pedestal,
	" Rate= ",r_count_pedestal/real_time
print "flasher       L= ", l_count_flasher, " R= ", r_count_flasher,
	" Rate= ",r_count_flasher/real_time
print "monitor       L= ", l_count_monitor, " R= ", r_count_monitor,
	" Rate= ",r_count_monitor/real_time
print "flux          L= ", l_count_flux, "  R= ", r_count_flux,
	" Rate= ",r_count_flux/real_time
print "paddle        L= ", l_count_paddle, "  R= ", r_count_paddle,
	" Rate= ",r_count_paddle/real_time

# ---------------------------------------------------------
zI1tmp = adcbuffer_mult_ig
zI2tmp = adcnotvalid_ig
repeat i from 1 to 3
  zI1tmp +=  adcbuffer_mult_l[i] + adcbuffer_mult_s[i] + tdcbuffer_mult[i]
  zI2tmp +=  adcnotvalid_l[i] + adcnotvalid_s[i] + tdcnotvalid[i]
endrepeat
if(zI1tmp > 0)
  print "Unexpected more than one buffer in:"
  print "   ADC_l 1:",adcbuffer_mult_l[1]," 2:",adcbuffer_mult_l[2]," 3:",adcbuffer_mult_l[3]
  print "   ADC_s 1:",adcbuffer_mult_s[1]," 2:",adcbuffer_mult_s[2]," 3:",adcbuffer_mult_s[3]
  print "   TDC   1:",tdcbuffer_mult[1]," 2:",tdcbuffer_mult[2]," 3:",tdcbuffer_mult[3] 
  print "   ADC_ig :",adcbuffer_mult_ig
endif
if(zI2tmp > 0)
  print "Unexpected not valid data in:"
  print "   ADC_l 1:",adcnotvalid_l[1]," 2:",adcnotvalid_l[2]," 3:",adcnotvalid_l[3]
  print "   ADC_s 1:",adcnotvalid_s[1]," 2:",adcnotvalid_s[2]," 3:",adcnotvalid_s[3]
  print "   TDC   1:",tdcnotvalid[1]," 2:",tdcnotvalid[2]," 3:",tdcnotvalid[3] 
  print "   ADC_ig :",adcnotvalid_ig
endif
# ---------------------------------------------------------
print ""
print "-- Scalers:"
#print "Target count (real time): ", ttarget_count_real, "	(", itarget_count_real, ")"
#print "             (live time): ", ttarget_count_live, "	(", itarget_count_live, ")"
print "Beam Paddle  (real time): ", tscaler1[13], "	(", iscaler1[13], ")"
print "             (live time): ", tscaler2[13], "	(", iscaler2[13], ")"
print "-- Rates:"
#print "Target rate  (real time): ", ttarget_rate_real, "	(", itarget_rate_real, ")"
#print "             (live time): ", ttarget_rate_live, "	(", itarget_rate_live, ")"
print "Beam Paddle  (real time): ", trate1[13], "	(", irate1[13], ")"
print "             (live time): ", trate2[13], "	(", irate2[13], ")"
print ""
# -------------------- end of Status command --------------------

########################################
command "Calc Peds":
########################################
print ""
print "---------------  Calculating pedestals... ---------------"
repeat i from 0 to 31
  call calcent(ped_raw_l_1[i], 300, ped_cent_l_1[i], ped_sigma_l_1[i], 
               ped_error_l_1[i], ped_num_l_1[i], max_chan_l_1, max_cnt_l_1)
  call calcent(ped_raw_s_1[i], 300, ped_cent_s_1[i], ped_sigma_s_1[i], 
               ped_error_s_1[i], ped_num_s_1[i], max_chan_s_1, max_cnt_s_1)
  call calcent(ped_raw_l_2[i], 300, ped_cent_l_2[i], ped_sigma_l_2[i], 
               ped_error_l_2[i], ped_num_l_2[i], max_chan_l_2, max_cnt_l_2)
  call calcent(ped_raw_s_2[i], 300, ped_cent_s_2[i], ped_sigma_s_2[i], 
               ped_error_s_2[i], ped_num_s_2[i], max_chan_s_2, max_cnt_s_2)
  call calcent(ped_raw_l_3[i], 300, ped_cent_l_3[i], ped_sigma_l_3[i], 
               ped_error_l_3[i], ped_num_l_3[i], max_chan_l_3, max_cnt_l_3)
  call calcent(ped_raw_s_3[i], 300, ped_cent_s_3[i], ped_sigma_s_3[i], 
               ped_error_s_3[i], ped_num_s_3[i], max_chan_s_3, max_cnt_s_3)
  call calcent(ped_raw_ig[i], 300, ped_cent_ig[i], ped_sigma_ig[i], 
               ped_error_ig[i], ped_num_ig[i], max_chan_ig, max_cnt_ig)
endrepeat
call stringcat(ped_dir, exp_dir, "/param/Ped")
call writeped(ped_dir,"pedestals.adc.long.1",num_runs, runs, 32,
	ped_cent_l_1, ped_sigma_l_1, ped_error_l_1, ped_num_l_1, ped_current_l_1)
call writeped(ped_dir,"pedestals.adc.short.1",num_runs, runs, 32,
	ped_cent_s_1, ped_sigma_s_1, ped_error_s_1, ped_num_s_1, ped_current_s_1)
call writeped(ped_dir,"pedestals.adc.long.2",num_runs, runs, 32,
	ped_cent_l_2, ped_sigma_l_2, ped_error_l_2, ped_num_l_2, ped_current_l_2)
call writeped(ped_dir,"pedestals.adc.short.2",num_runs, runs, 32,
	ped_cent_s_2, ped_sigma_s_2, ped_error_s_2, ped_num_s_2, ped_current_s_2)
call writeped(ped_dir,"pedestals.adc.long.3",num_runs, runs, 32,
	ped_cent_l_3, ped_sigma_l_3, ped_error_l_3, ped_num_l_3, ped_current_l_3)
call writeped(ped_dir,"pedestals.adc.short.3",num_runs, runs, 32,
	ped_cent_s_3, ped_sigma_s_3, ped_error_s_3, ped_num_s_3, ped_current_s_3)
call writeped(ped_dir,"pedestals.adc.ig",num_runs, runs, 32,
	ped_cent_ig, ped_sigma_ig, ped_error_ig, ped_num_ig, ped_current_ig)

#repeat i from 0 to 11
#  call calcent(ped_raw_flux[i], 300, ped_cent_flux[i], ped_sigma_flux[i], 
#               ped_error_flux[i], ped_num_flux[i], max_chan_flux, max_cnt_flux)
#endrepeat
#  call calcent(ped_raw_targ_s, 300, ped_cent_targ_s, ped_sigma_targ_s, 
#               ped_error_targ_s, ped_num_targ_s, max_chan_targ_s, max_cnt_targ_s)
#  call calcent(ped_raw_targ_l, 300, ped_cent_targ_l, ped_sigma_targ_l, 
#               ped_error_targ_l, ped_num_targ_s, max_chan_targ_l, max_cnt_targ_l)
#call writeped(ped_dir,"pedestals.targ.short",num_runs, runs, 1,
#	ped_cent_targ_s, ped_sigma_targ_s, ped_error_targ_s, ped_num_targ_s, ped_current_targ_s)
#call writeped(ped_dir,"pedestals.targ.long",num_runs, runs, 1,
#	ped_cent_targ_l, ped_sigma_targ_l, ped_error_targ_l, ped_num_targ_l, ped_current_targ_l)
#call writeped(ped_dir,"pedestals.flux",num_runs, runs, 2,
#	ped_cent_flux, ped_sigma_flux, ped_error_flux, ped_num_flux, ped_current_flux)

print "Pedestal files written for run number ",runno
print ""
# -------------------- end of Calc Peds command --------------------


########################################
command "Flasher Stats":
########################################

print "  *** Fitting flasher monitor adc's ***"
repeat i from 1 to 6
	call fitsource(flash_sourcemon[i], 1024, 0, 4, 100, 3500,
		source_peak[i], source_peakerr[i],
		source_stdev[i], source_stdeverr[i])
endrepeat
repeat i from 1 to 6
	call fitflash(flash_monitor[i], 4096, 0, 1, 100, 3500,
		monitor_peak[i], monitor_peakerr[i],
		monitor_stdev[i], monitor_stdeverr[i])
endrepeat
	call fitflash(flash_volt, 4096, 0, 1, 100, 3500,
		volt_peak, volt_peakerr,
		volt_stdev, volt_stdeverr)
repeat i from 1 to 88
	call fitflash(flash_long[i], 1024, 0, 4, 100, 3500,
		flash_long_peak[i], flash_long_peakerr[i],
		flash_long_stdev[i], flash_long_stdeverr[i])
	call fitflash(flash_short[i], 1024, 0, 4, 100, 3500,
		flash_short_peak[i], flash_short_peakerr[i],
		flash_short_stdev[i], flash_short_stdeverr[i])
endrepeat
call make_filename(zFilename, exp_dir, "/param/Flash/", runno, "flashdata")

print "\43 Flasher and Flasher Monitor data for run ", runno to zFilename
print "\43" to zFilename
print "\43 Source peak positions:" to zFilename
print "\43" to zFilename
print "\43 Num   Peak    error      Stdev    error" to zFilename
repeat i from 1 to 6
	print i,"  ",source_peak[i],"  ",source_peakerr[i],"  ",
		source_stdev[i],"  ",source_stdeverr[i] to zFilename
endrepeat
#------------------------
print "\43" to zFilename
print "\43 Flash Monitor peak positions:" to zFilename
print "\43" to zFilename
print "\43 Num   Peak    error      Stdev    error" to zFilename
repeat i from 1 to 6
	print i,"  ",monitor_peak[i],"  ",monitor_peakerr[i],"  ",
		monitor_stdev[i],"  ",monitor_stdeverr[i] to zFilename
endrepeat
#------------------------
print "\43" to zFilename
print "\43 Flasher Voltage monitor peak position:" to zFilename
print "\43" to zFilename
print "\43 Num   Peak    error      Stdev    error" to zFilename
	print "   ",volt_peak,"  ",volt_peakerr,"  ",
		volt_stdev,"  ",volt_stdeverr to zFilename
#------------------------
print "\43" to zFilename
print "\43 Flash Cell long gate peak positions:" to zFilename
print "\43" to zFilename
print "\43 Num   Peak    error      Stdev    error" to zFilename
repeat i from 1 to 88
	print i,"  ",flash_long_peak[i],"  ",flash_long_peakerr[i],"  ",
		flash_long_stdev[i],"  ",flash_long_stdeverr[i] to zFilename
endrepeat
#------------------------
print "\43" to zFilename
print "\43 Flash Cell short gate peak positions:" to zFilename
print "\43" to zFilename
print "\43 Num   Peak    error      Stdev    error" to zFilename
repeat i from 1 to 88
	print i,"  ",flash_short_peak[i],"  ",flash_short_peakerr[i],"  ",
		flash_short_stdev[i],"  ",flash_short_stdeverr[i] to zFilename
endrepeat
#------------------------
print "" to "/dev/null"

print "Flasher and Flasher Monitor data for run ", runno
print "      written to file: ", zFilename

########################################
command "TDC offsets":
########################################
print "--> Build new TDC offsets file..."
print "    (naive search for maximum between:", gamma_peak_lo,
      " -- ", gamma_peak_hi, ")"
call make_filename(zFilename, exp_dir, "/param/TDC_offsets/", runno, "tdc_offsets.dat")
print "    Output will be in: ", zFilename

print "\43 TDC offsets from run ",runno to zFilename
print "\43"
print "tdc_offset[0] = 0" to zFilename
repeat i from 1 to 88
  zA4096tmp = raw_tdc_gamma[i]
  zI1tmp = gamma_peak_lo
  repeat j from gamma_peak_lo to gamma_peak_hi	# search for maximum
    if(zA4096tmp[j] .ge. zA4096tmp[zI1tmp]) then
      zI1tmp = j
    endif
  endrepeat
  if(zI1tmp == gamma_peak_hi) then zI1tmp = 0 endif
  tdc_offset[i] = zI1tmp + 1	# adjust current tdc_offset
  # + 1 is because raw_tdc_gamma is defined from 1 to 4095
  print "tdc_offset[", i, "] = ", tdc_offset[i] to zFilename
endrepeat
  print "--> New TDC offsets file in ", zFilename
  print "    Edit the rundata file to set the future defaults."
# -------------------- end of TDC offsets ----------------------

########################################
command "PSD rot":
########################################
# Compute new PSD rotation values
print ""
print "--------------- Determining new PSD parameters... ---------------"
print ""

call make_filename(zFilename, exp_dir, "/param/PSD/", runno, "psd_params.dat")

print "  --> Writing to file: ", zFilename
print ""

zI1tmp = (PSD_loband_hi - PSD_loband_lo) / 2 + PSD_loband_lo
zI2tmp = (PSD_hiband_hi - PSD_hiband_lo) / 2 + PSD_hiband_lo
print "  Target band location:"
print "     Base of 'V' (x, y):	(", zI1tmp, ",	", psd_base_ch, ")"
print "     Slope of gamma arm:	", psd_m_targ
print ""

smooth  = 80			# smoothing parameter
arrsize = 300			# number of elements in array
arr_offset = -200		# zero offset for histogram
zI3tmp  = 1000			# scaling factor
maxDiff = 100			# warn if peak shifts more than this many ch's

print "\43 Target band location:" to zFilename
print "\43    Base of 'V' (x, y):	(", zI1tmp, ",	", psd_base_ch, ")" to zFilename
print "\43    Slope of gamma arm:	", psd_m_targ to zFilename
print "\43 Upper band cut:	",PSD_hiband_lo,"	",PSD_hiband_hi to zFilename
print "\43 Lower band cut:	",PSD_loband_lo,"	",PSD_loband_hi to zFilename
print "\43" to zFilename
print "\43 Smoothing param = ", smooth to zFilename
print "\43" to zFilename

repeat i from 0 to 88
  ## Low band cut
  zA1024tmp = psd_loband[i]
  call smoother(zA1024tmp,arrsize, smooth, zI3tmp)
  psd_loband_sm[i] = zA1024tmp
  call findMax(zA1024tmp, arrsize, peak0)
  peak0 += arr_offset
  if(i == 0) then # store the average peak locations for future sanity checks
    loband_ave = peak0
  else			# do the sanity check
    zI1tmp = loband_ave - peak0
    if( zI1tmp > maxDiff || zI1tmp < -maxDiff ) then
      print "  !!-> Cell[",i,",] low band location shifted by ", zI1tmp
    endif
  endif

  ## High band cut
  zA1024tmp = psd_hiband[i]
  call smoother(zA1024tmp,arrsize, smooth, zI3tmp)
  psd_hiband_sm[i] = zA1024tmp
  call findMax(zA1024tmp, arrsize, peak1)
  peak1 += arr_offset
  if(i == 0) then # store the average peak locations for future sanity checks
    hiband_ave = peak1
  else			# do the sanity check
    zI1tmp = hiband_ave - peak1
    if( zI1tmp > maxDiff || zI1tmp < -maxDiff ) then
      print "  !!-> Cell[",i,",] high band location shifted by ", zI1tmp
    endif
  endif

  ## Compute the new shear value from peak0, peak1
  #void calc_psd_rotation(int *top_ch, int *base_ch,
  #   int *peak0, int *ph0, int *peak1, int *ph1,
  #   int *offset, float *rot)
  psd_off_copy = psd_off[i]
  rot_var_copy = rot_var[i]
  zI1tmp = (PSD_loband_hi - PSD_loband_lo) / 2 + PSD_loband_lo
  zI2tmp = (PSD_hiband_hi - PSD_hiband_lo) / 2 + PSD_hiband_lo
  call calc_psd_rotation(psd_m_targ, psd_base_ch,
	peak0, zI1tmp, peak1, zI2tmp,
	psd_off_copy, rot_var_copy)

  print "psd_off[",i,"] = ", psd_off_copy to zFilename
  print "rot_var[",i,"] = ", rot_var_copy to zFilename

#print " --> Cell ",i
#print "  peak0 = ", peak0, "	peak1 = ", peak1
#print "  Old: psd_off = ", psd_off[i]  ,"	rot_var = ", rot_var[i]
#print "  New: psd_off = ", psd_off_copy,"	rot_var = ", rot_var_copy
#print ""

endrepeat

# -------------------- end of PSD rotation command --------------------

########################################
command "Neut Rate":
########################################

print ""
print "---------------- Neutron Rates ---------------- "
print ""
tdc_norm = 1.*(tdc_cut_hi-tdc_cut_lo)/(tdc_rand_hi-tdc_rand_lo)

repeat i from 1 to 88
  F_neut_rate[i-1] = 1000.*(F_neut_count[i]-tdc_norm*rand_count[i])/real_time
  #if(F_neut_rate[i-1] < 0) then
  #  print " Fnc: ", F_neut_count[i], "  randc: ", rand_count[i],  "  time: ", real_time
  #endif 
endrepeat

print "Total neutron rate over array: ", $F_neut_rate/1000, " Hz"
print ""
print "Cell neutron rates * 1000 [mHz]"
print "    (N TDC randoms normalization: ", tdc_norm, ")"
print " "
zFilename = ""
call print_array_real(0, 87, F_neut_rate, zFilename)

# -------------------- end of Neutron Rates command


########################################
command "Asym":
########################################
print ""
print "---------------- Calculating Asymetries ----------------"
print ""

F_neut_sub_2d  = 0
F_neut_sub_arm = 0
zA1024tmp      = 0

# Calculate asymetries as a function of theta
tdc_norm = 1.*(tdc_cut_hi-tdc_cut_lo)/(tdc_rand_hi-tdc_rand_lo)
print "N TDC randoms normalization: ", tdc_norm

print ""
print "       Angle			Planes 1/3		Planes 2/4"
repeat i from 0 to 10
  repeat j from 0 to 3 		# sum neuts-backround in 4 planes
    icell = 8*i + j + 1
    neuts[j] = F_neut_count[icell] + F_neut_count[icell+4]
    rand[j]  = rand_count[icell]   + rand_count[icell+4]
    diff_neut[j] = neuts[j] - tdc_norm*rand[j]
    err_diff_sq[j] = neuts[j] + rand[j]*tdc_norm**2   # sum of squared errors
#print "neuts/rand/diff = ", neuts[j], "  ",rand[j], "  ", diff_neut[j]

    zI1tmp = neuts[j] - tdc_norm*rand[j]
    repeat zI2tmp from 1 to zI1tmp		# terrible hack
      increment F_neut_sub_2d[icell/49]     using col[icell  ], row[icell  ]
      increment F_neut_sub_2d[(icell+4)/49] using col[icell+4], row[icell+4]
    endrepeat
    # Set-up the background subtracted neutrons per arm
    iarm=icell%8
    if( iarm.gt.0)
      zA1024tmp[iarm]  +=F_neut_count[icell] - tdc_norm*rand_count[icell]
    else 
      if( iarm.eq.0 )
        zA1024tmp[iarm]+=F_neut_count[icell] - tdc_norm*rand_count[icell]
      endif
    endif
     iarm=(icell+4)%8
    if( iarm.gt.0)
      zA1024tmp[iarm]  +=F_neut_count[icell+4] - tdc_norm*rand_count[icell+4]
    else 
      if( iarm.eq.0 )
        zA1024tmp[iarm]+=F_neut_count[icell+4] - tdc_norm*rand_count[icell+4]
      endif
    endif
  endrepeat

  repeat j from 0 to 1  	# one asym is H-V/H+V, the other is for phi+45
    # See Leo p. 103 for discussion on errors
    asym[j]  = 1. * (diff_neut[j] - diff_neut[j+2]) / (diff_neut[j] + diff_neut[j+2])
    err[j]   = 2./(diff_neut[j] + diff_neut[j+2])**2 * 
      (diff_neut[j]**2 *err_diff_sq[j] + diff_neut[j+2]**2 *err_diff_sq[j+2])**0.5
  endrepeat
  print "Theta = ", 157.5 - i*13.5, " (ring ", i+1, "):	",
	asym[0], " [", err[0], "],	", asym[1], " [", err[1], "]"
#  print "  Planes 1/3:	", asym[0], " [", err[0], "]", 
#	"  Planes 2/4:	", asym[1], " [", err[1], "]"

  ## build an asymetry "histogram"
  # get absolute value of asym[] since we can't have negative numbers of counts in a bin (I tested this)
  if( asym[0].lt.0 ) then
    asym[0] = 0-asym[0]
  endif
  if( asym[1].lt.0 ) then
    asym[1] = 0-asym[1]
  endif
  tmparr0[i] = 100 * asym[0]
  tmparr1[i] = 100 * asym[1]
  # zero out temp asyms if err is bigger than asym (so no negitive numbers in a bin)
  if(asym[0].le.err[0]) then
    tmparr0[i] = 0
  endif
  if(asym[1].le.err[1]) then
    tmparr1[i] = 0
  endif
endrepeat

F_neut_sub_arm = zA1024tmp

asym_hist[0]    = tmparr0
asym_hist[1]    = tmparr1
print ""


#-------------- end of Asym event ------------------------
