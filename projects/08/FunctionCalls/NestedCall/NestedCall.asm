//Bootstrap code
@256
D = A
@SP
M = D
// call Sys.init 0
@$ret.1
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
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
@0
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D

// goto label (unconditional jump) ... 
@Sys.init
0;JMP

($ret.1)


// function Sys.init 0
(Sys.init)

// push constant 4000
@4000
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop pointer 0
@SP
M = M - 1
A = M
D = M
@THIS
M = D

// push constant 5000
@5000
D = A
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

// call Sys.main 0
@Sys.init$ret.2
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
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
@0
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D

// goto label (unconditional jump) ... 
@Sys.main
0;JMP

(Sys.init$ret.2)

// pop temp 1
@5
D = A
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

// generating label ... 
(Sys.LOOP)

// goto label (unconditional jump) ... 
@Sys.LOOP
0;JMP

// function Sys.main 5
(Sys.main)

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

// push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

// push constant 4001
@4001
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop pointer 0
@SP
M = M - 1
A = M
D = M
@THIS
M = D

// push constant 5001
@5001
D = A
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

// push constant 200
@200
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop local 1
@LCL
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

// push constant 40
@40
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop local 2
@LCL
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

// push constant 6
@6
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop local 3
@LCL
D = M
@3
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

// push constant 123
@123
D = A
@SP
A = M
M = D
@SP
M = M + 1

// call Sys.add12 1
@Sys.main$ret.3
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
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
@Sys.add12
0;JMP

(Sys.main$ret.3)

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

// push local 2
@LCL
D = M
@2
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push local 3
@LCL
D = M
@3
A = D + A
D = M
@SP
A = M
M = D
@SP
M = M + 1

// push local 4
@LCL
D = M
@4
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

// function Sys.add12 0
(Sys.add12)

// push constant 4002
@4002
D = A
@SP
A = M
M = D
@SP
M = M + 1

// pop pointer 0
@SP
M = M - 1
A = M
D = M
@THIS
M = D

// push constant 5002
@5002
D = A
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

// push constant 12
@12
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

