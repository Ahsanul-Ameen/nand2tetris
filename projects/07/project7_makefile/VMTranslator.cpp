#include <bits/stdc++.h>
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
											


class Parser {
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
	
	void readFile() {
		
		for(string line; getline(in, line); ) {
			
			///############	IMPORTANT  ######################
			///if(!line.empty()) line.pop_back(); // remove newline in my PC
			
			if(line.empty() || line.find("//") != string::npos) continue;
		
			auto parse = split(line, " ");
			if(!parse.empty()) {
				commands.push(parse);
				//cout << parse << endl;
			}
		}
		
		//cout << commands.size() << endl;
	}
	
public:
	Parser(const string& file_path) {
		in.open(file_path);
		readFile();
		
		/*
		int i = 0;
		while(!commands.empty()) {
			cout << "instruction " << i++ << ": <" << commands.front() << ">" << endl;
			commands.pop(); // be careful
		}
		*/
		
		//cout << endl << endl;
		
	}
	
	bool hasMoreCommands() {
		return !commands.empty();
	}
	
	void advance() {
		assert(hasMoreCommands());
		current_command = commands.front();
		commands.pop();
		//cout << current_command << endl;
	}
	
	int commandType() {
		assert(!current_command.empty());
		string first = current_command.front();
		
		if(arithmetic.find(first) != arithmetic.end()) {
			return C_ARITHMETIC;
		} else if(first == "push") {
			return C_PUSH;
		} else if(first == "pop") {
			return C_POP;
		} else {
			//THere is so many 
			// but we've not implemented them yet
			return C_INVALID;
		}
	}
	
	string arg1() {
		int cmd = commandType();
		if(cmd == C_ARITHMETIC) {
			assert(current_command.size() == 1);
			return current_command[0];
		}
		else if(cmd != C_RETURN) {
			assert(current_command.size() >= 2);
			return current_command[1];
		}
		else return  "";
	}
	
	int arg2() {
		assert(current_command.size() > 2);
		int cmd = commandType();
		if(cmd == C_PUSH || cmd == C_POP || cmd == C_FUNCTION || cmd == C_CALL) {
			//return stoi(current_command[2]);
			stringstream ss(current_command[2]);
			int x;
			ss >> x;
			return x;
		} else return INT_MIN;
	}
	
	~Parser() {
		in.close();
	}
};


class CodeWriter {
	ofstream out;
	int instruction_id;
	string file_name;
	
		string getFileName(const string& s) {
		char sep = '/';
		#ifdef _WIN32
			sep = '\\';
		#endif
		size_t i = s.rfind(sep, s.length());
		if (i != string::npos) {
			string filename = s.substr(i+1, s.length() - i);
			size_t lastindex = filename.find_last_of("."); 
			string rawname = filename.substr(0, lastindex); 
			return(rawname);
		}

		return("");
	}

	//add / sub / and / or	
	void generateASAO(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"AM = M - 1\n"	// SP--
				"D = M\n"		// D = *SP
				"@SP\n"
				"AM = M - 1\n"	// SP--
				"M = M " + arithmetic[operation] + " D\n"	// compute
				"@SP\n"			
				"M = M + 1\n";		// SP++"
		out << code << endl;
	}
	
	//neg / not
	void generateNN(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"AM = M - 1\n"	// SP--
				"M = " + arithmetic[operation] + "M\n"	//*SP = -/!*SP
				"@SP\n"			
				"M = M + 1\n";		// SP++"
		out << code << endl;
	}
	
	//lt / eq / gt
	void generateLEG(const string& operation) {
		string code = "// arithmetic/logical " + operation + "\n"; 
		code +=	"@SP\n"
				"AM = M - 1\n"	// SP--
				"D = M\n"		// D = *SP
				"@SP\n"
				"AM = M - 1\n"	// SP--
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
		string variable = file_name + "." + i;
		  
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
		string variable = file_name + "." + i;
		code +=	"@SP\n"
				"M = M - 1\n"	// SP--
				"A = M\n"		// A = SP
				"D = M\n"		// D = *SP			
				"@" + variable + "\n"
				"M = D\n";		// static_i = *SP
		out << code << endl;
	}

	
	void generateEndLoop() {
		string code = "\n// END of program \n"; 
		code +=	"(ENDP)\n"
				"\t@ENDP\n"	
				"\t0;JMP\n";
		out << code << endl;
	}
	

	
	
	
	void writeArithmetic(const string& operation) { //(DONE)
		++instruction_id; 
		if(operation == "add" || operation == "sub" || operation == "and" || operation == "or") {
			generateASAO(operation);
		} else if(operation == "neg" || operation == "not") {
			generateNN(operation);
		} else if(operation == "lt" || operation == "eq" || operation == "gt") {
			generateLEG(operation);
		} else assert(false);
		
		
		
	}
	
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
	

	
public:
	CodeWriter(const string& file_path) {
		file_name = getFileName(file_path);
		out.open(file_path, ios::out | ios::trunc);
		instruction_id = 0;
	}
	
	void writeCode(const int& commandType, const string& arg1, int arg2 = -1) {
		//return;
		++instruction_id;
		if(commandType == C_ARITHMETIC) {
			writeArithmetic(arg1);
		} else if(commandType == C_PUSH || commandType == C_POP) {
			writePushPop(commandType, arg1, arg2);
		} else {
			cerr << "Instruction can't be processed" << endl;
		}
	}
	
	~CodeWriter() {
		generateEndLoop();
		out.close();
	}
};





int main(int argc, char** argv) {
    fast_io
    
    
	for(int i = 1; i < argc; ++i) {
		
		string input_file(argv[i]);
		string output_file = input_file;
		while(!output_file.empty() && output_file.back() != '.') output_file.pop_back();
		output_file += "asm";
		
		Parser parser(input_file);
		CodeWriter writer(output_file);
		
		
		while(parser.hasMoreCommands()) {
			int ctype = C_INVALID;
			string argument_1 = "";
			int argument_2 = INT_MIN;
			
				parser.advance();
			
			ctype = parser.commandType();
			//cout << ctype << " ";
			
			
			if(ctype != C_RETURN) {
				argument_1 = parser.arg1();
				//cout << argument_1 << " ";
			}
			
			if(ctype == C_PUSH || ctype == C_POP) {
				argument_2 = parser.arg2();
				//cout << argument_2;	
			}
			//cout << endl;
			
			writer.writeCode(ctype, argument_1, argument_2);
		}
    
	}
    
    
    
    return 0;
}

// g++ -pipe -std=c++2a -Wshadow -Wall -o "%e" "%f" -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -fconcepts -lm
