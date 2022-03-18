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
	if (eatIdentifier()) {
		//	subroutineName		matched	or	className|varName	matched
		logMid("identifier");
		if (eatSymbol('(')) {
			//	(	matched
			logMid("symbol");
			CompileExpressionList();	// expressionList	matched
			if (eatSymbol(')')) {
				//	)	matched
				logMid("symbol");
			}
			else assert(false);
		}
		else if (eatSymbol('.')) {	//	className | varName	matched actually
			//	.	matched
			logMid("symbol");
			if (eatIdentifier()) {
				//	subroutineName	matched
				logMid("identifier");
				if (eatSymbol('(')) {
					//	(	matched
					logMid("symbol");
					CompileExpressionList();	// expressionList	matched
					if (eatSymbol(')')) {
						//	)	matched
						logMid("symbol");
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

// coded up
CompilationEngine::CompilationEngine(const std::string& in, const std::string& out) :
	input_file(std::ifstream(in)), output_file(std::ofstream(out)), tokenizer(in) {}

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

// coded up
void CompilationEngine::CompileClassVarDec() {
	//	('static' | 'field' ) type varName (',' varName)* ';'
	if (eatKey(STATIC_KEY) || eatKey(FIELD_KEY)) {
		//	static	|	field		matched
		logStart("classVarDec");
		indentation += "  ";
		logMid("keyword");
		if (eatType()) {
			// type		matched
			if (tokenizer.tokenType() == IDENTIFIER) {
				logMid("identifier");
			}
			else {
				logMid("keyword");
			}
			if (eatIdentifier()) {
				//	varName		matched
				logMid("identifier");
				bool flag = false;
				do {
					flag = false;
					if (eatSymbol(',')) {
						//	,		matched
						logMid("symbol");
						if (eatIdentifier()) {
							//	varName		matched
							logMid("identifier");
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

// coded up
void CompilationEngine::CompileSubroutineDec() {
	//	('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
	if (eatKey(CONSTRUCTOR_KEY) || eatKey(FUNCTION_KEY) || eatKey(METHOD_KEY)) {
		//	constructor	| function	| method		matched
		logStart("subroutineDec");
		indentation += "  ";
		logMid("keyword");
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

// coded up
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
		if (eatIdentifier()) {
			// varName	matched
			logMid("identifier");
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
						if (eatIdentifier()) {
							// varName		matched
							logMid("identifier");
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

// coded up
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
			if (eatIdentifier()) {
				//	varName		matched
				logMid("identifier");
				bool flag = false;
				do {
					flag = false;
					if (eatSymbol(',')) {
						//	,		matched
						logMid("symbol");
						if (eatIdentifier()) {
							//	varName		matched
							logMid("identifier");
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

// coded up
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
			//	varName		matched
			logMid("identifier");
			if (eatSymbol('[')) {
				//	[	matched
				logMid("symbol");
				CompileExpression();	//	expression	match
				if (eatSymbol(']')) {
					//	]	matched
					logMid("symbol");
				}
				else assert(false);
			}
			if (eatSymbol('=')) {
				//	=	matched
				logMid("symbol");
				CompileExpression();	//	expression	match
				if (eatSymbol(';')) {
					//	;	matched
					logMid("symbol");
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

//	coded up
void CompilationEngine::compileWhile() {
	//	'while' '(' expression ')' '{' statements '}'
	if (eatKey(WHILE_KEY)) {
		//	while	matched
		logStart("whileStatement");
		indentation += "  ";
		logMid("keyword");
		if (eatSymbol('(')) {
			//	(	matched
			logMid("symbol");
			CompileExpression();	//	expression	match
			if (eatSymbol(')')) {
				//	)	matched
				logMid("symbol");
				if (eatSymbol('{')) {
					//	{	matched
					logMid("symbol");
					compileStatements();	//	statements	match
					if (eatSymbol('}')) {
						//	}	matched
						logMid("symbol");
						indentation.pop_back(); indentation.pop_back();
						logEnd("whileStatement");
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
		CompileExpression();	// expression?	match optional
		if (eatSymbol(';')) {
			//	;	matched
			logMid("symbol");
			indentation.pop_back(); indentation.pop_back();
			logEnd("returnStatement");
		}
		else  assert(false);
	}
	else assert(false);
}

// coded up
void CompilationEngine::compileIf() {
	//	'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}') ?
	if (eatKey(IF_KEY)) {
		//	if	matched
		logStart("ifStatement");
		indentation += "  ";
		logMid("keyword");
		if (eatSymbol('(')) {
			// (	matched
			logMid("symbol");
			CompileExpression();	//	expression	match
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
void CompilationEngine::CompileExpression() {
	//	term (op term)*
	if (!canExpression()) {
		return;
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
			if (canTerm()) {
				CompileTerm();	// term matched
				flag = true;
			}
			else assert(false);
		}
	} while (flag);
	indentation.pop_back(); indentation.pop_back();
	logEnd("expression");
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
	}
	else if (eatToken(STRING_CONST)) {
		//	stringConstant	matched
		logMid("stringConstant");
	}
	else if (eatKeyWordConst()) {
		//	keywordConstant	matched
		logMid("keyword");
	}
	else if (eatToken(IDENTIFIER)) {
		//	varName | varName '[' expression ']' | subroutineCall	-> 3 possibilities...
		if (eatSymbol('[')) {	//	varName '[' expression ']'
			//	[	matched
			tokenizer.backTrack();
			logMid("identifier");
			eatSymbol('[');
			logMid("symbol");
			CompileExpression();	// expression matched
			if (eatSymbol(']')) {
				logMid("symbol");
			}
			else assert(false);
		}
		else if (eatSymbol('(') || eatSymbol('.')) {	//	subroutineCall
			tokenizer.backTrack();
			tokenizer.backTrack();
			subroutineCall();	// subroutineCall match
		}
		else {
			//	varName matched 
			logMid("identifier");
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
		CompileTerm();	//	term	matched
	}
	else assert(false);

	indentation.pop_back(); indentation.pop_back();
	logEnd("term");
}

// coded up
void CompilationEngine::CompileExpressionList() {
	//	(expression (',' expression)* )?
	logStart("expressionList");
	indentation += "  ";
	if (canExpression()) {	
		CompileExpression();	// expression matched
		bool flag = false;
		do {
			flag = false;
			if (eatSymbol(',')) {
				//	,	matched
				logMid("symbol");
				if (canExpression()) {	
					CompileExpression();	//	expression matched
					flag = true;
				}
				else assert(false);
			}
		} while (flag);
	}
	indentation.pop_back(); indentation.pop_back();
	logEnd("expressionList");
}

CompilationEngine::~CompilationEngine() {
	input_file.close();
	output_file.close();
}