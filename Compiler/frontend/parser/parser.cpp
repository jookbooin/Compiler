#include "parser.h"

void Parser::peekError(const TokenType& type) {
	std::ostringstream oss;
	oss << "expect TokenType : " << peektoken_->getType() << ", actual : " << type ;

	errors_.push_back(oss.str());
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

Statement* Parser::parseStatement(const Token* const curtoken) {

	if (isCurTokenType(TokenTypes::LET)) {
		return parseLetStatement(curtoken);
	}

	// 2. RETURN 

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

Parser::Parser(const Lexer& lexer) : lexer_(lexer), curtoken_(nullptr), peektoken_(nullptr) {
	advanceToken();
	advanceToken();
}

Parser::Parser(const std::string& input) : lexer_(input), curtoken_(nullptr), peektoken_(nullptr) {
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
