#include "ast.h"

// Program
std::string Program::tokenLiteral() const {
	return "Program tokenLiteral()";
}

void Program::addStatement(Statement* const stm) {
	statements_.push_back(stm);
}

//Program::Program(const Program& copy) {
//
//}

Program::Program() {}

Program* Program::createProgram() {
	return new Program();
}

Program::~Program() {}


// LetStatement 
std::string LetStatement::tokenLiteral() const {
	return "letStatement tokenLiteral()";
}

void LetStatement::statementNode() const {
	
}

LetStatement::LetStatement(const Token* token, const Token* const name) : let_token_(token), variable_name_(Identifier::createIdentifierFromToken(name)),value_(nullptr) {}

//LetStatement::LetStatement(const LetStatement& copy) {
//
//}

LetStatement::~LetStatement() {
	delete let_token_;
	delete variable_name_;
}


