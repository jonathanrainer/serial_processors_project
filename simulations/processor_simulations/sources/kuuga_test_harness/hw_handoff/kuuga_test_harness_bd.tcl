
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
  set CLK [ create_bd_port -dir I -type clk CLK ]
  set_property -dict [ list \
CONFIG.FREQ_HZ {100000000} \
 ] $CLK
  set RST [ create_bd_port -dir I -type rst RST ]
  set_property -dict [ list \
CONFIG.POLARITY {ACTIVE_HIGH} \
 ] $RST
  set done [ create_bd_port -dir O done ]
  set input_location [ create_bd_port -dir I -from 31 -to 0 -type data input_location ]
  set result [ create_bd_port -dir O -from 31 -to 0 -type data result ]
  set start [ create_bd_port -dir I start ]

  # Create instance: kuuga_0, and set properties
  set kuuga_0 [ create_bd_cell -type ip -vlnv xilinx.com:hls:kuuga:1.0 kuuga_0 ]

  # Create port connections
  connect_bd_net -net CLK_1 [get_bd_ports CLK] [get_bd_pins kuuga_0/ap_clk]
  connect_bd_net -net RST_1 [get_bd_ports RST] [get_bd_pins kuuga_0/ap_rst]
  connect_bd_net -net input_location_1 [get_bd_ports input_location] [get_bd_pins kuuga_0/output_loc]
  connect_bd_net -net kuuga_0_ap_done [get_bd_ports done] [get_bd_pins kuuga_0/ap_done]
  connect_bd_net -net kuuga_0_ap_return [get_bd_ports result] [get_bd_pins kuuga_0/ap_return]
  connect_bd_net -net start_1 [get_bd_ports start] [get_bd_pins kuuga_0/ap_start]

  # Create address segments

  # Perform GUI Layout
  regenerate_bd_layout -layout_string {
   guistr: "# # String gsaved with Nlview 6.5.5  2015-06-26 bk=1.3371 VDI=38 GEI=35 GUI=JA:1.8
#  -string -flagsOSRD
preplace port start -pg 1 -y 90 -defaultsOSRD
preplace port RST -pg 1 -y 210 -defaultsOSRD
preplace port CLK -pg 1 -y 190 -defaultsOSRD
preplace port done -pg 1 -y 40 -defaultsOSRD
preplace portBus result -pg 1 -y 140 -defaultsOSRD
preplace portBus input_location -pg 1 -y 230 -defaultsOSRD
preplace inst kuuga_0 -pg 1 -lvl 1 -y 160 -defaultsOSRD
preplace netloc start_1 1 0 1 NJ
preplace netloc CLK_1 1 0 1 N
preplace netloc input_location_1 1 0 1 NJ
preplace netloc kuuga_0_ap_return 1 1 1 NJ
preplace netloc kuuga_0_ap_done 1 0 2 30 40 NJ
preplace netloc RST_1 1 0 1 N
levelinfo -pg 1 0 400 590 -top 20 -bot 280
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


