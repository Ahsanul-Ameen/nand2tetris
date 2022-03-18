#include "Parser.hpp"


string Parser::cleanUp(string prgm) {
	int n = prgm.length();
	string clean_code;
	// flag to denote comment
	bool s_cmt = false;

	// traverse the given program
	for (int i = 0; i < n; ++i) {
		// if single line comment started, then check for end of it
		if (s_cmt == true && prgm[i] == '\n') {
			clean_code.push_back(prgm[i]);
			s_cmt = false;
		}
		// if character is in comment, ignore it
		else if (s_cmt) continue;
		// check for beginning of comment and set appropriate flags
		else if (prgm[i] == '/' && i + 1 < n && prgm[i + 1] == '/') {
			s_cmt = true;
			++i;
		}
		// now it is guranteed that current character does not belongs to any comment
		else if(prgm[i] == '\n' || !isspace(prgm[i])) {
			clean_code.push_back(prgm[i]);
			// if label then add necessary newline for assembly code
			if(prgm[i] == ')' && i+1 < n && prgm[i+1] != '\n') {
				clean_code.push_back('\n');
			}
		}
	}
	return clean_code;
}


Parser::Parser(string const& input_file_path) :
	in_file(ifstream(input_file_path)), current_indx(0)
{
	stringstream ss;
	ss << in_file.rdbuf(); 				// read the whole file
	string clean_code = cleanUp(ss.str());
	
	//std::cout << clean_code << std::endl;
	
	istringstream iss(clean_code);
    string instruction;    
    
    while (std::getline(iss, instruction)) {
		//std::cout << "|" << instruction << "|" << std::endl;
        if(!instruction.empty()) {
			//std::cout << "|" << instruction << "|" << std::endl;
			content.push_back(instruction);
		}
    }
    
    /*
    for(int i = 0; i < (int)content.size(); ++i) {
		std::cout << "|" << content[i] << "|" << std::endl;
	}
	*/
}


bool Parser::hasMoreCommands() { return current_indx < (int)content.size(); }


void Parser::advance() { 
	if(hasMoreCommands()) {
		current_command = content[current_indx++];
	}
}


Command Parser::commandType() {
	if(current_command.front() == '@') return A_COMMAND;
	else if(current_command.front() == '(') return L_COMMAND;
	else return C_COMMAND;
}


string Parser::getCurrentToken() {
	return this->current_command;
}


string Parser::symbol() {
	if(commandType() == A_COMMAND) 
		return current_command.substr(1, current_command.size()-1);	
	else if(commandType() == L_COMMAND) 
		return current_command.substr(1, current_command.size()-2);
	else {
		std::cout << "Error in Parser::symbol()" << std::endl;
		return "";
	}
}


string Parser::dest() {
	if(commandType() == C_COMMAND) {
		auto npos = current_command.find("=");
		if(npos == string::npos) {
			return "null";
		} else {
			return current_command.substr(0, npos);
		}
	} else {
		std::cout << "Error in Parser::dest()" << std::endl;
		return "";
	}
}


string Parser::comp() {
	if(commandType() == C_COMMAND) {
		string str = current_command;
		auto npos1 = str.find(";");
		if(npos1 != string::npos) {	
			str = str.substr(0, npos1);
		}
		auto npos2 = str.find("=");
		if(npos2 != string::npos) {	
			str = str.substr(npos2 + 1);
		} 
		return str;
	} else {
		std::cout << "Error in Parser::comp()" << std::endl;
		return "";
	}
}


string Parser::jump() {
	if(commandType() == C_COMMAND) {
		auto npos = current_command.find(";");
		if(npos == string::npos) {
			return "null";
		} else {
			return current_command.substr(npos + 1);
		}
	} else {
		std::cout << "Error in Parser::jump()" << std::endl;
		return "";
	}
}


Parser::~Parser() {
	in_file.close();
}
