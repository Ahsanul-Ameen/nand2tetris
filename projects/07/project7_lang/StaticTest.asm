// push constant 111
@111
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 333
@333
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 888
@888
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop static 8
@SP
M = M - 1
A = M
D = M
@.8
M = D

// pop static 3
@SP
M = M - 1
A = M
D = M
@.3
M = D

// pop static 1
@SP
M = M - 1
A = M
D = M
@.1
M = D

// push static 3
@.3
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push static 1
@.1
D = M
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

// push static 8
@.8
D = M
@SP
A = M
M = D
@SP
M = M + 1

// arithmetic/logical add
@SP
AM = M - 1
D = M
@SP
AM = M - 1
M = M + D
@SP
M = M + 1


// END of program 
(ENDP)
	@ENDP
	0;JMP

