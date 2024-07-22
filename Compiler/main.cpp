
#include <iostream>
#include "frontend/lexer/lexer.h"
#include "frontend/repl/repl.h"
#include "frontend/parser/parser.h"
#include "globalUtils.h"

int main() {

	//start();
	std::string input = "let five = 5;";

	
	Lexer * lx = Lexer::createLexerFromInput(input);
	Parser* p = Parser::createParserFromLexer(*lx);

	//Parser* p = Parser::createParserFromInput(input);

	Program* program = p->parseProgram();
	
	return 0;
}


