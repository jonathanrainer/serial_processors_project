LIBRARY ieee; 
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;
USE ieee.std_logic_unsigned.all;

ENTITY GreenDroidREMCore IS
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
END ENTITY; 

ARCHITECTURE Behavioural OF GreenDroidREMCore IS
  TYPE States IS (ST_INIT,WS_INIT,ST_RESET,ST00,WS00,ST_END);
  SIGNAL Mstate : States;
BEGIN


-- CONTROL PROCESS --------
 PROCESS(clk,reset)
 BEGIN
 IF reset='1' THEN
    Mstate <= ST_RESET;
	ELSIF(rising_edge(clk)) THEN
 CASE Mstate IS
	WHEN ST_RESET => Mstate <= ST_INIT;
	WHEN ST_INIT => 		IF M_RDY='1' THEN Mstate <= ST00; ELSE Mstate <= WS_INIT; END IF;

	WHEN WS_INIT => 		IF M_RDY='1' THEN Mstate <= ST00; END IF;

	WHEN ST00 | WS00| ST_END => 	WHEN OTHERS => 

 END CASE;
END IF;
 END PROCESS;


-- EXECUTE PROCESS --------
 PROCESS(clk,reset)
  VARIABLE T,s0,s1,s2,s3,s4,s5,s6,s7,fpi :std_logic_vector(31 DOWNTO 0);
 BEGIN
	IF(reset='1') THEN
    -- reset any internal states -- 

    s0 := (OTHERS=>'0');
    s1 := (OTHERS=>'0');
    s2 := (OTHERS=>'0');
    s3 := (OTHERS=>'0');
    s4 := (OTHERS=>'0');
    s5 := (OTHERS=>'0');
    s6 := (OTHERS=>'0');
    s7 := (OTHERS=>'0');
 fpi:=(OTHERS=>'0'); 
 M_ADDR <= (OTHERS=>'Z');
 M_DATA <= (OTHERS=>'Z');
 M_RD <= 'Z';
 M_WR <= 'Z';

	ELSIF(rising_edge(clk)) THEN
    M_DATA <="ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
 CASE Mstate IS
    WHEN ST_INIT => 
	-- connect 4 input params here --
	  s0 := i00;
	  s1 := i01;
	  s2 := i02;
	  s3 := i03;
	fpi := FP;
 --rsd2 ;
 	T:=s0 ;
  s0:=s1 ;
  s1:=T ;
 --copy1 ;
	   s7 := s6;
	   s6 := s5;
	   s5 := s4;
	   s4 := s3;
	   s3 := s2;
	   s2 := s1;
	   s1 := s0;
 --copy3 ;
  T:= s2 ;
	   s7 := s6;
	   s6 := s5;
	   s5 := s4;
	   s4 := s3;
	   s3 := s2;
	   s2 := s1;
	   s1 := s0;
  s0:=T ;
 --mul ;
  s0:=std_logic_vector(signed(s0)/signed(s1)) ;
	   s1 := s2;
	   s2 := s3;
	   s3 := s4;
	   s4 := s5;
	   s5 := s6;
	   s6 := s7;
 --rsd3 ;
 	T:=s2 ;
  s2:=s1 ;
  s1:=s0 ;
  s0:=T ;
 --mul ;
  s0:=std_logic_vector(resize(signed(s0)*signed(s1), 32));
	   s1 := s2;
	   s2 := s3;
	   s3 := s4;
	   s4 := s5;
	   s5 := s6;
	   s6 := s7;
 --sub ;
  s0:=s0-s1 ;
	   s1 := s2;
	   s2 := s3;
	   s3 := s4;
	   s4 := s5;
	   s5 := s6;
	   s6 := s7;
	-- recover 4 results here --
	  r00 <= s0;
	  r01 <= s1;
	  r02 <= s2;
	  r03 <= s3;
	FPout <= fpi;

    WHEN OTHERS => 

   END CASE;
	END IF; 

 END PROCESS;

END ARCHITECTURE;

