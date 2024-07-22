#pragma once
//parser
#include <vector>

#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../ast/ast.h"
#include "../../globalUtils.h"
#include "parse_info.h"
#include "../ast/integerLiteral/integer_literal.h"
#include "../ast/prefixExpression/prefixExpression.h"
#include "../ast/infixExpression/infixExpression.h"

class Parser;

// 클래스 함수 포인터
typedef Expression* (Parser::*PrefixFuncPtr)();
typedef Expression* (Parser::*InfixFuncPtr)(Expression* left);

using PrefixFuncMap = std::map<TokenType, PrefixFuncPtr >;
using InfixFuncMap = std::map<TokenType, InfixFuncPtr >;

class Parser {    // 1개 생성
private:
	Token* curtoken_;  // 계속 변경이 되어야함
	Token* peektoken_;

	Lexer lexer_; // 1개  ( parser 소유권 )
	std::vector<std::string> errors_; // 파싱 에러 모음

	PrefixFuncMap prefix_func_map; // prefix 처리 method 보관하는 Map
	InfixFuncMap infix_func_map;   // infix 처리 method 보관하는 Map

	Parser(const Lexer& lexer);
	Parser(const std::string& input);
	LetStatement* parseLetStatement();
	ReturnStatement* parseReturnStatement();
	ExpressionStatement* parseExpressionStatement() ;

	Statement* parseStatementFromCurToken();

	void registerPrefixFunc(TokenType tokenType, PrefixFuncPtr prefixFuncPtr); // prefix_func_map에 등록 
	void registerInfixFunc(TokenType tokenType, InfixFuncPtr infixFuncPtr); // infix_func_map에 등록
	void initializeFuncMaps(); // prefix_func_map, infix_func_map 초기화

public:
	void addError(const std::string& error_info);
	void peekError(const TokenType& type);
	const std::vector<std::string>& getErrors() const;

	void advanceCurToken();
	bool isCurTokenType(const TokenType& type);
	bool isPeekTokenType(const TokenType& type);
	bool advanceTokenIfPeekTokenTypeIs(const TokenType& type); //  peekTokenType 확인 후, 올바른 타입이면 nextToken으로 이동
	int getCurTokenPrecedence();
	int getPeekTokenPrecedence();
	int getLeftOperatorRBP();
	int getRightOperatorLBP();

	Program* parseProgram();
	Expression* parseExpressionWithLeftOperatorRBP(int left_token_RBP); // 왼쪽 연산자(= 토큰)의 right_binding_power(= 연산자 우선순위) 전달 

	// prefix 파싱 메서드
	Expression* parseIdentifier();
	Expression* parseIntegerLiteral();
	Expression* parsePrefixExpression();
	Expression* parseBoolean();
	Expression* parseGroupedExpression();
	Expression* parseIfExpression();
	Expression* parseFunctionLiteral();

	// infix 파싱 메서드
	Expression* parseInfixExpression(Expression* left_expression); 

	static Parser* createParserFromLexer(const Lexer& lexer);
	static Parser* createParserFromInput(const std::string& input);
	//Parser(const Parser& copy);
	~Parser();
};