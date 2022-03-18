#pragma once

#include <string>
#include <fstream>	
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <vector>

using std::string;
using std::ifstream;
using std::stringstream;
using std::istringstream;
using std::vector;


enum Command {
	A_COMMAND,
	C_COMMAND,
	L_COMMAND
};

class Parser {
private:
	ifstream in_file;
	string current_command;
	vector<string> content;
	int current_indx;
private:
	// removes comments and white spaces from code
	string cleanUp(string prgm);
public:
	//	Opens the input file/stream and gets ready to parse it.
	Parser(string const& input_file_path);
	
	//	Are there more commands in the input?
	bool hasMoreCommands();
	
	//	Reads the next command from the input and makes it the current
	//	command. Should be called only if hasMoreCommands() is true.
	//	Initially there is no current command.
	void advance();
	
	//	Returns the type of the current command:
	//	A_COMMAND for @Xxx where Xxx is either a symbol or a decimal number
	//	C_COMMAND for dest=comp;jump
	//	L_COMMAND (actually, pseudo-command) for (Xxx) where Xxx is a symbol.
	Command commandType();
	
	// Returns current token;
	string getCurrentToken();
	
	//	Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx). 
	//	Should be called only when commandType() is A_COMMAND or L_COMMAND.
	string symbol();
	
	//	Returns the dest mnemonic in the current C-command (8 possi-bilities).
	//  Should be called only when commandType() is C_COMMAND.
	string dest();
	
	//	Returns the comp mnemonic in the current C-command (28 pos-sibilities). 
	//	Should be called only when commandType() is C_COMMAND.
	string comp();
	
	//	Returns the jump mnemonic in the current C-command (8 pos-sibilities). 
	//	Should be called only when commandType() is C_COMMAND.
	string jump();
	
	// Closes the input file
	virtual ~Parser();
};
