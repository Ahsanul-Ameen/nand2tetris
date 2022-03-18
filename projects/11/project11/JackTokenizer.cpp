#include <ctype.h>
#include "JackTokenizer.h"


// check if a keyword
bool is_keyword(const std::string& str) {
	return keyword_map.find(str) != keyword_map.end();
}

// check if a symbol
bool is_symbol(const std::string& str) {
	return symbol_map.find(str) != symbol_map.end();
}

// check if an integer constant
bool is_const_int(const std::string& str) {
	std::regex intrx("[0-9]{1,5}");
	return std::regex_match(str, intrx) && stoi(str) <= 32767;
}

// check if a string constant
bool is_const_string(const std::string& str) {
	std::regex stringrx("\"([^\"\\\\]|\\\\.)*\"");
	return std::regex_match(str, stringrx);
}

// check if an identifier
bool is_identifier(const std::string& str) {
	std::regex idrx("[a-zA-Z_][0-9a-zA-Z_]*");
	return std::regex_match(str, idrx);
}

JackTokenizer::JackTokenizer(const std::string& input_file_path) :
	input_file(std::ifstream(input_file_path)), current_indx(0), line_no(0)
{	
	//prev_indx.push({current_indx, current_token});
	std::stringstream str_stream;
	str_stream << input_file.rdbuf(); // read the file
	content = str_stream.str(); // content contains the whole file
	content = removeComments(content); // remove comments
}

std::string JackTokenizer::removeComments(std::string prgm) {
	int n = prgm.length();
	std::string clean_code;

	// flag to denote comment
	bool s_cmt = false, m_cmt = false;

	// traverse the given program
	for (int i = 0; i < n; ++i) {
		// if single line comment started, then check for end of it
		if (s_cmt == true && prgm[i] == '\n') {
			clean_code.push_back(prgm[i]);
			s_cmt = false;
		}
		// if multi line comment started, then check for end of it
		else if (m_cmt == true && prgm[i] == '*' && i + 1 < n && prgm[i + 1] == '/') {
			m_cmt = false;
			++i;
		}
		// if character is in comment, ignore it
		else if (s_cmt || m_cmt) continue;
		// check for beginning of comment and set appropriate flags
		else if (prgm[i] == '/' && i + 1 < n && prgm[i + 1] == '/') {
			s_cmt = true;
			++i;
		}
		else if (prgm[i] == '/' && i + 1 < n && prgm[i + 1] == '*') {
			m_cmt = true;
			++i;
		}
		// now it is guranteed that current character does not belongs to any comment
		else clean_code.push_back(prgm[i]);
	}
	return clean_code;
}

std::string JackTokenizer::getCurrentToken() {
	return this->current_token;
}

bool JackTokenizer::hasMoreTokens() {
	int cached_line = line_no;
	advance();
	bool flag = (tokenType() != ERR);
	backTrack();
	line_no = cached_line;
	return flag;
}

void JackTokenizer::advance() {
	using namespace std;
	prev_indx.push(make_pair(current_indx, current_token));	// cache current index

	auto character_left = [&]() {
		return current_indx < (int)content.size();
	};

	// gets the next token and make it current token
	string valid_token;
	// read a character, append it to the token and try validating
	while (character_left()) {
		if (valid_token.empty() && (content[current_indx] == '\n' || isspace(content[current_indx]))) {
			if (content[current_indx++] == '\n') ++line_no;
			continue;
		}
		valid_token.push_back(content[current_indx++]); // push the current character

		if (is_symbol(valid_token)) {	// so far so good
			//cout << "SYMBOL:	" << valid_token << endl;
			break;
		} else if (valid_token == "\"") {	// string starting from here
			while (character_left() && !is_const_string(valid_token)) {
				if (content[current_indx] == '\n') {
					assert(false); // error in jack program? string const can't contain newline
				}
				valid_token.push_back(content[current_indx++]);
			}
			
			//cout << "STRING_CONST:	" << valid_token << endl;
			break;
		} else if (is_const_int(valid_token)) {	// opportunity to enlarge
			while (character_left() && isdigit(content[current_indx]) && is_const_int(valid_token + content[current_indx])) {
				valid_token.push_back(content[current_indx++]);
			}
			//cout << "INT_CONST:		" << valid_token << endl;
			break;
		} else if (is_keyword(valid_token)) {	 // we're so luccy
			//cout << "KEYWORD:	" << valid_token << endl;
			break;
		} else if (is_identifier(valid_token)) {	// opportunity to enlarge as an identifier or keyword
			while (character_left() && is_identifier(valid_token + content[current_indx])) {
				valid_token.push_back(content[current_indx++]);
				if (is_keyword(valid_token)) {	// may encounter a keyword
					if(!character_left() || !is_identifier(valid_token + content[current_indx])) {
						//cout << "KEYWORD:	" << valid_token << endl;
						break;
					}
				} 
			}
			break;
		} else {
			cout << "******ERROR (invalid token):		|" << valid_token  << "|" << endl;
			current_indx = content.size();	// no more token will be parsed next
			system("pause");
			break;
		}
	}
	current_token = valid_token;
	//cout << current_token << endl;
}

Token JackTokenizer::tokenType() {
	if (is_keyword(current_token)) return KEYWORD;
	else if (is_symbol(current_token)) return SYMBOL;
	else if (is_const_int(current_token)) return INT_CONST;
	else if (is_const_string(current_token)) return STRING_CONST;
	else if (is_identifier(current_token)) return IDENTIFIER;
	else return ERR;
}

Keyword JackTokenizer::keyWord() {
	assert(tokenType() == KEYWORD);
	return keyword_map[current_token];
}

char JackTokenizer::symbol() {
	assert(tokenType() == SYMBOL);
	return symbol_map[current_token];
}

std::string JackTokenizer::identifier() {
	assert(tokenType() == IDENTIFIER);
	return current_token;
}

int JackTokenizer::intVal() {
	assert(tokenType() == INT_CONST);
	return stoi(current_token);
}

std::string JackTokenizer::stringVal() {
	assert(tokenType() == STRING_CONST);
	std::string str = current_token;
	str.erase(std::remove(str.begin(), str.end(), '\"'), str.end()); // removes double quotes
	return str;
}

void JackTokenizer::backTrack() {
	if (prev_indx.empty()) assert(false);

	current_indx = prev_indx.top().first;
	current_token = prev_indx.top().second;
	
	prev_indx.pop();
}

JackTokenizer::~JackTokenizer() {
	input_file.close();
}



//int main() {
//	JackTokenizer jack("D:\\Nand to Tetris\\nand2tetris\\projects\\10\\TEST\\Main.jack");
//
//	while (jack.hasMoreTokens()) {
//		jack.advance();
//		std::cout << jack.tokenType() << std::endl;
//	}
//
//	std::cin.get();
//}
