#include "parser.h"

void Parser::MoveNextToken() {
	curtoken_ = peektoken_;
	peektoken_ = lexer_.nextToken();
}

bool Parser::IsCurTokenType(const TokenType& type) {
	return curtoken_->getType() == type;
}

bool Parser::IsPeekTokenType(const TokenType& type) {
	return peektoken_->getType() == type;
}

bool Parser::moveNextIfPeekTokenTypeIs(const TokenType& type) {
	if (IsPeekTokenType(type)) {
		MoveNextToken();
		return true;
	}

	// 에러 발생 
	return false;
}

LetStatement* Parser::parseLetStatement(const Token* const let_token) {

	// 1. [let] five
	if (!moveNextIfPeekTokenTypeIs(TokenTypes::IDENT)) {
		return nullptr;
	}

	// 2. let [five]
	Token* variable_name_token = curtoken_;

	//if (!IsPeekTokenType(TokenTypes::ASSIGN)) {
	if (!moveNextIfPeekTokenTypeIs(TokenTypes::ASSIGN)) {
		return nullptr;
	}

	// 3. let five [ = ] 
	while (!IsCurTokenType(TokenTypes::SEMICOLON)) {
		MoveNextToken();
	}

	// 4. let five =  [ ; ]
	return new LetStatement(let_token, variable_name_token);
}

Statement* Parser::parseStatement(const Token* const curtoken) {

	if (IsCurTokenType(TokenTypes::LET)) {
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
	while (!IsCurTokenType(TokenTypes::kEOF)) {

		// 3. let, return 명령문 파싱
		Statement* stmt = parseStatement(curtoken_);

		// 4. Program의 Statement에 추가 
		if (stmt != nullptr) {
			root->addStatement(stmt);
		}

		// 5. 다음 token 호출
		MoveNextToken();
	}

	return root;
}

Parser::Parser(const Lexer& lexer) : lexer_(lexer), curtoken_(nullptr), peektoken_(nullptr) {
	MoveNextToken();
	MoveNextToken();
}

Parser::Parser(const std::string& input) : lexer_(input), curtoken_(nullptr), peektoken_(nullptr) {
	MoveNextToken();
	MoveNextToken();
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
