#include "CompilationEngine.h"


void CompilationEngine::logStart(const std::string& str) {
	output_file << indentation << "<" << str << ">" << std::endl;
}

void CompilationEngine::logMid(const std::string& str) {
	std::string token = tokenizer.getCurrentToken();
	if (tokenizer.tokenType() == STRING_CONST) {
		token = token.substr(1, token.length() - 2);
	}
	if (token == "<") token = "&lt;";
	else if (token == ">") token = "&gt;";
	else if (token == "&") token = "&amp;";
	output_file << indentation << "<" << str << "> " << token << " </" << str << ">" << std::endl;
}

void CompilationEngine::logEnd(const std::string& str) {
	output_file << indentation << "</" << str << ">" << std::endl;
}

bool CompilationEngine::eatToken(Token TOK) {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == TOK) {
		// token matched
		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatIdentifier() {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == IDENTIFIER) {
		// identifier matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatKey(Keyword KEY) {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == KEYWORD && tokenizer.keyWord() == KEY) {
		// keyword matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatSymbol(char ch) {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == SYMBOL && tokenizer.symbol() == ch) {
		// symbol matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatType() {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if ((tokenizer.tokenType() == KEYWORD &&
		(tokenizer.keyWord() == INT_KEY || 
		tokenizer.keyWord() == CHAR_KEY || 
		tokenizer.keyWord() == BOOLEAN_KEY)) || 
		(tokenizer.tokenType() == IDENTIFIER)) {
		// type matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}

}

bool CompilationEngine::eatOp() {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == SYMBOL && (
		tokenizer.symbol() == '+' ||
		tokenizer.symbol() == '-' || 
		tokenizer.symbol() == '*' ||
		tokenizer.symbol() == '/' ||	/*check out please*/
		tokenizer.symbol() == '&' || 
		tokenizer.symbol() == '|' || 
		tokenizer.symbol() == '<' || 
		tokenizer.symbol() == '>' || 
		tokenizer.symbol() == '=')) {
		// op matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatUnaryOp() {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == SYMBOL && (
		tokenizer.symbol() == '-' ||
		tokenizer.symbol() == '~')) {
		// unaryOp matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

bool CompilationEngine::eatKeyWordConst() {
	if (!tokenizer.hasMoreTokens()) return false;
	tokenizer.advance();
	if (tokenizer.tokenType() == KEYWORD && (
		tokenizer.keyWord() == TRUE_KEY ||
		tokenizer.keyWord() == FALSE_KEY || 
		tokenizer.keyWord() == NULL_KEY || 
		tokenizer.keyWord() == THIS_KEY)) {
		// keywordConstant matched

		return true;
	}
	else {
		tokenizer.backTrack();
		return false;
	}
}

// coded up
void CompilationEngine::subroutineCall() {
	//	subroutineName '(' expressionList ')' | ( className | varName) '.' subroutineName '(' expressionList ')'
	std::string name, type, caleeName;
	Kind kind;
	int nArgs = 0, indx;
	if (eatIdentifier()) {
		//	subroutineName		matched	or	className|varName	matched
		logMid("identifier");
		caleeName = tokenizer.getCurrentToken();
		if (eatSymbol('(')) {
			//	(	matched
			logMid("symbol");
			vmwriter.writePush(POINTER, 0);
			++nArgs;	// as we're calling a method with this;
			nArgs += CompileExpressionList();	// expressionList	matched
			if (eatSymbol(')')) {
				//	)	matched
				logMid("symbol");
				caleeName = class_name + "." + caleeName;
				// now call
				vmwriter.writeCall(caleeName, nArgs);
			}
			else assert(false);
		}
		else if (eatSymbol('.')) {	//	className | varName	matched actually
			//	.	matched
			logMid("symbol");
			name = caleeName;
			kind = symbol_table.kindOf(name);
			if(kind != NONE) {	// do obj.functionName(args...);
				type = symbol_table.typeOf(name); // class name
				indx = symbol_table.indexOf(name);
				if(kind == STA_TIC) vmwriter.writePush(STATIC, indx);
				else if(kind == FIELD) vmwriter.writePush(THIS, indx);
				else if(kind == ARG) vmwriter.writePush(ARGUMENT, indx);
				else if(kind == VAR) vmwriter.writePush(LOCAL, indx);
				nArgs = 1;
				caleeName = type;
			}
			caleeName += tokenizer.getCurrentToken();
			if (eatIdentifier()) {
				//	subroutineName	matched
				logMid("identifier");
				caleeName += tokenizer.getCurrentToken();
				if (eatSymbol('(')) {
					//	(	matched
					logMid("symbol");
					nArgs += CompileExpressionList();	// expressionList	matched
					if (eatSymbol(')')) {
						//	)	matched
						logMid("symbol");
						// now call function
						vmwriter.writeCall(caleeName, nArgs);
					}
					else assert(false);
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

bool CompilationEngine::canExpression() {
	//	term (op term)*
	// we'll check if it starts with a term
	return canTerm();
}

bool CompilationEngine::canTerm() {
	//	integerConstant | stringConstant | keywordConstant | varName | varName '[' expression ']' | subroutineCall | '(' expression ')' | unaryOp term
	if (eatToken(INT_CONST));
	else if (eatToken(STRING_CONST));
	else if (eatKeyWordConst());
	else if (eatToken(IDENTIFIER));
	else if (eatSymbol('('));
	else if (eatUnaryOp());
	else return false;

	tokenizer.backTrack();
	return true;
}



// -------------original usable methods implemented below--------------------------



// coded up
CompilationEngine::CompilationEngine(const std::string& in, const std::string& out) :
	input_file(std::ifstream(in)), output_file(std::ofstream(out)), tokenizer(in), vmwriter(in.substr(0, in.find_last_of('.')) + ".vm") 
{
	
}

// coded up
void CompilationEngine::CompileClass() {
	//	'class' className '{' classVarDec* subroutineDec* '}'
	if (eatKey(CLASS_KEY)) {
		//	class		matched
		logStart("class");
		indentation += "  ";
		logMid("keyword");
		if (eatIdentifier()) {
			// className	matched
			logMid("identifier");
			class_name = tokenizer.getCurrentToken();
			if (eatSymbol('{')) {
				//	{	matched
				logMid("symbol");
				bool flag = false;
				do {
					flag = false;
					if (eatKey(STATIC_KEY) || eatKey(FIELD_KEY)) {
						tokenizer.backTrack();
						CompileClassVarDec();	// classVarDec	matched
						flag = true;
					}
				} while (flag);

				do {
					flag = false;
					if (eatKey(CONSTRUCTOR_KEY) || eatKey(FUNCTION_KEY) || eatKey(METHOD_KEY)) {
						tokenizer.backTrack();
						CompileSubroutineDec();	// subroutineDec	matched
						flag = true;
					}
				} while (flag);

				if (eatSymbol('}')) {
					//	}	matched
					logMid("symbol");
					indentation.pop_back(); indentation.pop_back();
					logEnd("class");
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up along with symbol table 
void CompilationEngine::CompileClassVarDec() {
	//	('static' | 'field' ) type varName (',' varName)* ';'
	if (eatKey(STATIC_KEY) || eatKey(FIELD_KEY)) {
		//	static	|	field		matched
		logStart("classVarDec");
		indentation += "  ";
		logMid("keyword");
		Kind kind = NONE;
		if(tokenizer.getCurrentToken() == "static") kind = STA_TIC;
		else if(tokenizer.getCurrentToken() == "field") kind = FIELD;
		else assert(false);
		if (eatType()) {
			// type		matched
			if (tokenizer.tokenType() == IDENTIFIER) {
				logMid("identifier");
			}
			else {
				logMid("keyword");
			}
			std::string type = tokenizer.getCurrentToken();
			if (eatIdentifier()) {
				//	varName		matched
				logMid("identifier");
				std::string name = tokenizer.getCurrentToken();
				symbol_table.define(name, type, kind);
				bool flag = false;
				do {
					flag = false;
					if (eatSymbol(',')) {
						//	,		matched
						logMid("symbol");
						if (eatIdentifier()) {
							//	varName		matched
							logMid("identifier");
							name = tokenizer.getCurrentToken();
							symbol_table.define(name, type, kind);
							flag = true;
						}
						else assert(false);
					}
				} while (flag);

				if (eatSymbol(';')) {
					//	;	matched
					logMid("symbol");
					indentation.pop_back(); indentation.pop_back();
					logEnd("classVarDec");
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up along with symbol table
void CompilationEngine::CompileSubroutineDec() {
	//	('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
	if (eatKey(CONSTRUCTOR_KEY) || eatKey(FUNCTION_KEY) || eatKey(METHOD_KEY)) {
		//	constructor	| function	| method		matched
		logStart("subroutineDec");
		indentation += "  ";
		logMid("keyword");
		symbol_table.startSubroutine();
		
		this->subroutine_type = tokenizer.getCurrentToken();
		if(this->subroutine_type == "method") symbol_table.define("this", class_name, ARG); // very necessary
		
		if (eatKey(VOID_KEY) || eatType()) {
			//	void | type		matched
			if (tokenizer.tokenType() == IDENTIFIER) {
				logMid("identifier");
			}
			else {
				logMid("keyword");
			}
			
			if (eatIdentifier()) {
				//	subroutineName		matched
				logMid("identifier");
				function_name = tokenizer.getCurrentToken();
				if (eatSymbol('(')) {
					//	(		matched
					logMid("symbol");
					compileParameterList();	//	match	parameterList
					if (eatSymbol(')')) {
						//	)	matched
						logMid("symbol");
						compileSubroutineBody();	// match	subroutineBody
						indentation.pop_back(); indentation.pop_back();
						logEnd("subroutineDec");
					}
					else assert(false);
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up along with symbol table
void CompilationEngine::compileParameterList() {
	//	( (type varName) (',' type varName)*)?
	//	doesn't handle ()
	logStart("parameterList");
	indentation += "  ";
	if (eatType()) {
		// type matched
		if (tokenizer.tokenType() == IDENTIFIER) {
			logMid("identifier");
		}
		else {
			logMid("keyword");
		}
		std::string type = tokenizer.getCurrentToken();
		if (eatIdentifier()) {
			// varName	matched
			logMid("identifier");
			symbol_table.define(tokenizer.getCurrentToken(), type, ARG);
			bool flag = false;
			do {
				flag = false;
				if (eatSymbol(',')) {
					// ,	matched
					logMid("symbol");
					if (eatType()) {
						// type		matched
						if (tokenizer.tokenType() == IDENTIFIER) {
							logMid("identifier");
						}
						else {
							logMid("keyword");
						}
						type = tokenizer.getCurrentToken();
						if (eatIdentifier()) {
							// varName		matched
							logMid("identifier");
							symbol_table.define(tokenizer.getCurrentToken(), type, ARG);
							flag = true;
						}
						else assert(false);
					}
					else assert(false);
				}
			} while (flag);
		}
		else assert(false);
	}
	indentation.pop_back(); indentation.pop_back();
	logEnd("parameterList");
}

// coded up
void CompilationEngine::compileSubroutineBody() {
	//	'{' varDec* statements '}'

	if (eatSymbol('{')) {
		//	{		matched
		logStart("subroutineBody");
		indentation += "  ";

		logMid("symbol");

		bool flag = false;
		do {
			flag = false;
			if (eatKey(VAR_KEY)) {
				// varDec	matched
				tokenizer.backTrack();
				compileVarDec();	// varDec	match
				flag = true;
			}
		} while (flag);
		
		int nLocals = symbol_table.varCount(VAR);
		vmwriter.writeFunction(class_name + "." + function_name, nLocals);
		// do something
		if(this->subroutine_type == "method") {
			// implicit argument this 0
			vmwriter.writePush(ARGUMENT, 0);
			vmwriter.writePop(POINTER, 0);
		} else if(this->subroutine_type == "constructor") {
			vmwriter.writePush(CONSTANT, symbol_table.varCount(FIELD));
			vmwriter.writeCall("Memory.alloc", 1);
			vmwriter.writePop(POINTER, 0);
		} else {}	// do nothing
		
		compileStatements();	// statements	mathced
		if (eatSymbol('}')) {
			//	}	matched
			logMid("symbol");	
		}
		else assert(false);

		indentation.pop_back(); indentation.pop_back();
		logEnd("subroutineBody");
	}
	else assert(false);
}

// coded up along with symbol table
void CompilationEngine::compileVarDec() {
	//	'var' type varName (',' varName)* ';'

	if (eatKey(VAR_KEY)) {
		// var		matched
		logStart("varDec");
		indentation += "  ";
		logMid("keyword");
		if (eatType()) {
			//	type	matched
			if (tokenizer.tokenType() == IDENTIFIER) {
				logMid("identifier");
			}
			else {
				logMid("keyword");
			}
			std::string type = tokenizer.getCurrentToken();
			if (eatIdentifier()) {
				//	varName		matched
				logMid("identifier");
				symbol_table.define(tokenizer.getCurrentToken(), type, VAR);
				bool flag = false;
				do {
					flag = false;
					if (eatSymbol(',')) {
						//	,		matched
						logMid("symbol");
						if (eatIdentifier()) {
							//	varName		matched
							logMid("identifier");
							symbol_table.define(tokenizer.getCurrentToken(), type, VAR);
							flag = true;
						}
						else assert(false);
					} 
				} while (flag);

				if (eatSymbol(';')) {
					//	;		matched
					logMid("symbol");
					indentation.pop_back(); indentation.pop_back();
					logEnd("varDec");
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up with vm code
void CompilationEngine::compileStatements() {
	//	(letStatement | ifStatement | whileStatement | doStatement | returnStatement)*		0 or more occurances
	bool first_time = true;
	bool flag = true;
	auto manage_first = [&]() {
		first_time = false;
		logStart("statements");
		indentation += "  ";
		return;
	};

	auto manage_last = [&]() {
		indentation.pop_back(); indentation.pop_back();
		logEnd("statements");
		return;
	};

	do {	// Uses a loop to handle 0 or more statement instances, according to the left-most token
		if (eatKey(LET_KEY)) {
			if (first_time) manage_first();
			tokenizer.backTrack();
			compileLet();
		}
		else if (eatKey(IF_KEY)) {
			if (first_time) manage_first();
			tokenizer.backTrack();
			compileIf();
		}
		else if (eatKey(WHILE_KEY)) {
			if (first_time) manage_first();
			tokenizer.backTrack();
			compileWhile();
		}
		else if (eatKey(DO_KEY)) {
			if (first_time) manage_first();
			tokenizer.backTrack();
			compileDo();
		}
		else  if (eatKey(RETURN_KEY)) {
			if (first_time) manage_first();
			tokenizer.backTrack();
			compileReturn();
		}
		else {
			manage_last();	// end of statent*
			flag = false;
		}
	} while (flag);
}

// coded up 
void CompilationEngine::compileDo() {
	//	'do' subroutineCall ';'
	if (eatKey(DO_KEY)) {
		//	do	matched
		logStart("doStatement");
		indentation += "  ";
		logMid("keyword");
		subroutineCall();	//	match subroutineCall
		if (eatSymbol(';')) {
			//	;	matched
			logMid("symbol");
			indentation.pop_back(); indentation.pop_back();
			logEnd("doStatement");
			vmwriter.writePop(TEMP, 0);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up
void CompilationEngine::compileLet() {
	//	'let' varName ('[' expression ']')? '=' expression ';'

	if (eatKey(LET_KEY)) {
		//	let		matched
		logStart("letStatement");
		indentation += "  ";
		logMid("keyword");
		if (eatIdentifier()) {
			std::string name = tokenizer.getCurrentToken();
			bool indexing = false;
			//	varName		matched
			logMid("identifier");
			if (eatSymbol('[')) {
				//	[	matched
				logMid("symbol");
				indexing = true;
				CompileExpression();	//	expression	match
				if (eatSymbol(']')) {
					//	]	matched
					logMid("symbol");
					Kind kind = symbol_table.kindOf(name);
					if(kind == STA_TIC) vmwriter.writePush(STATIC, symbol_table.indexOf(name));
					else if(kind == FIELD) vmwriter.writePush(THIS, symbol_table.indexOf(name));
					else if(kind == ARG) vmwriter.writePush(ARGUMENT, symbol_table.indexOf(name));
					else if(kind == VAR) vmwriter.writePush(LOCAL, symbol_table.indexOf(name));
					vmwriter.WriteArithmetic(ADD);
				}
				else assert(false);
			} else {
				// do nothing
				indexing = false;
			}
			if (eatSymbol('=')) {
				//	=	matched
				logMid("symbol");
				CompileExpression();	//	expression	match
				if (eatSymbol(';')) {
					//	;	matched
					logMid("symbol");
					if(indexing) {
						vmwriter.writePop(TEMP, 0);
						vmwriter.writePop(POINTER, 1);
						vmwriter.writePush(TEMP, 0);
						vmwriter.writePop(THAT, 0);
					} else {
						Kind kind = symbol_table.kindOf(name);
						if(kind == STA_TIC) vmwriter.writePop(STATIC, symbol_table.indexOf(name));
						else if(kind == FIELD) vmwriter.writePop(THIS, symbol_table.indexOf(name));
						else if(kind == ARG) vmwriter.writePop(ARGUMENT, symbol_table.indexOf(name));
						else if(kind == VAR) vmwriter.writePop(LOCAL, symbol_table.indexOf(name));
					}
					indentation.pop_back(); indentation.pop_back();
					logEnd("letStatement");
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

//	coded up with vmcode
void CompilationEngine::compileWhile() {
	//	'while' '(' expression ')' '{' statements '}'
	static int while_cnt = 0;
	if (eatKey(WHILE_KEY)) {
		//	while	matched
		logStart("whileStatement");
		indentation += "  ";
		logMid("keyword");
		std::string label1 = "WHILE_EXP" + std::to_string(while_cnt);
		std::string label2 = "WHILE_END" + std::to_string(while_cnt);
		++while_cnt;
		if (eatSymbol('(')) {
			//	(	matched
			logMid("symbol");
			vmwriter.WriteLabel(label1);
			CompileExpression();	//	expression	match
			if (eatSymbol(')')) {
				//	)	matched
				logMid("symbol");
				vmwriter.WriteArithmetic(NOT);
				vmwriter.WriteIf(label2);
				if (eatSymbol('{')) {
					//	{	matched
					logMid("symbol");
					compileStatements();	//	statements	match
					vmwriter.WriteGoto(label1);
					if (eatSymbol('}')) {
						//	}	matched
						logMid("symbol");
						indentation.pop_back(); indentation.pop_back();
						logEnd("whileStatement");
						vmwriter.WriteLabel(label2);	
					}
					else assert(false);
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

//	coded up
void CompilationEngine::compileReturn() {
	//	'return' expression ? ';'
	if (eatKey(RETURN_KEY)) {
		//	return		matched
		logStart("returnStatement");
		indentation += "  ";
		logMid("keyword");
		bool flag = CompileExpression();	// expression?	match optional
		if (eatSymbol(';')) {
			//	;	matched
			logMid("symbol");
			indentation.pop_back(); indentation.pop_back();
			logEnd("returnStatement");
			if(!flag) vmwriter.writePush(CONSTANT, 0);
			vmwriter.writeReturn();
		}
		else  assert(false);
	}
	else assert(false);
}

// coded up with vmcode
void CompilationEngine::compileIf() {
	//	'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}') ?
	static int if_cnt = 0;
	if (eatKey(IF_KEY)) {
		//	if	matched
		logStart("ifStatement");
		indentation += "  ";
		logMid("keyword");
		if (eatSymbol('(')) {
			// (	matched
			logMid("symbol");
			CompileExpression();	//	expression	match
			vmwriter.WriteArithmetic(NOT);
			std::string label1 = "IF_FALSE" + std::to_string(if_cnt);
			std::string label2 = "IF_END" + std::to_string(if_cnt);
			if_cnt++;
			vmwriter.WriteIf(label1);
			if (eatSymbol(')')) {
				//	)	matched
				logMid("symbol");
				if (eatSymbol('{')) {
					//	{	matched
					logMid("symbol");
					compileStatements();	//	statements	matched
					if (eatSymbol('}')) {
						//	}	matched
						logMid("symbol");
						vmwriter.WriteGoto(label2);
						vmwriter.WriteLabel(label1);
						
						if (eatKey(ELSE_KEY)) {
							// else	matched
							logMid("keyword");
							if (eatSymbol('{')) {
								//	{	matched
								logMid("symbol");
								compileStatements();	//	statements	match
								if (eatSymbol('}')) {
									//	}	matched
									logMid("symbol");
								}
								else assert(false);
							}
							else assert(false);
						}
						
						vmwriter.WriteLabel(label2);
						indentation.pop_back(); indentation.pop_back();
						logEnd("ifStatement");
					}
					else assert(false);
				}
				else assert(false);
			}
			else assert(false);
		}
		else assert(false);
	}
	else assert(false);
}

// coded up
bool CompilationEngine::CompileExpression() {
	//	term (op term)*
	if (!canExpression()) {
		return false;
	}
	logStart("expression");
	indentation += "  ";
	
	if (canTerm()) {	// term mathced
		CompileTerm();
	}
	else assert(false);

	bool flag = false;
	do {
		flag = false;
		if (eatOp()) {
			//	op matched
			logMid("symbol");
			std::string op = tokenizer.getCurrentToken();
			if (canTerm()) {
				CompileTerm();	// term matched
				if(op == "+") vmwriter.WriteArithmetic(ADD);
				else if(op == "-") vmwriter.WriteArithmetic(SUB);
				else if(op == "*") vmwriter.writeCall("Math.multiply", 2);
				else if(op == "/") vmwriter.writeCall("Math.divide", 2);
				else if(op == "&") vmwriter.WriteArithmetic(AND);
				else if(op == "|") vmwriter.WriteArithmetic(OR);
				else if(op == "<") vmwriter.WriteArithmetic(LT);
				else if(op == ">") vmwriter.WriteArithmetic(GT);
				else if(op == "=") vmwriter.WriteArithmetic(EQ);
				flag = true;
			}
			else assert(false);
		}
	} while (flag);
	indentation.pop_back(); indentation.pop_back();
	logEnd("expression");
	return true;
}

// coded up
void CompilationEngine::CompileTerm() {
	//	integerConstant | stringConstant | keywordConstant | varName | varName '[' expression ']' | subroutineCall | '(' expression ')' | unaryOp term
	if (!canTerm()) {
		return;
	}
	logStart("term");
	indentation += "  ";

	if (eatToken(INT_CONST)) {
		//	integerConstant matched
		logMid("integerConstant");
		vmwriter.writePush(CONSTANT, std::stoi(tokenizer.getCurrentToken()));
	}
	else if (eatToken(STRING_CONST)) {
		//	stringConstant	matched
		logMid("stringConstant");
		std::string string_constant = tokenizer.getCurrentToken();
		vmwriter.writePush(CONSTANT, (int)string_constant.size() - 2);
		vmwriter.writeCall("String.new", 1);
		for(int i = 1; i < (int)string_constant.size() - 1; ++i) {
			vmwriter.writePush(CONSTANT, string_constant[i]);
			vmwriter.writeCall("String.appendChar", 2);
		}
	}
	else if (eatKeyWordConst()) {
		//	keywordConstant	matched
		logMid("keyword");
		if(tokenizer.getCurrentToken() == "null" || 
			tokenizer.getCurrentToken() == "false") {
				vmwriter.writePush(CONSTANT, 0);
			}
		else if(tokenizer.getCurrentToken() == "true") {
			vmwriter.writePush(CONSTANT, 0);
			vmwriter.WriteArithmetic(NOT);
		} else if(tokenizer.getCurrentToken() == "this") {
			vmwriter.writePush(POINTER, 0);
		}
	}
	else if (eatToken(IDENTIFIER)) {
		//	varName | varName '[' expression ']' | subroutineCall	-> 3 possibilities...
		if (eatSymbol('[')) {	//	varName '[' expression ']'
			//	[	matched
			tokenizer.backTrack();
			logMid("identifier");
			std::string name = tokenizer.getCurrentToken();
			Kind kind = symbol_table.kindOf(name);
			int indx = symbol_table.indexOf(name);
			
			eatSymbol('[');
			logMid("symbol");
			CompileExpression();	// expression matched
			if(kind == STA_TIC) vmwriter.writePush(STATIC, indx);
			else if(kind == FIELD) vmwriter.writePush(THIS, indx);
			else if(kind == ARG) vmwriter.writePush(ARGUMENT, indx);
			else if(kind == VAR) vmwriter.writePush(LOCAL, indx);
			if (eatSymbol(']')) {
				logMid("symbol");
				vmwriter.WriteArithmetic(ADD);
				vmwriter.writePop(POINTER, 1);
				vmwriter.writePush(THAT, 0);
			}
			else assert(false);
		}
		else if (eatSymbol('(') || eatSymbol('.')) {	//	subroutineCall
			tokenizer.backTrack();
			tokenizer.backTrack();
			subroutineCall();	// subroutineCall match
			// full call
			
		}
		else {	// varName
			logMid("identifier");
			std::string name = tokenizer.getCurrentToken();
			Kind kind = symbol_table.kindOf(name);
			std::string type = symbol_table.typeOf(name);
			int indx = symbol_table.indexOf(name);
			
			if(kind == STA_TIC) vmwriter.writePush(STATIC, indx);
			else if(kind == FIELD) vmwriter.writePush(THIS, indx);
			else if(kind == ARG) vmwriter.writePush(ARGUMENT, indx);
			else if(kind == VAR) vmwriter.writePush(LOCAL, indx);
		}
	}
	else if (eatSymbol('(')) {
		//	(	matched
		logMid("symbol");
		if (canExpression()) {
			CompileExpression();	//	expression matched
		}
		else assert(false);
		if (eatSymbol(')')) {
			//	)	matched
			logMid("symbol");
		}
		else assert(false);
	}
	else if (eatUnaryOp()) {
		//	unaryOp	matched
		logMid("symbol");
		std::string uop = tokenizer.getCurrentToken();
		CompileTerm();	//	term	matched
		if(uop == "-") vmwriter.WriteArithmetic(NEG);
		else if(uop == "~") vmwriter.WriteArithmetic(NOT);
	}
	else assert(false);

	indentation.pop_back(); indentation.pop_back();
	logEnd("term");
}

// coded up
int CompilationEngine::CompileExpressionList() {
	//	(expression (',' expression)* )?
	int nArgs = 0;
	logStart("expressionList");
	indentation += "  ";
	if (canExpression()) {	
		CompileExpression();	// expression matched
		++nArgs;
		bool flag = false;
		do {
			flag = false;
			if (eatSymbol(',')) {
				//	,	matched
				logMid("symbol");
				if (canExpression()) {	
					CompileExpression();	//	expression matched
					++nArgs;
					flag = true;
				}
				else assert(false);
			}
		} while (flag);
	}
	indentation.pop_back(); indentation.pop_back();
	logEnd("expressionList");
	return nArgs;
}

CompilationEngine::~CompilationEngine() {
	input_file.close();
	output_file.close();
	vmwriter.close();
}
