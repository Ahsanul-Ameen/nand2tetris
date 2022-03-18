#Arithmetic / Logical commands

Command 	Return value 	Return value
add 		x + y 			integer	ok
sub 		x - y 			integer	ok
neg 			-y 			integer	ok
eq 			x==0 			boolean ok
gt 			x > y 			boolean ok
lt 			x < y 			boolean ok
and 		x and y 		boolean	ok
or 			x or y 			boolean	ok
not 		not x 			boolean ok

0, 1, -1, D, A, !D, !A, -D, -A, D+1, A+1, D-1, A-1, D+A, D-A, A-D, D&A, D|A,
M,
!M,
-M,
M+1,
M-1, D+M, D-M, M-D, D&M, D|M

#add / sub/ and / or 
	SP--	
	D = *SP
	SP--
	*SP +/-/&/|= D
	++SP
	
	
====================================================
HACK assembly:
			
			@SP
			AM = M - 1	// SP--
			D = M		// D = *SP
			@SP
			AM = M - 1	// SP--
			M = M op D	// compute
			@SP			
			M = M + 1	// SP++
====================================================
	
	
#neg
	SP--
	*SP = -*SP
	++SP
	
	
====================================================
HACK assembly:
			
			@SP
			AM = M - 1	// SP--
			M = -M		// neg
			@SP			
			M = M + 1	// SP++
====================================================



#eq/gt/lt
	x > y	-> x-y;JGT put -1 / or 0
	x == y	-> x-y;JE  put -1 / or 0
	x < y	-> x-y;JLT put -1 / or 0



====================================================
HACK assembly:
	// please provide LABEL_i to distinguish between different VM instructions
	// ++i
			
			@SP
			AM = M - 1	// SP--
			D = M		// D = *SP
			@SP
			AM = M - 1	// SP--
			D = M - D
			@TRUE_i
			D;JGT/JE/JLT
			(FALSE_i)
				@SP
				A = M
				M = 0	// *SP = false
				@END_i
				0;JMP	// jump to end_i
			(TRUE_i)
				@SP
				A = M
				M = -1	// *SP = true
			(END_i)
			@SP			
			M = M + 1	// SP++
====================================================



#not 
	--SP
	*SP = !*SP


====================================================
HACK assembly:
	// please provide LABEL_i to distinguish between different VM instructions
	// ++i
			
			@SP
			AM = M - 1	// SP--
			M = !M		// *SP = !*SP
			@SP			
			M = M + 1	// SP++
====================================================






#Memory access commands
pop segment	i
push segment i

	

#Memory segments

Syntax: push / pop segment i
Examples:
• push constant 17
• pop local 2
• pop static 5
• push argument 3





#Stack Implementation		[push/pop local/argument/this/that i]	// done

push segment i				addr = segmentPointer + i, *SP = *addr, SP++ 

example: push local i				addr = LCL + i, *SP = *addr, SP++ 
====================================================
HACK assembly:
			@LCL
			D = M		// D = localaddress
			@i
			A = D + A	// D = RAM[LCL] + i
			D = M		// D = *addr
			@SP
			A = M
			M = D		// *SP = *addr
			@SP
			M = M + 1	// SP++
====================================================


pop segment i				addr = segmentPointer + i, SP--, *addr = *SP


example: pop local i		addr = LCL + i, SP--, *addr = *SP

====================================================
HACK assembly:
	
	@LCL
	D = M	
	@0
	D = D + A
	@R13
	M = D		// R13 = segmentPointer + i
	@SP
	M = M - 1
	A = M	
	D = M		// D = *SP
	@R13
	A = M
	M = D		//*addr = *SP

====================================================


segment	= { local , argument , this , that }

#SEGMENT POINTERS	

	SP
	LCL	
	ARG
	THIS
	THAT
	

	


#Constant 		// done
push constant i				*SP = i, SP++

====================================================
HACK assembly:
			@i
			D = A		// D = i
			@SP
			A = M
			M = D		// *SP = D = i
			@SP
			M = M + 1	// SP++
====================================================


example: 	push constant 17
pseudo assembly:
			*SP = 17
			SP++
Hack assembly:
			@17
			D = A	// D = 17
			@SP		
			A = M
			M = D   // *SP = D
			@SP
			M = M + 1 //SP++
			


#Static	segment [16, 255]	// done

push static i				//stack.push(D)

========================================================
HACK assembly
							@filename.i	
							D = M		// D = static i
							@SP
							A = M
							M = D		// stack.push(D)
							@SP
							M = M + 1	// SP++	
=======================================================
							
							
pop static i				// D = stack.pop (code omitted)
========================================================
HACK assembly
							@SP
							AM = M - 1	// SP--
							D = M		// D = *SP = stack.pop()
							@filename.i
							M = D		// pop static i
=======================================================							
							
							
#Temp	[R5 - R12] total 8 registers // done

push temp i					addr = 5 + i, *SP = *addr, SP++

====================================================
HACK assembly:
			@5
			D = A		// D = 5
			@i
			A = D + A	// A = 5 + i
			D = M		// D = *temp
			@SP
			A = M
			M = D		// *SP = *addr
			@SP
			M = M + 1	// SP++
====================================================

pop temp i					addr = 5 + i, SP--, *addr = *SP

====================================================
HACK assembly:
	
				"@5\n"
				"D = A\n" 
				"@" + i + "\n"		
				"D = D + A\n"		
				"@R13\n"
				"M = D\n"	// R13 = 5 + i
				"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"		// A = SP
				"D = M\n"		// D = *SP			
				"@R13\n"
				"A = M\n"
				"M = D\n";		// *addr = *SP

====================================================



#Pointer 0/1 // done

push pointer 0/1			*SP = THIS/THAT, SP++

====================================================
HACK assembly:
			@THIS/THAT
			D = M		// D = THIS/THAT
			@SP
			A = M
			M = D		// *SP = D
			@SP
			M = M + 1	// SP++
====================================================

pop pointer 0/1				SP--, THIS/THAT = *SP


====================================================
HACK assembly:
			@SP			
			AM = M - 1	// SP--
			D = M		// D = *SP
			@THIS/THAT
			M = D		// THIS/THAT = D
====================================================





