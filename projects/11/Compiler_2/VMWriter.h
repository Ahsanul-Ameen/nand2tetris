#pragma once

#include <fstream>
#include <string>

using std::ofstream;
using std::string;
using std::endl;


enum Segment {
	CONSTANT, ARGUMENT, LOCAL, STATIC, THIS, THAT, POINTER, TEMP
};

enum Command {
	ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT
};


class VMWriter {
private:
	std::ofstream output_file;
public:
	//	Creates a new file and prepares it for writing VM commands
	VMWriter(const string& out);
	
	//	Writes a VM push command
	void writePush(Segment segment, int indx);
	
	//	Writes a VM pop command
	void writePop(Segment segment, int indx);
	
	//	Writes a VM arithmetic command
	void WriteArithmetic(Command command);
	
	//	Writes a VM label command
	void WriteLabel(const string& label);
	
	//	Writes a VM goto command
	void WriteGoto(const string& label);
	
	//	Writes a VM If-goto command
	void WriteIf(const string& label);
	
	//	Writes a VM call command
	void writeCall(const string& name, const int& nArgs);
	
	//	Writes a VM function command
	void writeFunction(const string& name, const int& nLocals);
	
	//	Writes a VM return command
	void writeReturn();
	
	//	Closes the output file
	void close();
};
