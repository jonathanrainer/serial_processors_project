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

entity rem_testbench is
end rem_testbench;

architecture Behavioral of rem_testbench is

    signal sig_i00, sig_i01, sig_i02, sig_i03, sig_r00, sig_r01, sig_r02, 
            sig_r03, sig_FP, sig_FPout, sig_M_ADDR, sig_M_DATA, 
            sig_MDAT : std_logic_vector(31 DOWNTO 0);
    signal sig_M_RD, sig_M_WR, sig_M_RDY, sig_reset, sig_CLK, sig_MWAIT : std_logic;
    
    component GreenDroidREMCore is 
         PORT (
           i00 : IN std_logic_vector(31 DOWNTO 0);
           i01 : IN std_logic_vector(31 DOWNTO 0);
           i02 : IN std_logic_vector(31 DOWNTO 0);
           i03 : IN std_logic_vector(31 DOWNTO 0);
   
           r00 : OUT std_logic_vector(31 DOWNTO 0);
           r01 : OUT std_logic_vector(31 DOWNTO 0);
           r02 : OUT std_logic_vector(31 DOWNTO 0);
           r03 : OUT std_logic_vector(31 DOWNTO 0);
   
           FP : IN std_logic_vector(31 DOWNTO 0);
           FPout : OUT std_logic_vector(31 DOWNTO 0);
           M_ADDR :   OUT std_logic_vector(31 DOWNTO 0);
           M_DATA : INOUT std_logic_vector(31 DOWNTO 0);
           M_RD  : INOUT std_logic; 
           M_WR  : INOUT std_logic; 
           M_RDY : IN std_logic; 
           reset : IN std_logic; 
           CLK  : IN std_logic 
         ); 
     end component;
         
     component mem is 
        PORT (
             M_ADDR :   IN std_logic_vector(31 DOWNTO 0);
             M_DATA : INOUT std_logic_vector(31 DOWNTO 0);
             M_RD  : IN std_logic; 
             M_WR  : IN std_logic; 
             M_RDY : OUT std_logic;
              
            MWAIT : IN std_logic;
            MDAT  : IN std_logic_vector(31 DOWNTO 0)
           ); 
     end component;
     
begin
    uut: GreendroidREMCore
        port map (
           i00 => sig_i00,
           i01 => sig_i01,
           i02 => sig_i02,
           i03 => sig_i03,
           r00 => sig_r00,
           r01 => sig_r01,
           r02 => sig_r02,
           r03 => sig_r03,
   
           FP => sig_FP,
           FPout => sig_FPout,
           M_ADDR => sig_M_ADDR,
           M_DATA => sig_M_DATA,
           M_RD  => sig_M_RD,
           M_WR  => sig_M_WR,
           M_RDY => sig_M_RDY,
           reset => sig_reset,
           CLK  => sig_CLK
           );
           
     mymem: mem
        port map(
        M_ADDR => sig_M_ADDR,
        M_DATA => sig_M_DATA,
        M_RD  => sig_M_RD,
        M_WR  => sig_M_WR,
        M_RDY => sig_M_RDY,
        MWAIT => sig_MWAIT,
        MDAT  => sig_MDAT
        );
        
     clock: process begin
        sig_CLK <= '0';
        wait for 5ns;
        sig_CLK <= '1';
        wait for 5ns;
     end process clock;
     
     test: process begin
        sig_i00 <= "00000000000000000000000000001100";
        sig_i01 <= "00000000000000000000000000000010";
        sig_i02 <= "00000000000000000000000000000011";
        sig_i03 <= "00000000000000000000000000000100";
        sig_MDAT <= "00000000000000000000000000011111";
        wait for 5ns;
        wait;
        end process;
        


end Behavioral;
