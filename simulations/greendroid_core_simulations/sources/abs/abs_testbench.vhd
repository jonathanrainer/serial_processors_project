----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04.03.2016 11:22:26
-- Design Name: 
-- Module Name: rem_testbench - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity abs_testbench is
end abs_testbench;

architecture Behavioural of abs_testbench is

    signal sig_i00, sig_i01, sig_i02, sig_r00, sig_r01, sig_r02,
     sig_FP, sig_FPout,sig_MDAT : std_logic_vector(31 DOWNTO 0);
    signal sig_reset, sig_CLK, sig_MWAIT : std_logic;
    
    component ABSCoreAndMemory is 
         PORT (
            in0 : IN std_logic_vector(31 DOWNTO 0);
            in1 : IN std_logic_vector(31 DOWNTO 0);
            in2 : IN std_logic_vector(31 DOWNTO 0);
        
            out0 : OUT std_logic_vector(31 DOWNTO 0);
            out1 : OUT std_logic_vector(31 DOWNTO 0);
            out2 : OUT std_logic_vector(31 DOWNTO 0);
            
            frame_pointer : IN std_logic_vector(31 DOWNTO 0);
            frame_pointer_out : OUT std_logic_vector(31 DOWNTO 0);
            rst : IN std_logic; 
            clck  : IN std_logic; 
            
            mem_wait : IN std_logic;
            mem_push  : IN std_logic_vector(31 DOWNTO 0)
            );
     end component;
     
begin

    uut: ABSCoreAndMemory
        port map (
           in0 => sig_i00,
           in1 => sig_i01,
           in2 => sig_i02,
           out0 => sig_r00,
           out1 => sig_r01,
           out2 => sig_r02,
   
           frame_pointer => sig_FP,
           frame_pointer_out => sig_FPout,
           rst => sig_reset,
           clck  => sig_CLK,
           mem_wait => sig_MWAIT,
           mem_push => sig_MDAT
           );
     
     clock: process 
     constant clock_period:time := 40ns;
     begin   
        wait for 200ns;
        for I in 0 to 100 loop
            sig_CLK <= '0';
            wait for clock_period/2;
            sig_CLK <= '1';
            wait for clock_period/2;
        end loop;
        wait;
        end process clock;
     
     test: process begin
        sig_MWAIT <= '1';
        sig_reset <= '1';
        wait for 100ns;
        sig_reset <= '0';
        wait for 100ns;
        sig_i00 <=              "00110000000000000000000000000000";
        sig_i01 <=              "00000000000000000000001001011111";
        sig_i02 <=              "00000000000000000000000001000101";
        sig_MDAT <=             "00000000000000000000000000011111";
        sig_FP <=               "00000000000000000000000001001000";
        wait;
     end process test;
        


end Behavioural;
