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

// function Class1.set 0
// generating label ... 
(Class1.set)

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

// pop static 0
@SP
M = M - 1
A = M
D = M
@Class1.0
M = D

// push argument 1
@ARG
D = M
@1
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// pop static 1
@SP
M = M - 1
A = M
D = M
@Class1.1
M = D

// push constant 0
@0
D = A
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

// function Class1.get 0
// generating label ... 
(Class1.get)

// push static 0
@Class1.0
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push static 1
@Class1.1
D = M
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

// function Class2.set 0
// generating label ... 
(Class2.set)

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

// pop static 0
@SP
M = M - 1
A = M
D = M
@Class2.0
M = D

// push argument 1
@ARG
D = M
@1
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// pop static 1
@SP
M = M - 1
A = M
D = M
@Class2.1
M = D

// push constant 0
@0
D = A
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

// function Class2.get 0
// generating label ... 
(Class2.get)

// push static 0
@Class2.0
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push static 1
@Class2.1
D = M
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

// push constant 6
@6
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 8
@8
D = A
@SP
A = M
M = D
@SP
M = M + 1

// call Class1.set 2
@Sys.init$ret.2	// push retAddrLabel
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
@2
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Class1.set	// goto label
0;JMP

// generating label ... 
(Sys.init$ret.2)

// pop temp 0
@5
D = A
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

// push constant 23
@23
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 15
@15
D = A
@SP
A = M
M = D
@SP
M = M + 1

// call Class2.set 2
@Sys.init$ret.3	// push retAddrLabel
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
@2
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Class2.set	// goto label
0;JMP

// generating label ... 
(Sys.init$ret.3)

// pop temp 0
@5
D = A
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

// call Class1.get 0
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
@0
D = D - A
@ARG
M = D
@SP	// LCL = SP
D = M
@LCL
M = D

@Class1.get	// goto label
0;JMP

// generating label ... 
(Sys.init$ret.4)

// call Class2.get 0
@Sys.init$ret.5	// push retAddrLabel
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

@Class2.get	// goto label
0;JMP

// generating label ... 
(Sys.init$ret.5)

// generating label ... 
(Sys.WHILE)

@Sys.WHILE	// goto label
0;JMP

