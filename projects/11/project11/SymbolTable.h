#pragma once

#include <string>
#include <tuple>
#include <cassert>
#include <unordered_map>

using std::string;
using std::tuple;
using std::unordered_map;
using std::get;


enum Kind { STA_TIC, FIELD, ARG , VAR, NONE };

class SymbolTable {
private:
	// hash map of name : {kind, type, #}
	unordered_map< string, tuple<Kind, string, int> > class_scoped, subroutine_scoped;
	unordered_map<Kind, int> running_cnt;
	//	tup = make_tuple(a, b, c); 
	//	get<0>(tup)
	//	tie(i_val,ignore,f_val) = tup; 
public:	
	// Creates a new empty symbol table
	SymbolTable();
	
	//	Starts a new subroutine scope 
	// (i.e. erases all names in the previous subroutine’s scope.)
	void startSubroutine();
	
	//	Defines a new identifier of a given name,
	// type, and kind and assigns it a running
	// index. STATIC and FIELD identifiers
	// have a class scope, while ARG and VAR
	// identifiers have a subroutine scope.
	void define(const string& name, const string& type, Kind kind);
	
	//	Returns the number of variables of the
	//	given kind already defined in the current scope.
	int varCount(Kind kind);
	
	//	Returns the kind of the named identifier in
	//	the current scope. Returns NONE if the
	//	identifier is unknown in the current scope.
	Kind kindOf(const string& name);
	
	//	Returns the type of the named identifier in
	//	the current scope.
	string typeOf(const string& name);
	
	//	Returns the index assigned to named identifier.
	int indexOf(const string& name);
	
};
