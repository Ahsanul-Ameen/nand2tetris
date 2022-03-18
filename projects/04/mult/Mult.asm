// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.



// fetch value stored in RAM[0] and store it in variable a
(LOAD_A)
	@R0
	D = M
	@a
	M = D	// a = RAM[0]
// fetch value stored in RAM[1] and store it in variable b
(LOAD_B)
	@R1
	D = M
	@b
	M = D	// b = RAM[1]

// update RAM[2]
(RESET)
	@0
	D = A
	@R2
	M = D	// RAM[2] = 0
	
// add a b times to RAM[2]
(LOOP)
	@a
	D = M
	@END
	D;JLE	// end if a <= 0
	
	@b
	D = M
	@END	
	D;JLE	// optional also end if b <= 0
	@R2
	M = D + M	// RAM[2] = b + RAM[2]
	//decrease value of a 
	@a
	M = M - 1	// a = a - 1
	@LOOP
	0;JMP

(END)
	@END
	0;JMP


