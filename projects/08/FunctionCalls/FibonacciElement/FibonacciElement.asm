//Bootstrap code
@256
D = A
@SP
M = D
// call Sys.init 0
@$ret.1	// push retAddrLabel
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL	// push LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG	// push ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS	// push THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT	// push THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP	// ARG = SP - 5 - nArgs
D = M
@5
D = D - A
@0
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Sys.init	// goto label
0;JMP

// generating label ... 
($ret.1)

// function Main.fibonacci 0
// generating label ... 
(Main.fibonacci)

// push argument 0
@ARG
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push constant 2
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1

// arithmetic/logical lt
@SP
M = M - 1
A = M
D = M
@SP
M = M - 1
A = M
D = M - D
@TRUE_4
D;JLT
(FALSE_4)
	@SP
	A = M
	M = 0
	@END_4
	0;JMP
(TRUE_4)
	@SP
	A = M
	M = -1
(END_4)
@SP
M = M + 1

@SP 	// if-goto label
M = M-1
A = M
D = M
@Main.IF_TRUE
D;JNE

@Main.IF_FALSE	// goto label
0;JMP

// generating label ... 
(Main.IF_TRUE)

// push argument 0
@ARG
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// return
@LCL	//	endFrame = LCL
D = M
@endFrame
M = D
@endFrame	//	retAddr = *(endFrame - 5)
D = M
@5
A = D - A
D = M
@retAddr
M = D
// *ARG = pop()
// pop argument 0
@ARG
D = M
@0
D = D + A
@R13
M = D
@SP
M = M - 1
A = M
D = M
@R13
A = M
M = D

@ARG	//	SP = ARG + 1
D = M + 1
@SP
M = D
@endFrame	// THAT = *(endFrame - 1)
D = M
@1
A = D - A
D = M
@THAT
M = D
@endFrame	// THIS = *(endFrame - 2)
D = M
@2
A = D - A
D = M
@THIS
M = D
@endFrame	// ARG = *(endFrame - 3)
D = M
@3
A = D - A
D = M
@ARG
M = D
@endFrame	// LCL = *(endFrame - 4)
D = M
@4
A = D - A
D = M
@LCL
M = D
@retAddr	// goto retAddr
A = M
0;JMP

// generating label ... 
(Main.IF_FALSE)

// push argument 0
@ARG
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push constant 2
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1

// arithmetic/logical sub
@SP
M = M - 1
A = M
D = M
@SP
M = M - 1
A = M
M = M - D
@SP
M = M + 1

// call Main.fibonacci 1
@Main.fibonacci$ret.2	// push retAddrLabel
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL	// push LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG	// push ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS	// push THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT	// push THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP	// ARG = SP - 5 - nArgs
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Main.fibonacci	// goto label
0;JMP

// generating label ... 
(Main.fibonacci$ret.2)

// push argument 0
@ARG
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push constant 1
@1
D = A
@SP
A = M
M = D
@SP
M = M + 1

// arithmetic/logical sub
@SP
M = M - 1
A = M
D = M
@SP
M = M - 1
A = M
M = M - D
@SP
M = M + 1

// call Main.fibonacci 1
@Main.fibonacci$ret.3	// push retAddrLabel
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL	// push LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG	// push ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS	// push THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT	// push THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP	// ARG = SP - 5 - nArgs
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Main.fibonacci	// goto label
0;JMP

// generating label ... 
(Main.fibonacci$ret.3)

// arithmetic/logical add
@SP
M = M - 1
A = M
D = M
@SP
M = M - 1
A = M
M = M + D
@SP
M = M + 1

// return
@LCL	//	endFrame = LCL
D = M
@endFrame
M = D
@endFrame	//	retAddr = *(endFrame - 5)
D = M
@5
A = D - A
D = M
@retAddr
M = D
// *ARG = pop()
// pop argument 0
@ARG
D = M
@0
D = D + A
@R13
M = D
@SP
M = M - 1
A = M
D = M
@R13
A = M
M = D

@ARG	//	SP = ARG + 1
D = M + 1
@SP
M = D
@endFrame	// THAT = *(endFrame - 1)
D = M
@1
A = D - A
D = M
@THAT
M = D
@endFrame	// THIS = *(endFrame - 2)
D = M
@2
A = D - A
D = M
@THIS
M = D
@endFrame	// ARG = *(endFrame - 3)
D = M
@3
A = D - A
D = M
@ARG
M = D
@endFrame	// LCL = *(endFrame - 4)
D = M
@4
A = D - A
D = M
@LCL
M = D
@retAddr	// goto retAddr
A = M
0;JMP

// function Sys.init 0
// generating label ... 
(Sys.init)

// push constant 4
@4
D = A
@SP
A = M
M = D
@SP
M = M + 1

// call Main.fibonacci 1
@Sys.init$ret.4	// push retAddrLabel
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL	// push LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG	// push ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS	// push THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT	// push THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP	// ARG = SP - 5 - nArgs
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Main.fibonacci	// goto label
0;JMP

// generating label ... 
(Sys.init$ret.4)

// generating label ... 
(Sys.WHILE)

@Sys.WHILE	// goto label
0;JMP

