HHHHHHHHHHHHHHHH// Declares a brand new function 
(Main.Main.fibonacci)

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
AM = M - 1
D = M
@SP
AM = M - 1
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

// if-goto label (unconditional jump) ... 
@SP
M = M-1
A = M
D = M
@IF_TRUE
D;JGT

// goto label (unconditional jump) ... 
@IF_FALSE
0;JMP

// generating label ... 
(IF_TRUE)

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

// return to return_address... 
@LCL
D = M
@5
M = D
@5
A = D - A
D = M
@6
M = D

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

@ARG
D = M
@SP
M = D + 1
@5
M = M - 1
A = M
D = M
@THAT
M = D
@5
M = M - 1
A = M
D = M
@THIS
M = D
@5
M = M - 1
A = M
D = M
@ARG
M = D
@5
M = M - 1
A = M
D = M
@LCL
M = D
@6
A = M
0;JMP

// generating label ... 
(IF_FALSE)

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
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1

// call function f
@Main.Main.fibonacci$ret.1
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push local 0
@LCL
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

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

// push this 0
@THIS
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push that 0
@THAT
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

@SP
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D

// goto label (unconditional jump) ... 
@Main.Main.fibonacci
0;JMP

(Main.Main.fibonacci$ret.1)

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
AM = M - 1
D = M
@SP
AM = M - 1
M = M - D
@SP
M = M + 1

// call function f
@Main.Main.fibonacci$ret.2
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push local 0
@LCL
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

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

// push this 0
@THIS
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push that 0
@THAT
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

@SP
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D

// goto label (unconditional jump) ... 
@Main.Main.fibonacci
0;JMP

(Main.Main.fibonacci$ret.2)

// arithmetic/logical add
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1

// return to return_address... 
@LCL
D = M
@5
M = D
@5
A = D - A
D = M
@6
M = D

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

@ARG
D = M
@SP
M = D + 1
@5
M = M - 1
A = M
D = M
@THAT
M = D
@5
M = M - 1
A = M
D = M
@THIS
M = D
@5
M = M - 1
A = M
D = M
@ARG
M = D
@5
M = M - 1
A = M
D = M
@LCL
M = D
@6
A = M
0;JMP

// Declares a brand new function 
(Sys.Sys.init)

// push constant 4
@4
D = A
@SP
A = M
M = D
@SP
M = M + 1

// call function f
@Sys.Main.fibonacci$ret.3
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push local 0
@LCL
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

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

// push this 0
@THIS
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push that 0
@THAT
D = M
@0
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

@SP
D = M
@5
D = D - A
@1
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D

// goto label (unconditional jump) ... 
@Sys.Main.fibonacci
0;JMP

(Sys.Main.fibonacci$ret.3)

// generating label ... 
(WHILE)

// goto label (unconditional jump) ... 
@WHILE
0;JMP


// END of program 
(ENDP)
	@ENDP
	0;JMP

