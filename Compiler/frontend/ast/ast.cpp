#include "ast.h"

// Program

// test

const std::vector<Statement*>& Program::getStatements() const {
    return statements_;
}
//


std::string Program::getTokenLiteral() const {
	if (!statements_.empty() && statements_.front() != nullptr) {
		return statements_.front()->getTokenLiteral();
	}

	return "Program empty!";
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
std::string LetStatement::getTokenLiteral() const {
	return let_token_->getLiteral();
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


