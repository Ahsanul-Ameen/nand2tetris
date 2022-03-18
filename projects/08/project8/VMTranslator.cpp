#include<bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
using namespace std;



using ll = long long;
using pii = pair<int, int>;

#define     endl               '\n'
#define     fast_io            ios::sync_with_stdio(false); cin.tie(0);
#define     all(x)             begin(x), end(x)
#define     debug(x)           cerr <<"Line "<< __LINE__ <<" : "<< #x " = "<< x <<endl;
 
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T, TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T> &t) { for(auto& i: t) os<<i<<" "; return os; }


bool popLast = false;
bool isDir = false;

enum {C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL, C_INVALID};
unordered_map<string, string> arithmetic = 	{
												{"add", "+"}, 
												{"sub", "-"}, 
												{"or", "|"}, 
												{"and", "&"}, 
												{"neg", "-"}, 
												{"not", "!"}, 
												{"eq", "JEQ"}, 
												{"gt", "JGT"}, 
												{"lt", "JLT"}
											}; 
unordered_map<string, string> segments = 	{
												{"local", "LCL"}, 
												{"argument", "ARG"}, 
												{"this", "THIS"}, 
												{"that", "THAT"}, 
											};										
											


string filename(string path) {
	// Remove directory if present.
	// Do this before extension removal incase directory has a period character.
	const size_t last_slash_idx = path.find_last_of("\\/");
	if (string::npos != last_slash_idx) {
		path.erase(0, last_slash_idx + 1);
	}
	return path;
}

string stem(string path) {
	path = filename(path);
	// Remove extension if present.
	const size_t period_idx = path.rfind('.');
	if (string::npos != period_idx) {
		path.erase(period_idx);
	}
	return path;
}



class Parser {
	string parsed_file;
	ifstream in;
	queue<vector<string>> commands;
	vector<string> current_command;
	
	vector<string> split (const string& s, const string& delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		string token;
		vector<string> res;

		while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
			token = s.substr (pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back (token);
		}

		res.push_back (s.substr (pos_start));
		return res;
	}
	
	// UPDATABLE
	void readFile() {
		for(string line; getline(in, line); ) {
			if(popLast && !line.empty()) line.pop_back(); 
			
			if(line.empty() || line.rfind("//", 0) == 0) continue;
		
			auto parse = split(line, " ");
			if(!parse.empty()) {
				commands.push(parse);
			}
		}
		
		//cout << commands.size() << endl;
	}
	
public:
	Parser(const string& file_path) {
		parsed_file = stem(file_path);
		in.open(file_path);
		readFile();
	}
	
	string getFileName() { return parsed_file; }
	
	bool hasMoreCommands() { return !commands.empty(); }
	
	void advance() {
		assert(hasMoreCommands());
		current_command = commands.front();
		commands.pop();
		//cout << current_command << endl;
	}
	
	int commandType() {
		assert(!current_command.empty());
		string first = current_command.front();
		
		if (arithmetic.find(first) != arithmetic.end()) return C_ARITHMETIC;
		else if (first == "push") return C_PUSH;
		else if (first == "pop") return C_POP;
		else if (first == "label") return C_LABEL;
		else if (first == "goto") return C_GOTO;
		else if (first == "if-goto") return C_IF;
		else if (first == "function") return C_FUNCTION;
		else if (first == "call") return C_CALL;
		else if (first == "return") return C_RETURN;
		else {
			cerr << "C_INVALID" << " command: " << current_command << endl;
			return C_INVALID;
		}
	}
	
	string arg1() {
		int cmd = commandType();
		assert(cmd != C_INVALID && cmd != C_RETURN);
		
		if(cmd == C_ARITHMETIC) {
			assert(current_command.size() >= 1);
			return current_command[0];
		}
		else {
			assert(current_command.size() >= 2);
			return current_command[1];
		}
	}
	
	int arg2() {
		//if(current_command.size() != 3) cout << "|" << current_command << "| " << current_command.size() << endl;
		assert(current_command.size() >= 3);
		const int cmd = commandType();
		if (cmd == C_PUSH || cmd == C_POP || cmd == C_FUNCTION || cmd == C_CALL) {
			return stoi(current_command[2]);
		} else {
			cerr << "Invalid call for parser.arg2()" << endl;
			return 0;
		}
	}
	
	~Parser() {
		in.close();
	}
};


class CodeWriter {
	ofstream out;
	int instruction_id, file_id;
	string output_file_name;
	string input_file_name;
	string current_function;
	
	string getFileName(const string& path_string) {
		return filename(path_string);
	}
	
	// DONE
	void writeInit() {
		out << "//Bootstrap code" << endl;
		out << "@256" << endl;
		out << "D = A" << endl;
		out << "@SP" << endl;
		out << "M = D" << endl;
		
		writeCall("Sys.init", 0);
	}
	
	//add / sub / and / or	
	void generateASAO(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"
				"D = M\n"		// D = *SP
				"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"
				"M = M " + arithmetic[operation] + " D\n"	// compute
				"@SP\n"			
				"M = M + 1\n";		// SP++"
		out << code << endl;
	}
	
	//neg / not
	void generateNN(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"
				"M = " + arithmetic[operation] + "M\n"	//*SP = -/!*SP
				"@SP\n"			
				"M = M + 1\n";		// SP++"
		out << code << endl;
	}
	
	//lt / eq / gt
	void generateLEG(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"
				"D = M\n"		// D = *SP
				"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"
				"D = M - D\n"
				"@TRUE_" + to_string(instruction_id) + "\n"
				"D;" + arithmetic[operation] + "\n"			// D;JGT/JE/JLT
				"(FALSE_" + to_string(instruction_id) + ")\n"
				"\t@SP\n"
				"\tA = M\n"
				"\tM = 0\n"			//*SP = false
				"\t@END_" + to_string(instruction_id) + "\n"
				"\t0;JMP\n"			// jump to end_i
				"(TRUE_" + to_string(instruction_id) + ")\n"
				"\t@SP\n"
				"\tA = M\n"
				"\tM = -1\n"		// *SP = true
				"(END_" + to_string(instruction_id) + ")\n"
				"@SP\n"
				"M = M + 1\n";		// SP++
				
		out << code << endl;
	}
	
	
	void generatePushConstant(const string& i) {
		string code = "// push constant " + i + "\n"; 
		code +=	"@" + i + "\n"
				"D = A\n" // D = i
				"@SP\n"			
				"A = M\n"		
				"M = D\n"	// *SP = D = i"
				"@SP\n"		
				"M = M + 1\n";	// SP++"
		out << code << endl;
	}
	
	void generatePushSegment(const string& segment, const string& i) {
		string code = "// push " + segment + " " + i + "\n"; 
		code +=	"@" + segments[segment] + "\n"
				"D = M\n" 	// D = base_address
				"@" + i + "\n"		
				"A = D + A\n"	// A = RAM[addr] + i	
				"D = M\n"		// D = *addr
				"@SP\n"
				"A = M\n"
				"M = D\n"	// *SP = *addr
				"@SP\n"
				"M = M + 1\n";	// SP++
		out << code << endl;
	}
	
	void generatePushTemp(const string& i) {
		string code = "// push temp " + i + "\n"; 
		code +=	"@5\n"
				"D = A\n" 	// D = 5
				"@" + i + "\n"		
				"A = D + A\n"	// A = 5 + i
				"D = M\n"		// D = *temp_i
				"@SP\n"
				"A = M\n"
				"M = D\n"	// *SP = *temp_i
				"@SP\n"
				"M = M + 1\n";	// SP++
		out << code << endl;
	}	
	
	void generatePushPointer(const string& i) {
		string code = "// push pointer " + i + "\n";
		string pointer;
		if(i == "0") pointer = "THIS";
		else if(i == "1") pointer = "THAT";
		else assert(false);
		  
		code +=	"@" + pointer + "\n"
				"D = M\n" 	// D = THIS/THAT
				"@SP\n"
				"A = M\n"
				"M = D\n"	// *SP = D
				"@SP\n"
				"M = M + 1\n";	// SP++
		out << code << endl;
	}	
	
	void generatePushStatic(const string& i) {
		string code = "// push static " + i + "\n";
		//cout << input_file_name << " | " << output_file_name << endl;
		string variable = input_file_name + "." + i;	// separate static file for each input file
		  
		code +=	"@" + variable + "\n"
				"D = M\n" 	// D = static i
				"@SP\n"
				"A = M\n"
				"M = D\n"	// *SP = D
				"@SP\n"
				"M = M + 1\n";	// SP++
		out << code << endl;
	}
	
	void generatePopSegment(const string& segment, const string& i) {
		string code = "// pop " + segment + " " + i + "\n"; 
		code +=	"@" + segments[segment] + "\n"
				"D = M\n" 	// D = base_address
				"@" + i + "\n"		
				"D = D + A\n"		
				"@R13\n"
				"M = D\n"	// R13 = segmentPointer + i
				"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"			// A = SP
				"D = M\n"		// D = *SP			
				"@R13\n"
				"A = M\n"
				"M = D\n";		// *addr = *SP
		out << code << endl;
	}
	
	void generatePopTemp(const string& i) {
		string code = "// pop temp " + i + "\n"; 
		code +=	"@5\n"
				"D = A\n" 
				"@" + i + "\n"		
				"D = D + A\n"		
				"@R13\n"
				"M = D\n"	// R13 = 5 + i
				"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"		// A = SP
				"D = M\n"		// D = *SP			
				"@R13\n"
				"A = M\n"
				"M = D\n";		// *addr = *SP
		out << code << endl;
	}
	
	void generatePopPointer(const string& i) {
		
		string pointer;
		if(i == "0") pointer = "THIS";
		else if(i == "1") pointer = "THAT";
		else assert(false);
		
		string code = "// pop pointer " + i + "\n"; 
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"		// A = SP
				"D = M\n"		// D = *SP			
				"@" + pointer + "\n"
				"M = D\n";		// THIS/THAT = *SP
		out << code << endl;
	}
	
	void generatePopStatic(const string& i) {
		string code = "// pop static " + i + "\n";
		string variable = input_file_name + "." + i;
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"		// A = SP
				"D = M\n"		// D = *SP			
				"@" + variable + "\n"
				"M = D\n";		// static_i = *SP
		out << code << endl;
	}

	// DONE
	void writeArithmetic(const string& operation) { 
		if(operation == "add" || operation == "sub" || operation == "and" || operation == "or") {
			generateASAO(operation);
		} else if(operation == "neg" || operation == "not") {
			generateNN(operation);
		} else if(operation == "lt" || operation == "eq" || operation == "gt") {
			generateLEG(operation);
		} else assert(false);
		
		
		
	}
	
	// DONE
	void writePushPop(const int& command, const string& segment, const int& index) {
		if(command == C_PUSH) {
			if(segment == "constant") generatePushConstant(to_string(index));
			else if(segments.count(segment)) generatePushSegment(segment, to_string(index));
			else if(segment == "temp") generatePushTemp(to_string(index));
			else if(segment == "pointer") generatePushPointer(to_string(index));
			else if(segment == "static") generatePushStatic(to_string(index));
		} else if(command == C_POP) {
			if(segments.count(segment)) generatePopSegment(segment, to_string(index));
			else if(segment == "temp") generatePopTemp(to_string(index));
			else if(segment == "pointer") generatePopPointer(to_string(index));
			else if(segment == "static") generatePopStatic(to_string(index));
		} else assert(false);
	}
	
	// DONE
	void writeLabel(const string& label) {
		/*Writes the assembly code that is the
		translation of the given label command.*/
		//Xxx.foo$bar
		string code = "// generating label ... \n"; 
		code +=	"(" + label + ")\n";
		out << code << endl;
	}
	
	// DONE
	void writeGoto (const string& label) {
		/*Writes the assembly code that is the
		translation of the given goto command.*/
		string code =	"@" + label + "\t// goto label\n";
			   code += "0;JMP\n";
		out << code<< endl;
	}
	
	// DONE
	void writeIf (const string& label) { 
		string code = "@SP \t// if-goto label\n";
			   code += "M = M-1\n"; // --SP
			   code += "A = M\n";	// A = M
			   code += "D = M\n"; 	// D = *SP
			   code +=	"@" + label + "\n"; 
			   code += "D;JNE\n";	// if *SP != 0 then goto label
		out << code<< endl;
	}
	
	// TODO
	void writeCall (const string& functionName, const int& numArgs) {

		static int i = 1; 
		
		string ret_addr = current_function + "$ret." + to_string(i);	 
	 
		string code = "// call " + functionName + " " + to_string(numArgs) + "\n";
		// push retAddrLabel	(Using a translator-generated label) 
		code +=	"@" + ret_addr + "\t// push retAddrLabel\n"	
				"D = A\n" 	
				"@SP\n"			
				"A = M\n"		
				"M = D\n"
				"@SP\n"		
				"M = M + 1\n";	
		// push LCL 	(Saves LCL of the called)		
		code +=	"@LCL\t// push LCL\n"
				"D = M\n" 
				"@SP\n"			
				"A = M\n"		
				"M = D\n"
				"@SP\n"		
				"M = M + 1\n";			
		//	push ARG 	(Saves ARG of the caller)		
		code +=	"@ARG\t// push ARG\n"	
				"D = M\n" 
				"@SP\n"			
				"A = M\n"		
				"M = D\n"	
				"@SP\n"		
				"M = M + 1\n";	
		//	push THIS	(Saves THIS of the caller)		
		code +=	"@THIS\t// push THIS\n"		 
				"D = M\n" 
				"@SP\n"			
				"A = M\n"		
				"M = D\n"	
				"@SP\n"		
				"M = M + 1\n";		
		//	push THAT	(Saves THAT of the caller)		
		code +=	"@THAT\t// push THAT\n"
				"D = M\n" 
				"@SP\n"			
				"A = M\n"		
				"M = D\n"	
				"@SP\n"		
				"M = M + 1\n";						
		//	ARG = SP-5-nArgs	(Repositions ARG)
		code += "@SP\t// ARG = SP - 5 - nArgs\n"
				"D = M\n"	
				"@5\n"	
				"D = D - A\n"	
				"@" + to_string(numArgs) + "\n"
				"D = D - A\n"
				"@ARG\n"
				"M = D\n";	
		//	LCL = SP	(Repositions LCL)
		code += "@SP\t// LCL = SP\n"
				"D = M\n"
				"@LCL\n"
				"M = D\n";
		out << code << endl;
		//	goto functionName	(Transfers control to the called functiion)
		writeGoto(functionName);
		//(fileName.functionName$ret.i) 	the same translator generated label
		writeLabel(ret_addr);
		
		// increment running call id
		++i;
	}
	
	// TODO
	void writeReturn () {
		/*Writes the assembly code that is the
		translation of the given Return command.*/
		string code = "// return\n"; 
		//	endFrame = LCL 		(endFrame is a temporary variable)
		code += "@LCL\t//	endFrame = LCL\n"
				"D = M\n"
				"@endFrame\n"
				"M = D\n";
		// retAddr = *(endFrame - 5)	(gets the return address)
		code += "@endFrame\t//	retAddr = *(endFrame - 5)\n"
				"D = M\n"
				"@5\n"
				"A = D - A\n"
				"D = M\n"
				"@retAddr\n"
				"M = D\n";
		out << code << "// *ARG = pop()\n";
		// *ARG = pop()			(repositions the return value for the caller)
		generatePopSegment("argument", "0");
		//	SP = ARG + 1		(repositions SP of the caller)
		code = 	"@ARG\t//	SP = ARG + 1\n"
				"D = M + 1\n"
				"@SP\n"
				"M = D\n";
		// THAT = *(endFrame - 1)	(restores THAT of the caller)
		code +=	"@endFrame\t// THAT = *(endFrame - 1)\n"
				"D = M\n"
				"@1\n"
				"A = D - A\n"
				"D = M\n"
				"@THAT\n"
				"M = D\n";
		// THIS = *(endFrame - 2)	(restores THIS of the caller)
		code +=	"@endFrame\t// THIS = *(endFrame - 2)\n"
				"D = M\n"
				"@2\n"
				"A = D - A\n"
				"D = M\n"
				"@THIS\n"
				"M = D\n";		
		// ARG = *(endFrame - 3)	(restores ARG of the caller)
		code +=	"@endFrame\t// ARG = *(endFrame - 3)\n"
				"D = M\n"
				"@3\n"
				"A = D - A\n"
				"D = M\n"
				"@ARG\n"
				"M = D\n";		
		// LCL = *(endFrame - 4)	(restores LCL of the caller)
		code +=	"@endFrame\t// LCL = *(endFrame - 4)\n"
				"D = M\n"
				"@4\n"
				"A = D - A\n"
				"D = M\n"
				"@LCL\n"
				"M = D\n";		
		// goto retAddr				(goes to the caller's return address)		
		code += "@retAddr\t// goto retAddr\n"		
				"A = M\n"
				"0;JMP\n";
		out << code << endl;
	}
	
	// TODO
	void writeFunction (const string& functionName, const int& numLocals) {
		current_function = functionName;
		out << "// function " + functionName + " " + to_string(numLocals) + "\n";
		writeLabel(functionName);
		for(int i = 1; i <= numLocals; ++i) {
			generatePushConstant("0");
		}
	}
	
	// DONE
	void generateEndLoop() {
		string code = "\n// END of all program \n"; 
		code +=	"(ENDP)\n"
				"\t@ENDP\n"	
				"\t0;JMP\n";
		out << code << endl;
	}
	
public:
	CodeWriter(const string& file_path) {
		output_file_name = getFileName(file_path);
		out.open(file_path, ios::out | ios::trunc);
		instruction_id = 0;
		file_id = 0;
		
		if (isDir) writeInit(); // Bootstrap code
	}
	
	
	void updateFileID() { ++file_id; }
	
	void updateInputFileName(string parsed_file) { input_file_name = parsed_file; }
	
	void writeCode(const int& commandType, const string& arg1, int arg2 = -1) {
		//cout << commandType << " " << arg1 << " " << arg2 << endl;
		++instruction_id; // we don't prevents its increment
		if (commandType == C_ARITHMETIC) {
			writeArithmetic(arg1);
		} else if (commandType == C_PUSH || commandType == C_POP) {
			writePushPop(commandType, arg1, arg2);
		} else if (commandType == C_LABEL) {
			writeLabel(input_file_name + "." + arg1);	
		} else if (commandType == C_GOTO) {
			writeGoto(input_file_name + "." + arg1);
		} else if (commandType == C_IF) {
			writeIf(input_file_name + "." + arg1);
		} else if (commandType == C_CALL) {
			writeCall(arg1, arg2);
		} else if (commandType == C_RETURN) {
			writeReturn();
		} else if (commandType == C_FUNCTION) {
			writeFunction(arg1, arg2);
		} else {
			cerr << "@ERROR: Instruction can't be processed...." << endl;
		}
	}
	
	~CodeWriter() {
		//generateEndLoop();
		out.close();
	}
};



void generateCode(Parser& parser, CodeWriter& writer) {
	writer.updateFileID();
	writer.updateInputFileName(parser.getFileName());
	writer.updateInputFileName(parser.getFileName());
	
	while(parser.hasMoreCommands()) {
		int ctype = C_INVALID;	
		string argument_1 = "";
		int argument_2 = INT_MIN;
		
		parser.advance();
		ctype = parser.commandType();
		
		if(ctype != C_RETURN) argument_1 = parser.arg1();
		if(ctype == C_PUSH || ctype == C_POP || ctype == C_FUNCTION || ctype == C_CALL) argument_2 = parser.arg2();
				
		writer.writeCode(ctype, argument_1, argument_2);
	}
}


int is_regular_file(const string& path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
}

string file_to_file(string path_string) {
	return path_string.substr(0,path_string.find_last_of('.')) + ".asm";
}

string dir_to_file(string path_string) {
	// in has a trailing '/', removing it:	
	if(!path_string.empty() && path_string.back() == '/') path_string.pop_back();
	// Extracting the last directory name:
	size_t slash = path_string.find_last_of("/");
	string temp = path_string.substr(slash+1, std::string::npos);
	return path_string + "/" + temp + ".asm";
}


vector<string> files_in_dir(string path_string) {
	if(!path_string.empty() && path_string.back() != '/') path_string.push_back('/');
	DIR *dir;
	struct dirent *entry;
	vector<string> v;
	
	if ((dir = opendir(path_string.c_str())) != nullptr) {
	// Scanning directory contents looking for .vm files...
  		while ((entry = readdir(dir)) != NULL) {
  			string entry_name = entry->d_name;
  			if (entry_name.find(".vm") != string::npos) {
  				string file_path = path_string;
  				file_path.append(entry_name); // path/file.vm
  				v.push_back(file_path);  // ... and adding them to vm_files.
   			}
  		}		
   		closedir(dir); 
   		return v;
  	}
	else {
  		cerr << "Error opening directory." << endl;
  		exit(-1);
	}
}



int main(int argc, char** argv) {
    fast_io
    
    popLast = false;
    
    
	for(int i = 1; i < argc; ++i) {
		string path_string(argv[i]);
		
		if (!is_regular_file(path_string)) { 
			isDir = true;
			string output_file = dir_to_file(path_string);
			CodeWriter writer(output_file);
			
			auto vm_files = files_in_dir(path_string);
			
			for(const auto& item : vm_files) {
				Parser parser(item);
				generateCode(parser, writer);
			}
			
		} else if(is_regular_file(path_string) == 1) {	
			isDir = false;
			Parser parser(path_string);
			string output_file = file_to_file(path_string);	
			CodeWriter writer(output_file);	
			generateCode(parser, writer);
		} 
		
	}
    
    
    
    return 0;
}
