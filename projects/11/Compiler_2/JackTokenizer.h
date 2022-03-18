#pragma once

#include <string>
#include <fstream>	
#include <sstream>
#include <unordered_map>
#include <regex>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>


enum Token {
	KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST, ERR
};

enum Keyword {
	CLASS_KEY, METHOD_KEY, FUNCTION_KEY, CONSTRUCTOR_KEY,
	INT_KEY, BOOLEAN_KEY, CHAR_KEY, VOID_KEY,
	VAR_KEY, STATIC_KEY, FIELD_KEY, LET_KEY,
	DO_KEY, IF_KEY, ELSE_KEY, WHILE_KEY, RETURN_KEY,
	TRUE_KEY, FALSE_KEY, NULL_KEY, THIS_KEY
};

// priority 1
static std::unordered_map<std::string, Keyword> keyword_map {
	{ "class", CLASS_KEY},
	{ "method", METHOD_KEY },
	{ "function", FUNCTION_KEY },
	{ "constructor", CONSTRUCTOR_KEY },
	{ "int", INT_KEY },
	{ "boolean", BOOLEAN_KEY },
	{ "char", CHAR_KEY },
	{ "void", VOID_KEY },
	{ "var", VAR_KEY },
	{ "static", STATIC_KEY },
	{ "field", FIELD_KEY },
	{ "let", LET_KEY },
	{ "do", DO_KEY },
	{ "if", IF_KEY },
	{ "else", ELSE_KEY },
	{ "while", WHILE_KEY },
	{ "return", RETURN_KEY },
	{ "true", TRUE_KEY },
	{ "false", FALSE_KEY },
	{ "null", NULL_KEY },	/* Modified */
	{ "this", THIS_KEY}
};

// priority 2
static std::unordered_map<std::string, char> symbol_map {
	{"{", '{'},
	{"}", '}'},
	{"(", '('},
	{")", ')'},
	{"[", '['},
	{"]", ']'},
	{".", '.'},
	{",", ','},
	{";", ';'},
	{"+", '+'},
	{"-", '-'},
	{"*", '*'},
	{"/", '/'},	/** Check Out! */
	{"&", '&'},
	{"|", '|'},
	{"<", '<'},
	{">", '>'},
	{"=", '='},
	{"~", '~'}
};

// check if a keyword
bool is_keyword(const std::string& str);

// check if a symbol
bool is_symbol(const std::string& str);

// check if an integer constant
bool is_const_int(const std::string& str);

// check if a string constant
bool is_const_string(const std::string& str);

// check if an identifier
bool is_identifier(const std::string& str);



class JackTokenizer {
	std::ifstream input_file;
	std::string current_token;
	std::string content;
	int current_indx;
	std::stack<std::pair<int, std::string>>	prev_indx;
	int line_no;

	std::string removeComments(std::string prgm);
public:
	JackTokenizer(const std::string& input_file_path);

	std::string getCurrentToken();
	bool hasMoreTokens();
	void advance();
	Token tokenType();

	Keyword keyWord();
	char symbol();
	std::string identifier();
	int intVal();
	std::string stringVal();

	void backTrack();
	~JackTokenizer();
};
