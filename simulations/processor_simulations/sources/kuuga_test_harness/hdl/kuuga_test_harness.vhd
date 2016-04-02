--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.4 (lin64) Build 1412921 Wed Nov 18 09:44:32 MST 2015
--Date        : Wed Mar 30 17:30:47 2016
--Host        : csteach0 running 64-bit Ubuntu 14.04.4 LTS
--Command     : generate_target kuuga_test_harness.bd
--Design      : kuuga_test_harness
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity kuuga_test_harness is
  port (
    Agito_Done : out STD_LOGIC;
    Agito_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Agito_Result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_CLK : in STD_LOGIC;
    Kuuga_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_RST : in STD_LOGIC;
    Kuuga_Result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_done : out STD_LOGIC;
    start : in STD_LOGIC
  );
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of kuuga_test_harness : entity is "kuuga_test_harness,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=kuuga_test_harness,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=3,numReposBlks=3,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,synth_mode=Global}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of kuuga_test_harness : entity is "kuuga_test_harness.hwdef";
end kuuga_test_harness;

architecture STRUCTURE of kuuga_test_harness is
  component kuuga_test_harness_kuuga_0_0 is
  port (
    ap_clk : in STD_LOGIC;
    ap_rst : in STD_LOGIC;
    ap_start : in STD_LOGIC;
    ap_done : out STD_LOGIC;
    ap_idle : out STD_LOGIC;
    ap_ready : out STD_LOGIC;
    ap_return : out STD_LOGIC_VECTOR ( 31 downto 0 );
    output_loc : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  end component kuuga_test_harness_kuuga_0_0;
  component kuuga_test_harness_agito_0_0 is
  port (
    ap_clk : in STD_LOGIC;
    ap_rst : in STD_LOGIC;
    ap_start : in STD_LOGIC;
    ap_done : out STD_LOGIC;
    ap_idle : out STD_LOGIC;
    ap_ready : out STD_LOGIC;
    ap_return : out STD_LOGIC_VECTOR ( 31 downto 0 );
    output_loc : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  end component kuuga_test_harness_agito_0_0;
  component kuuga_test_harness_clk_gen_0_0 is
  port (
    clk : out STD_LOGIC;
    sync_rst : out STD_LOGIC
  );
  end component kuuga_test_harness_clk_gen_0_0;
  signal Agito_Input_Loc_1 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal CLK_1 : STD_LOGIC;
  signal RST_1 : STD_LOGIC;
  signal agito_0_ap_done : STD_LOGIC;
  signal agito_0_ap_return : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal clk_gen_0_clk : STD_LOGIC;
  signal clk_gen_0_sync_rst : STD_LOGIC;
  signal input_location_1 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal kuuga_0_ap_done : STD_LOGIC;
  signal kuuga_0_ap_return : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal start_1 : STD_LOGIC;
  signal NLW_agito_0_ap_idle_UNCONNECTED : STD_LOGIC;
  signal NLW_agito_0_ap_ready_UNCONNECTED : STD_LOGIC;
  signal NLW_kuuga_0_ap_idle_UNCONNECTED : STD_LOGIC;
  signal NLW_kuuga_0_ap_ready_UNCONNECTED : STD_LOGIC;
begin
  Agito_Done <= agito_0_ap_done;
  Agito_Input_Loc_1(31 downto 0) <= Agito_Input_Loc(31 downto 0);
  Agito_Result(31 downto 0) <= agito_0_ap_return(31 downto 0);
  CLK_1 <= Kuuga_CLK;
  Kuuga_Result(31 downto 0) <= kuuga_0_ap_return(31 downto 0);
  Kuuga_done <= kuuga_0_ap_done;
  RST_1 <= Kuuga_RST;
  input_location_1(31 downto 0) <= Kuuga_Input_Loc(31 downto 0);
  start_1 <= start;
agito_0: component kuuga_test_harness_agito_0_0
     port map (
      ap_clk => clk_gen_0_clk,
      ap_done => agito_0_ap_done,
      ap_idle => NLW_agito_0_ap_idle_UNCONNECTED,
      ap_ready => NLW_agito_0_ap_ready_UNCONNECTED,
      ap_return(31 downto 0) => agito_0_ap_return(31 downto 0),
      ap_rst => clk_gen_0_sync_rst,
      ap_start => start_1,
      output_loc(31 downto 0) => Agito_Input_Loc_1(31 downto 0)
    );
clk_gen_0: component kuuga_test_harness_clk_gen_0_0
     port map (
      clk => clk_gen_0_clk,
      sync_rst => clk_gen_0_sync_rst
    );
kuuga_0: component kuuga_test_harness_kuuga_0_0
     port map (
      ap_clk => CLK_1,
      ap_done => kuuga_0_ap_done,
      ap_idle => NLW_kuuga_0_ap_idle_UNCONNECTED,
      ap_ready => NLW_kuuga_0_ap_ready_UNCONNECTED,
      ap_return(31 downto 0) => kuuga_0_ap_return(31 downto 0),
      ap_rst => RST_1,
      ap_start => start_1,
      output_loc(31 downto 0) => input_location_1(31 downto 0)
    );
end STRUCTURE;
