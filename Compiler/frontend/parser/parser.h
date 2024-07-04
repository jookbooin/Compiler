#pragma once
//parser
#include <vector>

#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"
#include "../../globalUtils.h"

class Parser {    // 1개 생성
private:
	Lexer lexer_; // 1개  ( parser 소유권 )
	Token* curtoken_;  // 계속 변경이 되어야함
	Token* peektoken_;

	std::vector<std::string> errors_; // 파싱 에러 모음

	Parser(const Lexer& lexer);
	Parser(const std::string& input);
	LetStatement* parseLetStatement(const Token* const let_token);
	ReturnStatement* parseReturnStatement(const Token* const return_token);
	Statement* parseStatement(const Token* const curtoken);

public:
	void peekError(const TokenType& type);
	void advanceToken();
	bool isCurTokenType(const TokenType& type);
	bool isPeekTokenType(const TokenType& type);
	bool advanceTokenIfPeekTokenTypeIs(const TokenType& type);	


	Program* parseProgram();
	
	static Parser* createParserFromLexer(const Lexer& lexer);
	static Parser* createParserFromInput(const std::string& input);
	//Parser(const Parser& copy);
	~Parser();
};