#include "SymbolTable.hpp"


static bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


SymbolTable::SymbolTable() {
	this->addEntry("SP", 0);
	this->addEntry("LCL", 1);
	this->addEntry("ARG", 2);
	this->addEntry("THIS", 3);
	this->addEntry("THAT", 4);
	for(int i = 0; i < 16; i++) {
		this->addEntry("R" + std::to_string(i), i);
	}
	this->addEntry("SCREEN", 16384);
	this->addEntry("KBD", 24567);
};


void SymbolTable::addEntry(string symbol, int address) {
	this->symbol_map.insert({symbol, address});
}


bool SymbolTable::contains(string symbol) {
	if(is_number(symbol)) return true;
	auto it = this->symbol_map.find(symbol);
	return (it != this->symbol_map.end());
}


int SymbolTable::GetAddress(string symbol) {
	if(is_number(symbol)) return stoi(symbol);
	return this->symbol_map[symbol];
}


SymbolTable::~SymbolTable() {
	this->symbol_map.clear();
}
