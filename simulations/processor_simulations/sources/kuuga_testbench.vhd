library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity kuuga_testbench is
end kuuga_testbench;

architecture Behavioral of kuuga_testbench is
    
    signal sig_Agito_CLK, sig_Kuuga_CLK, sig_Kuuga_RST, sig_Agito_RST, sig_start, sig_Kuuga_done, sig_Agito_done : STD_LOGIC;
    signal sig_Agito_Result, sig_Kuuga_Result, sig_Agito_Input_Loc,  sig_Kuuga_Input_Loc: STD_LOGIC_VECTOR (31 downto 0);
    
    component kuuga_test_harness_wrapper is
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
      Kuuga_Done : out STD_LOGIC;
      start : in STD_LOGIC
    );
    end component;

begin uut: kuuga_test_harness_wrapper
        port map (
            Agito_CLK => sig_Agito_CLK,
            Agito_Done => sig_Agito_done,
            Agito_Input_Loc => sig_Agito_Input_Loc,
            Agito_RST => sig_Agito_RST,
            Agito_Result => sig_Agito_Result,
            Kuuga_CLK => sig_Kuuga_CLK,
            Kuuga_Done => sig_Kuuga_done,
            Kuuga_Input_Loc => sig_Kuuga_Input_Loc,
            Kuuga_RST => sig_Kuuga_RST,
            Kuuga_Result => sig_Kuuga_Result,
            start => sig_start
            );
            
        kuuga_clock: process begin
            wait for 200ns;
            L1: loop
                exit L1 when sig_Kuuga_done = '1';
                sig_Kuuga_CLK <= '0';
                wait for 40ns;
                sig_Kuuga_CLK <= '1';
                wait for 40ns;
            end loop;
            end process;
            
        agito_clock: process begin
            wait for 200ns;
            L2: loop
                exit L2 when sig_Agito_done = '1';
                sig_Agito_CLK <= '0';
                wait for 40ns;
                sig_Agito_CLK <= '1';
                wait for 40ns;
            end loop;
            end process;    
           
        testbench: process begin
            sig_Agito_RST <= '1';
            sig_Kuuga_RST <= '1';
            wait for 5ns;
            sig_Agito_RST <= '0';
            sig_Kuuga_RST <= '0';
            wait for 235ns;
            sig_Agito_Input_Loc <= "00000000000000000000000000000000";
            sig_Kuuga_Input_Loc <= "00000000000000000000000000000100";
            sig_start <= '1';
            wait;
            end process;            
    


end Behavioral;
