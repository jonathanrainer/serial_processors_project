
################################################################
# This is a generated script based on design: kuuga_test_harness
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2015.4
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   puts "ERROR: This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source kuuga_test_harness_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7vx485tffg1761-2
#    set_property BOARD_PART xilinx.com:vc707:part0:1.2 [current_project]

# CHECKING IF PROJECT EXISTS
if { [get_projects -quiet] eq "" } {
   puts "ERROR: Please open or create a project!"
   return 1
}



# CHANGE DESIGN NAME HERE
set design_name kuuga_test_harness

# This script was generated for a remote BD.
set str_bd_folder /usr/userfs/j/jr776/w2k/serial_processors_project/simulations/processor_simulations/sources
set str_bd_filepath ${str_bd_folder}/${design_name}/${design_name}.bd

# Check if remote design exists on disk
if { [file exists $str_bd_filepath ] == 1 } {
   puts "ERROR: The remote BD file path <$str_bd_filepath> already exists!\n"

   puts "INFO: Please modify the variable <str_bd_folder> to another path or modify the variable <design_name>."

   return 1
}

# Check if design exists in memory
set list_existing_designs [get_bd_designs -quiet $design_name]
if { $list_existing_designs ne "" } {
   puts "ERROR: The design <$design_name> already exists in this project!"
   puts "ERROR: Will not create the remote BD <$design_name> at the folder <$str_bd_folder>.\n"

   puts "INFO: Please modify the variable <design_name>."

   return 1
}

# Check if design exists on disk within project
set list_existing_designs [get_files */${design_name}.bd]
if { $list_existing_designs ne "" } {
   puts "ERROR: The design <$design_name> already exists in this project at location:"
   puts "   $list_existing_designs"
   puts "ERROR: Will not create the remote BD <$design_name> at the folder <$str_bd_folder>.\n"

   puts "INFO: Please modify the variable <design_name>."

   return 1
}

# Now can create the remote BD
create_bd_design -dir $str_bd_folder $design_name
current_bd_design $design_name

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set Agito_Done [ create_bd_port -dir O -type data Agito_Done ]
  set Agito_Input_Loc [ create_bd_port -dir I -from 31 -to 0 -type data Agito_Input_Loc ]
  set Agito_Result [ create_bd_port -dir O -from 31 -to 0 -type data Agito_Result ]
  set Kuuga_CLK [ create_bd_port -dir I -type clk Kuuga_CLK ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {100000000} \
 ] $Kuuga_CLK
  set Kuuga_Input_Loc [ create_bd_port -dir I -from 31 -to 0 -type data Kuuga_Input_Loc ]
  set Kuuga_RST [ create_bd_port -dir I -type rst Kuuga_RST ]
  set_property -dict [ list \
CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $Kuuga_RST
  set Kuuga_Result [ create_bd_port -dir O -from 31 -to 0 -type data Kuuga_Result ]
  set Kuuga_done [ create_bd_port -dir O Kuuga_done ]
  set start [ create_bd_port -dir I start ]

  # Create instance: agito_0, and set properties
  set agito_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:agito:1.0 agito_0 ]

  # Create instance: clk_gen_0, and set properties
  set clk_gen_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_gen:1.0 clk_gen_0 ]
  set_property -dict [ list \
CONFIG.INITIAL_RESET_CLOCK_CYCLES {250} \
CONFIG.RESET_POLARITY {ACTIVE_HIGH} \
 ] $clk_gen_0

  # Create instance: kuuga_0, and set properties
  set kuuga_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:kuuga:1.0 kuuga_0 ]

  # Create port connections
  connect_bd_net -net Agito_Input_Loc_1 [get_bd_ports Agito_Input_Loc] [get_bd_pins agito_0/output_loc]
  connect_bd_net -net CLK_1 [get_bd_ports Kuuga_CLK] [get_bd_pins kuuga_0/ap_clk]
  connect_bd_net -net RST_1 [get_bd_ports Kuuga_RST] [get_bd_pins kuuga_0/ap_rst]
  connect_bd_net -net agito_0_ap_done [get_bd_ports Agito_Done] [get_bd_pins agito_0/ap_done]
  connect_bd_net -net agito_0_ap_return [get_bd_ports Agito_Result] [get_bd_pins agito_0/ap_return]
  connect_bd_net -net clk_gen_0_clk [get_bd_pins agito_0/ap_clk] [get_bd_pins clk_gen_0/clk]
  connect_bd_net -net clk_gen_0_sync_rst [get_bd_pins agito_0/ap_rst] [get_bd_pins clk_gen_0/sync_rst]
  connect_bd_net -net input_location_1 [get_bd_ports Kuuga_Input_Loc] [get_bd_pins kuuga_0/output_loc]
  connect_bd_net -net kuuga_0_ap_done [get_bd_ports Kuuga_done] [get_bd_pins kuuga_0/ap_done]
  connect_bd_net -net kuuga_0_ap_return [get_bd_ports Kuuga_Result] [get_bd_pins kuuga_0/ap_return]
  connect_bd_net -net start_1 [get_bd_ports start] [get_bd_pins agito_0/ap_start] [get_bd_pins kuuga_0/ap_start]

  # Create address segments

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.5.5  2015-06-26 bk=1.3371 VDI=38 GEI=35 GUI=JA:1.8
#  -string -flagsOSRD
preplace port Agito_Done -pg 1 -y 280 -defaultsOSRD
preplace port Kuuga_done -pg 1 -y 20 -defaultsOSRD
preplace port Agito_CLK -pg 1 -y 400 -defaultsOSRD
preplace port Kuuga_CLK -pg 1 -y 170 -defaultsOSRD
preplace port Kuuga_RST -pg 1 -y 190 -defaultsOSRD
preplace port start -pg 1 -y 90 -defaultsOSRD
preplace port Agito_RST -pg 1 -y 420 -defaultsOSRD
preplace portBus Kuuga_Result -pg 1 -y 140 -defaultsOSRD
preplace portBus Agito_Result -pg 1 -y 320 -defaultsOSRD
preplace portBus Agito_Input_Loc -pg 1 -y 310 -defaultsOSRD
preplace portBus Kuuga_Input_Loc -pg 1 -y 210 -defaultsOSRD
preplace inst kuuga_0 -pg 1 -lvl 1 -y 130 -defaultsOSRD
preplace inst agito_0 -pg 1 -lvl 1 -y 370 -defaultsOSRD
preplace netloc start_1 1 0 1 30
preplace netloc CLK_1 1 0 1 NJ
preplace netloc input_location_1 1 0 1 20
preplace netloc Agito_CLK_1 1 0 1 NJ
preplace netloc agito_0_ap_return 1 1 1 380
preplace netloc kuuga_0_ap_return 1 1 1 NJ
preplace netloc kuuga_0_ap_done 1 0 2 40 20 NJ
preplace netloc agito_0_ap_done 1 0 2 40 270 NJ
preplace netloc Agito_RST_1 1 0 1 NJ
preplace netloc Agito_Input_Loc_1 1 0 1 20
preplace netloc RST_1 1 0 1 NJ
levelinfo -pg 1 -20 210 400 -top 0 -bot 490
",
}

  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


