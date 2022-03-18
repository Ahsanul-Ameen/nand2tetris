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

// pop pointer 1
@SP
M = M - 1
A = M
D = M
@THAT
M = D

// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop that 0
@THAT
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

// push constant 1
@1
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop that 1
@THAT
D = M
@1
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

// generating label ... 
(FibonacciSeries.MAIN_LOOP_START)

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
@FibonacciSeries.COMPUTE_ELEMENT
D;JGT

// goto label (unconditional jump) ... 
@FibonacciSeries.END_PROGRAM
0;JMP

// generating label ... 
(FibonacciSeries.COMPUTE_ELEMENT)

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

// push that 1
@THAT
D = M
@1
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

// pop that 2
@THAT
D = M
@2
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

// push pointer 1
@THAT
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

// pop pointer 1
@SP
M = M - 1
A = M
D = M
@THAT
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

// goto label (unconditional jump) ... 
@FibonacciSeries.MAIN_LOOP_START
0;JMP

// generating label ... 
(FibonacciSeries.END_PROGRAM)


// END of all program 
(ENDP)
	@ENDP
	0;JMP

