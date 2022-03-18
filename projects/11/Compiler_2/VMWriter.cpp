#include "VMWriter.h"
#include <cassert>


inline string getSegment(Segment segment) {
	if(segment == CONSTANT) return "constant";
	else if(segment == ARGUMENT) return "argument";
	else if(segment == LOCAL) return "local";
	else if(segment == STATIC) return "static";
	else if(segment == THIS) return "this";
	else if(segment == THAT) return "that";
	else if(segment == POINTER) return "pointer";
	else if(segment == TEMP) return "temp";
	else {
		assert(false);
		return "wtf!";
	}
}

inline string getCommand(Command command) {
	if(command == ADD) return "add";
	else if(command == SUB) return "sub";
	else if(command == NEG) return "neg";
	else if(command == EQ) return "eq";
	else if(command == GT) return "gt";
	else if(command == LT) return "lt";
	else if(command == AND) return "and";
	else if(command == OR) return "or";
	else if(command == NOT) return "not";
	else {
		assert(false);
		return "wtf!!";
	}
}


VMWriter::VMWriter(const string& out) : 
	output_file(ofstream(out)) {}


void VMWriter::writePush(Segment segment, int indx) {
	output_file << "push " << getSegment(segment) << " " << indx << endl;
}

void VMWriter::writePop(Segment segment, int indx) {
	output_file << "pop " << getSegment(segment) << " " << indx << endl;
}

void VMWriter::WriteArithmetic(Command command) {
	output_file << getCommand(command) << endl;
}

void VMWriter::WriteLabel(const string& label) {
	output_file << "label " << label << endl;
}

void VMWriter::WriteGoto(const string& label) {
	output_file << "goto " << label << endl;
}

void VMWriter::WriteIf(const string& label) {
	output_file << "if-goto " << label << endl;
}

void VMWriter::writeCall(const string& name, const int& nArgs) {
	output_file << "call " << name << " " << nArgs << endl;
}

void VMWriter::writeFunction(const string& name, const int& nLocals) {
	output_file << "function " << name << " " << nLocals << endl;
}

void VMWriter::writeReturn() {
	output_file << "return" << endl;
}

void VMWriter::close() {
	output_file.close();
}
