// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


(INFINITE_LOOP)
	(LOAD_SCREEN_ADDRESS)
		@SCREEN
		D = A
		@addr
		M = D	// addr = 16384
				// (screen’s base address)
		@8192
		D = A
		@n
		M = D	// n = (256 * 512 / 16) = 8192
		
	(INPUT)
		@KBD
		D = M
		@BLACK_SCREEN
		D;JNE
		
		
	// clear whole screen 
	(CLEAR_SCREEN)
		@addr	
		A = M	
		M = 0	// RAM[addr] = 0x0000
		@addr
		M = M + 1	// addr = addr + 1
		@n
		M = M - 1
		D = M
		@CLEAR_SCREEN
		D;JGT
	
	@CONDITION	// continue and don't execute BLACK_SCREEN
	0;JMP
	
	// make screen black
	(BLACK_SCREEN)
		@addr	
		A = M	
		M = -1	// RAM[addr] = 0xFFFF
		@addr
		M = M + 1	// addr = addr + 1
		@n
		M = M - 1
		D = M
		@BLACK_SCREEN
		D;JGT
	
	
	(CONDITION)
		@INFINITE_LOOP
		0;JMP
	
	
