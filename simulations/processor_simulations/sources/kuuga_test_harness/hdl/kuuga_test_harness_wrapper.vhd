--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.4 (lin64) Build 1412921 Wed Nov 18 09:44:32 MST 2015
--Date        : Wed Mar 23 21:39:45 2016
--Host        : csteach0 running 64-bit Ubuntu 14.04.4 LTS
--Command     : generate_target kuuga_test_harness_wrapper.bd
--Design      : kuuga_test_harness_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity kuuga_test_harness_wrapper is
  port (
    Agito_CLK : in STD_LOGIC;
    Agito_Done : out STD_LOGIC;
    Agito_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Agito_RST : in STD_LOGIC;
    Agito_Result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_CLK : in STD_LOGIC;
    Kuuga_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_RST : in STD_LOGIC;
    Kuuga_Result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_done : out STD_LOGIC;
    start : in STD_LOGIC
  );
end kuuga_test_harness_wrapper;

architecture STRUCTURE of kuuga_test_harness_wrapper is
  component kuuga_test_harness is
  port (
    start : in STD_LOGIC;
    Kuuga_done : out STD_LOGIC;
    Kuuga_Result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Kuuga_CLK : in STD_LOGIC;
    Kuuga_RST : in STD_LOGIC;
    Agito_CLK : in STD_LOGIC;
    Agito_RST : in STD_LOGIC;
    Agito_Input_Loc : in STD_LOGIC_VECTOR ( 31 downto 0 );
    Agito_Done : out STD_LOGIC;
    Agito_Result : out STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  end component kuuga_test_harness;
begin
kuuga_test_harness_i: component kuuga_test_harness
     port map (
      Agito_CLK => Agito_CLK,
      Agito_Done => Agito_Done,
      Agito_Input_Loc(31 downto 0) => Agito_Input_Loc(31 downto 0),
      Agito_RST => Agito_RST,
      Agito_Result(31 downto 0) => Agito_Result(31 downto 0),
      Kuuga_CLK => Kuuga_CLK,
      Kuuga_Input_Loc(31 downto 0) => Kuuga_Input_Loc(31 downto 0),
      Kuuga_RST => Kuuga_RST,
      Kuuga_Result(31 downto 0) => Kuuga_Result(31 downto 0),
      Kuuga_done => Kuuga_done,
      start => start
    );
end STRUCTURE;
