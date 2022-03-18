// function SimpleFunction.test 2
(SimpleFunction.test)

// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 0
@0
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

// push local 1
@LCL
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

// arithmetic/logical not
@SP
M = M - 1
A = M
M = !M
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
@LCL
D = M
@endFrame
M = D
@endFrame
D = M
@5
A = D - A
D = M
@retAddr
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
D = M + 1
@SP
M = D
@endFrame
D = M
@1
A = D - A
D = M
@THAT
M = D
@endFrame
D = M
@2
A = D - A
D = M
@THIS
M = D
@endFrame
D = M
@3
A = D - A
D = M
@ARG
M = D
@endFrame
D = M
@4
A = D - A
D = M
@LCL
M = D
@retAddr
A = M
0;JMP


// END of all program 
(ENDP)
	@ENDP
	0;JMP

