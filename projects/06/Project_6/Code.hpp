#pragma once

#include <string>
#include <unordered_map>
#include <bitset>

using std::string;
using std::unordered_map;
using std::bitset;


struct Code {
	static unordered_map<string, string> dest_map, comp_map, jump_map;
	
	//	Returns the binary code(3 bits) of the dest mnemonic.
	static string dest(const string& mnemonic);
	
	// Returns the binary code(7 bits) of the comp mnemonic.
	static string comp(const string& mnemonic);
	
	//	Returns the binary code(3 bits) of the jump mnemonic.
	static string jump(const string& mnemonic);
	
	// Returns the binary code(15 bits) of the A-instruction mnemonic
	static string addr(int address);
};


