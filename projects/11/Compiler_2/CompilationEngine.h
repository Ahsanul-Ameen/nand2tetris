#pragma once

#include <iostream>
#include <fstream>
#include "JackTokenizer.h"
#include "SymbolTable.h"
#include "VMWriter.h"


class CompilationEngine {
private:
	std::ifstream input_file;
	std::ofstream output_file;
	JackTokenizer tokenizer;
	SymbolTable symbol_table;
	VMWriter vmwriter;
	std::string	indentation;
	std::string class_name;
	std::string function_name;
	std::string subroutine_type;

	void logStart(const std::string& str);

	void logMid(const std::string& str);

	void logEnd(const std::string& str);

	bool eatToken(Token TOK);
	bool eatSymbol(char ch);
	bool eatKey(Keyword KEY);
	bool eatIdentifier();
	bool eatType();
	bool eatOp();
	bool eatUnaryOp();
	bool eatKeyWordConst();
	void subroutineCall();
	bool canExpression();
	bool canTerm();
public:

	//creates a new compilation engine with
	//the given input and output.The next
	//method called must be
	//compileClass().
	CompilationEngine(const std::string& in, const std::string& out);

	//	compiles a complete class.
	void CompileClass();

	//	compiles a static declaration or a field declaration.
	void CompileClassVarDec();

	//	compiles a complete method, function, or constructor.
	void CompileSubroutineDec();

	//	compiles a (possibly empty) parameter list, not including the enclosing “()”.
	void compileParameterList();

	// Compiles a subRoutine's body
	void compileSubroutineBody();
	
	//	compiles a var declaration.
	void compileVarDec();

	//	compiles a sequence of statements, not including the enclosing “{}”.
	void compileStatements();

	//	Compiles a do statement
	void compileDo();

	// Compiles a let statement
	void compileLet();

	//	Compiles a while statement
	void compileWhile();

	//	Compiles a return statement
	void compileReturn();

	//	compiles an if statement, possibly with a trailing else clause.
	void compileIf();

	//	compiles an expression.
	bool CompileExpression();	// intentionally made bool return type

	//	compiles a term. Needs extra lookahead token in case of identifiers...
	void CompileTerm();	// intentionally made bool return type

	//	compiles a (possibly empty) comma-separated list of expressions.
	//  returns number of expressions as argument 
	int CompileExpressionList();

	//	destructs
	~CompilationEngine();
};
