#include "repl.h"


void start() {
	std::string input;

	while (1) {
		std::cout << PROMPT ;
		if (!std::getline(std::cin, input)) {
			break;
		}

		//Lexer* lx = Lexer::createLexerFromInput(input);

		// token도 언젠가는 지워야함.
		/*for (Token* tok = lx->nextToken(); tok->getType() != "EOF"; tok = lx->nextToken()) {
            std::cout << "[Type:" << tok->getType() << "  Literal:" << tok->getLiteral() << "]" << std::endl;	
        }*/

	}


}