// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop local 0
@LCL
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

// generating label ... 
(BasicLoop.LOOP_START)

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

// pop local 0
@LCL
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

// if-goto label (unconditional jump) ... 
@SP
M = M-1
A = M
D = M
@BasicLoop.LOOP_START
D;JGT

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


// END of all program 
(ENDP)
	@ENDP
	0;JMP

