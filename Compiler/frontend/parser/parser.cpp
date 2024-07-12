#include "parser.h"

// prefix
Expression* Parser::parseIdentifier() {
	const Token* identifier_token = curtoken_;

	return Identifier::createIdentifierFromToken(identifier_token);
}

Expression* Parser::parseIntegerLiteral() {
	
	const Token* integer_token = curtoken_;

	Expression* expression = nullptr;
	try {
		expression = IntegerLiteral::createIntegerLiteralFromToken(integer_token);
	} catch (const ParsingException& e) { // string -> int 변환 불가 메서드 
			addError(e.what());
	}

	return expression;
}

Expression* Parser::parsePrefixExpression() {

	// 1. '-, !' operator 토큰 따로 저장 
	const Token* prefix_token = curtoken_;

	// 2. - [ 5 ]
	advanceCurToken();

	/*
	* 3. '5' right_expression 생성
	*     '-, !' 의 RBP 전달 
	*/
	Expression* right_expression = parseExpressionWithLeftOperatorRBP(Operator::Precedence::PREFIX); 
	
	// [-5]
	PrefixExpression* prefix_expression = PrefixExpression::createPrefixExpressionOf(prefix_token, right_expression);

	return prefix_expression;
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

void Parser::advanceCurToken() {
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
		advanceCurToken();
		return true;
	}

	// 에러 발생 
	peekError(type);
	return false;
}

LetStatement* Parser::parseLetStatement() {

	// 1. [ let ] five =
	const Token* let_token = curtoken_;

	// let → [ five ] 
	if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::IDENT)) {
		return nullptr;
	}

	// 2. let [ five ] =
	const Token* variable_name_token = curtoken_;

	// five → [ = ]
	if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::ASSIGN)) {
		return nullptr;
	}

	// 3. let five [ = ] 
	while (!isCurTokenType(TokenTypes::SEMICOLON)) {
		advanceCurToken();
	}

	// 4. let five =  [ ; ]
	return new LetStatement(let_token, variable_name_token);
}

ReturnStatement* Parser::parseReturnStatement() {
	
	// 1. [ return ] exp
	const Token* return_token = curtoken_;
	ReturnStatement* returnStatement = new ReturnStatement(return_token);

	// return → [ exp ]
	advanceCurToken();
	return returnStatement;
}

ExpressionStatement* Parser::parseExpressionStatement() {
	
	/**
	*  [ 1 ] + 2
	*  [ 1 ] 
	*/
	const Token* expression_token = curtoken_;
	
	Expression* expression = parseExpressionWithLeftOperatorRBP(Operator::Precedence::LOWEST);

	ExpressionStatement* expression_statement = new ExpressionStatement(expression_token, expression); // 내부로 expression 소유권 전달
	
	if (isPeekTokenType(TokenTypes::SEMICOLON)) { // 
		advanceCurToken();
	}

	return expression_statement;
}

Statement* Parser::parseStatementFromCurToken() {

	if (isCurTokenType(TokenTypes::LET)) {
		return parseLetStatement();
	} else if (isCurTokenType(TokenTypes::RETURN)) {
		return parseReturnStatement();
	} else {
		return parseExpressionStatement();
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
		Statement* stmt = parseStatementFromCurToken();

		// 4. Program의 Statement에 추가 
		if (stmt != nullptr) {

			// 유일한 객체로 만들어 전달?
			root->addStatement(stmt);
		}

		// 5. 다음 token 호출
		advanceCurToken();
	}

	return root;
}

/// <summary>
/// 재귀적으로 동작 /
/// 매개변수는 왼쪽 연산자의 right_binding_power을 의미 / 
/// [ + (5) * ] : 5가 + , * 의 우선순위를 통해 어느것을 먼저 처리할지 결정/
/// </summary>
Expression* Parser::parseExpressionWithLeftOperatorRBP(int left_operator_RBP) { 
	
	Expression* leftExpression;

	// 1. prefix : + [5] *
	auto it = prefix_func_map.find(curtoken_->getType());
	if (it == prefix_func_map.end()) {
		addError("prefix_func_map에서 " + curtoken_->getType() + "을 찾을 수 없습니다."); // 
		return nullptr; // 예외 발생?
	} 

	PrefixFuncPtr prefix_func_ptr = it->second;   // map에서 함수 포인터 가져옴
	leftExpression = (this->*prefix_func_ptr)(); // 클래스 함수 포인터 → 함수 호출

	return leftExpression;
}

Parser::Parser(const Lexer& lexer) : lexer_(lexer), curtoken_(nullptr), peektoken_(nullptr) {
	initializeFuncMaps();
	advanceCurToken();
	advanceCurToken();
}

Parser::Parser(const std::string& input) : lexer_(input), curtoken_(nullptr), peektoken_(nullptr) {
	initializeFuncMaps();
	advanceCurToken();
	advanceCurToken();
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
