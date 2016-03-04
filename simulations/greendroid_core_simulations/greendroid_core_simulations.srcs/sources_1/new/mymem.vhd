
----------------------------------------------------------------------------------
-- Company: The University of York
-- Engineer: Christopher Crispin-Bailey
-- 
-- Create Date:    19:57:29 04/09/2014 
-- Design Name: 
-- Module Name:    mem - Behavioral 
-- Project Name:    Bit Serial Processors
-- Target Devices: 
-- Tool versions: 
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

entity mem is

PORT (
        M_ADDR :   IN std_logic_vector(31 DOWNTO 0);
        M_DATA : INOUT std_logic_vector(31 DOWNTO 0);
        M_RD  : IN std_logic; 
        M_WR  : IN std_logic; 
        M_RDY : OUT std_logic;
		 
	MWAIT : IN std_logic;
	MDAT  : IN std_logic_vector(31 DOWNTO 0)
      ); 


end mem;

architecture Behavioral of mem is

begin


PROCESS(M_ADDR, M_RD,M_WR)
BEGIN

	M_DATA <= (OTHERS =>'Z');

	IF(M_RD='1') THEN
	
		M_DATA <= MDAT;

	END IF;

		-- MRDY SIGNAL --
		
		M_RDY <='1' AND MWAIT;
		
END PROCESS;



end Behavioral;
