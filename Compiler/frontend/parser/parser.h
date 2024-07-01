#pragma once
//parser

#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"

class Parser {    // 1개 생성
private:
	Lexer lexer_; // 1개 생성
	Token* curtoken_;  // 계속 변경이 되어야함
	Token* peektoken_;

	Parser(const Lexer& lexer);
	Parser(const std::string& input);
	LetStatement* parseLetStatement(const Token* const let_token);
	Statement* parseStatement(const Token* const curtoken);

public:
	bool IsCurTokenType(const TokenType& type);
	bool IsPeekTokenType(const TokenType& type);
	bool moveNextIfPeekTokenTypeIs(const TokenType& type);

	void MoveNextToken();

	Program* parseProgram();
	
	static Parser* createParserFromLexer(const Lexer& lexer);
	static Parser* createParserFromInput(const std::string& input);
	//Parser(const Parser& copy);
	~Parser();
};