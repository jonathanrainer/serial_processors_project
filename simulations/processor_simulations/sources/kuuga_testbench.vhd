library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity kuuga_testbench is
end kuuga_testbench;

architecture Behavioral of kuuga_testbench is
    
    signal sig_CLK, sig_RST, sig_start, sig_done : STD_LOGIC;
    signal sig_result, sig_input_location: STD_LOGIC_VECTOR (31 downto 0);
    
    component kuuga_test_harness_wrapper is
      port (
      CLK : in STD_LOGIC;
      RST : in STD_LOGIC;
      done : out STD_LOGIC;
      input_location : in STD_LOGIC_VECTOR ( 31 downto 0 );
      result : out STD_LOGIC_VECTOR ( 31 downto 0 );
      start : in STD_LOGIC
    );
    end component;

begin uut: kuuga_test_harness_wrapper
        port map (
            start => sig_start,
            done => sig_done,
            result => sig_result,
            input_location => sig_input_location,
            CLK => sig_CLK,
            RST => sig_RST
            );
            
        clock: process begin
            wait for 200ns;
            L1: loop
                exit L1 when sig_done = '1';
                sig_CLK <= '0';
                wait for 10ns;
                sig_CLK <= '1';
                wait for 10ns;
            end loop;
            end process;
            
        testbench: process begin
            sig_RST <= '1';
            wait for 5ns;
            sig_RST <= '0';
            wait for 235ns;
            sig_input_location <= "00000000000000000000000000000010";
            sig_start <= '1';
            wait;
            end process;            
    


end Behavioral;
