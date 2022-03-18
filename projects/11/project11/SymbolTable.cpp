#include "SymbolTable.h"


SymbolTable::SymbolTable() : 
	running_cnt({{STA_TIC, 0}, {FIELD, 0}, {ARG, 0}, {VAR, 0}})
{}

void SymbolTable::startSubroutine() {
	subroutine_scoped.clear();
	running_cnt[ARG] = running_cnt[VAR] = 0;
}

void SymbolTable::define(const string& name, const string& type, Kind kind) {
	assert(kind != NONE);
	if(kind == STA_TIC || kind == FIELD) {
		class_scoped.insert({name, make_tuple(kind, type, running_cnt[kind]++)});
	} else if(kind == ARG || kind == VAR) {
		subroutine_scoped.insert({name, make_tuple(kind, type, running_cnt[kind]++)});
	}
}

int SymbolTable::varCount(Kind kind) {
	assert(kind != NONE);
	return running_cnt[kind];
}

Kind SymbolTable::kindOf(const string& name) {
	auto it = subroutine_scoped.find(name);
	if(it != subroutine_scoped.end()) {
		return get<0>(it->second);
	} 
	it = class_scoped.find(name);
	if(it != class_scoped.end()) {
		return get<0>(it->second);
	}
	return NONE;
}

string SymbolTable::typeOf(const string& name) {
	auto it = subroutine_scoped.find(name);
	if(it != subroutine_scoped.end()) {
		return get<1>(it->second);
	} 
	it = class_scoped.find(name);
	if(it != class_scoped.end()) {
		return get<1>(it->second);
	}
	assert(false);
	return "NONE";
}

int SymbolTable::indexOf(const string& name) {
	auto it = subroutine_scoped.find(name);
	if(it != subroutine_scoped.end()) {
		return get<2>(it->second);
	} 
	it = class_scoped.find(name);
	if(it != class_scoped.end()) {
		return get<2>(it->second);
	}
	assert(false);
	return -1;
}
