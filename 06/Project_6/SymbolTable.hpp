#pragma once

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;


class SymbolTable {
private:
	unordered_map<string, int> symbol_map;
public:
	//	Creates a new empty symbol table.
	SymbolTable();
	
	//	Adds the pair (symbol, address) to the table.
	void addEntry(string symbol, int address);
	
	// Does the symbol table contain the given symbol?
	bool contains(string symbol);
	
	//	Returns the address associated with the symbol.
	int GetAddress(string symbol);
	
	// Destructs the symbol table
	~SymbolTable();
};
