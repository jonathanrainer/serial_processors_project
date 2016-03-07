--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.4 (lin64) Build 1412921 Wed Nov 18 09:44:32 MST 2015
--Date        : Sat Mar  5 17:24:17 2016
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
    CLK : in STD_LOGIC;
    RST : in STD_LOGIC;
    done : out STD_LOGIC;
    input_location : in STD_LOGIC_VECTOR ( 31 downto 0 );
    result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    start : in STD_LOGIC
  );
end kuuga_test_harness_wrapper;

architecture STRUCTURE of kuuga_test_harness_wrapper is
  component kuuga_test_harness is
  port (
    start : in STD_LOGIC;
    done : out STD_LOGIC;
    result : out STD_LOGIC_VECTOR ( 31 downto 0 );
    input_location : in STD_LOGIC_VECTOR ( 31 downto 0 );
    CLK : in STD_LOGIC;
    RST : in STD_LOGIC
  );
  end component kuuga_test_harness;
begin
kuuga_test_harness_i: component kuuga_test_harness
     port map (
      CLK => CLK,
      RST => RST,
      done => done,
      input_location(31 downto 0) => input_location(31 downto 0),
      result(31 downto 0) => result(31 downto 0),
      start => start
    );
end STRUCTURE;
