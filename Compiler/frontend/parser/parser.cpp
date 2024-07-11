#include "parser.h"

// prefix
Expression* Parser::parseIdentifier() {
	return Identifier::createIdentifierFromToken(curtoken_);
}

Expression* Parser::parseIntegerLiteral() {
	
	Expression* expression = nullptr;
	try {
		expression = IntegerLiteral::createIntegerLiteralFromToken(curtoken_);
	} catch (const ParsingException& e) { // string -> int 변환 불가 메서드 
			addError(e.what());
	}

	return expression;
}

Expression* Parser::parsePrefixExpression() {
	return nullptr;
}

Expression* Parser::parseBoolean() {
	return nullptr;
}

Expression* Parser::parseIfExpression() {
	return nullptr;
}

Expression* Parser::parseGroupedExpression() {
	return nullptr;
}

Expression* Parser::parseFunctionLiteral() {
	return nullptr;
}

// infix 
Expression* Parser::parseInfixExpression(Expression* left) {
	return nullptr;
}

void Parser::registerPrefixFunc(TokenType tokenType, PrefixFuncPtr prefixFuncPtr) {
	prefix_func_map[tokenType] = prefixFuncPtr;
}

void Parser::registerInfixFunc(TokenType tokenType, InfixFuncPtr infixFuncPtr) {
	infix_func_map[tokenType] = infixFuncPtr;
}

void Parser::initializeFuncMaps() {
	// prefix
	registerPrefixFunc(TokenTypes::IDENT, &Parser::parseIdentifier);

	registerPrefixFunc(TokenTypes::INT, &Parser::parseIntegerLiteral);

	registerPrefixFunc(TokenTypes::BANG, &Parser::parsePrefixExpression);
	registerPrefixFunc(TokenTypes::MINUS, &Parser::parsePrefixExpression);

	registerPrefixFunc(TokenTypes::TRUE, &Parser::parseBoolean);
	registerPrefixFunc(TokenTypes::FALSE, &Parser::parseBoolean);

	registerPrefixFunc(TokenTypes::LPAREN, &Parser::parseGroupedExpression);

	registerPrefixFunc(TokenTypes::IF, &Parser::parseIfExpression);

	registerPrefixFunc(TokenTypes::FUNCTION, &Parser::parseFunctionLiteral);

	// infix
	registerInfixFunc(TokenTypes::PLUS, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::MINUS, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::SLASH, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::ASTERISK, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::EQ, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::NOT_EQ, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::LT, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::GT, &Parser::parseInfixExpression);
	registerInfixFunc(TokenTypes::LPAREN, &Parser::parseInfixExpression);
}

void Parser::addError(const std::string& error_info) {
	errors_.push_back(error_info);
}

void Parser::peekError(const TokenType& type) {
	std::ostringstream oss;
	oss << "expect TokenType : " << peektoken_->getType() << ", actual : " << type ;

	addError(oss.str());
}

void Parser::advanceToken() {
	curtoken_ = peektoken_;
	peektoken_ = lexer_.nextToken();
}

bool Parser::isCurTokenType(const TokenType& type) {
	return curtoken_->getType() == type;
}

bool Parser::isPeekTokenType(const TokenType& type) {
	return peektoken_->getType() == type;
}

bool Parser::advanceTokenIfPeekTokenTypeIs(const TokenType& type) {
	if (isPeekTokenType(type)) {
		advanceToken();
		return true;
	}

	// 에러 발생 
	peekError(type);
	return false;
}

LetStatement* Parser::parseLetStatement(const Token* const let_token) {

	// 1. [let] five
	if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::IDENT)) {
		return nullptr;
	}

	// 2. let [five]
	Token* variable_name_token = curtoken_;

	//if (!IsPeekTokenType(TokenTypes::ASSIGN)) {
	if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::ASSIGN)) {
		return nullptr;
	}

	// 3. let five [ = ] 
	while (!isCurTokenType(TokenTypes::SEMICOLON)) {
		advanceToken();
	}

	// 4. let five =  [ ; ]
	return new LetStatement(let_token, variable_name_token);
}

ReturnStatement* Parser::parseReturnStatement(const Token* const return_token) {
	ReturnStatement* returnStatement = new ReturnStatement(return_token);
	advanceToken();
	return returnStatement;
}

ExpressionStatement* Parser::parseExpressionStatement(const Token* const expression_token) {
	
	Expression* expression = parseExpression(Operator::Priority::LOWEST);

	ExpressionStatement* expression_statement = new ExpressionStatement(expression_token, expression); // 내부로 expression 소유권 전달
	
	if (isPeekTokenType(TokenTypes::SEMICOLON)) { // 
		advanceToken();
	}

	return expression_statement;
}

Statement* Parser::parseStatement(const Token* const curtoken) {

	if (isCurTokenType(TokenTypes::LET)) {
		return parseLetStatement(curtoken);
	} else if (isCurTokenType(TokenTypes::RETURN)) {
		return parseReturnStatement(curtoken);
	} else {
		return parseExpressionStatement(curtoken);
	}

	// 3. 

	return nullptr;
}

/*
* program DI
  - root 1개만 있어야 하므로 참조로 전달?
*/
Program* Parser::parseProgram() {

	// 1. AST root 노드 생성
	Program* root = new Program();

	// 2. EOF 까지 token 반복
	while (!isCurTokenType(TokenTypes::kEOF)) {

		// 3. let, return 명령문 파싱
		// nullptr이 아닌 예외를 던지는 방법은?
		Statement* stmt = parseStatement(curtoken_);

		// 4. Program의 Statement에 추가 
		if (stmt != nullptr) {

			// 유일한 객체로 만들어 전달?
			root->addStatement(stmt);
		}

		// 5. 다음 token 호출
		advanceToken();
	}

	return root;
}

/// <summary>
/// 재귀적으로 동작 /
/// 매개변수는 왼쪽 연산자의 right_binding_power을 의미 / 
/// [ + (5) * ] : 5가 + , * 의 우선순위를 통해 어느것을 먼저 처리할지 결정/
/// </summary>
Expression* Parser::parseExpression(int left_token_RBP) { 
	
	Expression* leftExpression;

	// 1. prefix : + [5] *
	auto it = prefix_func_map.find(curtoken_->getType());
	if (it == prefix_func_map.end()) {
		return nullptr; // 예외 발생?
	} 

	PrefixFuncPtr prefix_func_ptr = it->second;   // map에서 함수 포인터 가져옴
	leftExpression = (this->*prefix_func_ptr)(); // 클래스 함수 포인터 → 함수 호출

	return leftExpression;
}

Parser::Parser(const Lexer& lexer) : lexer_(lexer), curtoken_(nullptr), peektoken_(nullptr) {
	initializeFuncMaps();
	advanceToken();
	advanceToken();
}

Parser::Parser(const std::string& input) : lexer_(input), curtoken_(nullptr), peektoken_(nullptr) {
	initializeFuncMaps();
	advanceToken();
	advanceToken();
}

Parser* Parser::createParserFromLexer(const Lexer& lexer) {
	Parser* p = new Parser(lexer);

	return p;
}

Parser* Parser::createParserFromInput(const std::string& input) {
	Parser* p = new Parser(input);
	return p;
}

//Parser::Parser(const Parser& copy){
//	
//}

Parser::~Parser() {
}
