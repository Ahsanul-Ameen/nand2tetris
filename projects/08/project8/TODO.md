label c 	This command labels the current location in the function’s code. Only labeled
locations can be jumped to from other parts of the program. The label c is an
arbitrary string composed of letters, numbers, and the special characters “ _ ” ,
“ : ”, and “ . ”. The scope of the label is the current function.
[a-zA-Z0-9_:/.]

goto c	 This command effects a "goto" operation, causing execution to continue from
the location marked by the c label. The jump destination must be located in the
same function.

if-goto c	 This command effects a "conditional goto" operation. The stack’s topmost
value is popped; if the value is not zero, execution continues from the location
marked by the c label; otherwise, execution continues from the next command
in the program. The jump destination must be located in the same function.


function f n 	Here starts the code of a function named f, which has n local variables;
		
			
		(fileName.functionName)							// declare label for function entry
		for(int i = 1; i <= numLocal; ++i) {		// k=number of local variables
			push constant 0							// initialize all of them to 0
		}
		
		
call f m 		Call function f , stating that m arguments have already been pushed onto the stack;
		
		push @fileName.functionName$ret.i // (using label below)
		push LCL // save LCL of calling function
		push ARG // save ARG of calling function
		push THIS // save THIS of calling function
		push THAT // save THAT of calling function
		ARG = SP-n-5 // reposition ARG (n=number of args)
		LCL = SP // reposition LCL
		goto f // transfer control
		(fileName.functionName$ret.i) // label for the return address
		
return 			Return to the calling function.


		FRAME=LCL // FRAME is a temporary variable   |temp0 
		RET=*(FRAME-5) // save return address in a temp.  |var temp1
		*ARG=pop() // reposition return value for caller	|
		SP=ARG+1 // restore SP for caller
		THAT=*(FRAME-1) // restore THAT of calling function
		THIS=*(FRAME-2) // restore THIS of calling function
		ARG=*(FRAME-3) // restore ARG of calling function
		LCL=*(FRAME-4) // Restore LCL of calling function
		goto RET // GOTO the return-address
		
		
		
		

/home/ubuntu/Videos/Level_3Term_2/Nand to Tetris/nand2tetris/projects/08/FunctionCalls/FibonacciElement/Sys.vm
		



