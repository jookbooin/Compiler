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
typedef std::unique_ptr<Expression> (Parser::*PrefixFuncPtr)();
typedef std::unique_ptr<Expression> (Parser::*InfixFuncPtr)(std::unique_ptr<Expression> left);

using PrefixFuncMap = std::map<TokenType, PrefixFuncPtr >;
using InfixFuncMap = std::map<TokenType, InfixFuncPtr >;

class Parser {    // 1개 생성
private:
	std::unique_ptr<Token> curtoken_;  
	std::unique_ptr<Token> peektoken_;

	Lexer lexer_; // 1개  ( parser 소유권 )
	std::vector<std::string> errors_; // 파싱 에러 모음

	PrefixFuncMap prefix_func_map; // prefix 처리 method 보관하는 Map
	InfixFuncMap infix_func_map;   // infix 처리 method 보관하는 Map

	Parser(const std::string& input);

	std::unique_ptr<LetStatement> parseLetStatement();
	std::unique_ptr<ReturnStatement> parseReturnStatement();
	std::unique_ptr<ExpressionStatement> parseExpressionStatement() ;
	std::unique_ptr<Statement> parseStatementFromCurToken();

	void registerPrefixFunc(TokenType tokenType, PrefixFuncPtr prefixFuncPtr); // prefix_func_map에 등록 
	void registerInfixFunc(TokenType tokenType, InfixFuncPtr infixFuncPtr); // infix_func_map에 등록
	void initializeFuncMaps(); // prefix_func_map, infix_func_map 초기화

public:

	Parser(Lexer&& lx);
	~Parser();
	Parser(const Parser& copy) = delete;
	Parser& operator=(const Parser& src) = delete;
    Parser& operator=(Parser&& src) = delete;    

	// prefix 파싱 메서드
	std::unique_ptr<Expression> parseIdentifier();
	std::unique_ptr<Expression> parseIntegerLiteral();
	std::unique_ptr<Expression> parsePrefixExpression();
	std::unique_ptr<Expression> parseBoolean();
	std::unique_ptr<Expression> parseGroupedExpression();
	std::unique_ptr<Expression> parseIfExpression();
	std::unique_ptr<Expression> parseFunctionLiteral();

	// infix 파싱 메서드
	std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> left_expression); 

	std::unique_ptr<Expression> parseExpressionWithLeftOperatorRBP(int left_token_RBP); // 왼쪽 연산자(= 토큰)의 right_binding_power(= 연산자 우선순위) 전달 

	Program* parseProgram();
	void addError(const std::string& error_info);
	const std::string& peekError(const TokenType& type);
	void advanceCurToken();
	bool isCurTokenType(const TokenType& type);
	bool isPeekTokenType(const TokenType& type);
	bool advanceTokenIfPeekTokenTypeIs(const TokenType& type); //  peekTokenType 확인 후, 올바른 타입이면 nextToken으로 이동

	// getter
	int getCurTokenPrecedence();
	int getPeekTokenPrecedence();
	int getLeftOperatorRBP();
	int getRightOperatorLBP();
	const std::vector<std::string>& getErrors() const;


	static Parser* createFrom(const Lexer& lexer);
	static Parser* createFrom(const std::string& input);
};