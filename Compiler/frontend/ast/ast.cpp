#include "ast.h"

// Program
const std::vector<Statement*>& Program::getStatements() const {
	return statements_;
}

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

const Identifier* LetStatement::getVariableName() const {
	return variable_name_;
}

LetStatement::LetStatement(const Token * token, const Token* const name) : let_token_(token), variable_name_(Identifier::createIdentifierFromToken(name)), value_(nullptr) {}

//LetStatement& LetStatement::operator=(const LetStatement & src) {}

//LetStatement::LetStatement(LetStatement && src) noexcept {}

//LetStatement& LetStatement::operator=(const LetStatement && src) noexcept {}

//LetStatement::LetStatement(const LetStatement & copy) {}

LetStatement::~LetStatement() {
	delete let_token_;
	delete variable_name_;
}

// Return
ReturnStatement::ReturnStatement(const Token* const token) : return_token_(token), return_value_(nullptr) {}

std::string ReturnStatement::getTokenLiteral() const {
	return return_token_->getLiteral();
}

void ReturnStatement::statementNode() const {

}

//ReturnStatement& operator=(const ReturnStatement& src) {}

//ReturnStatement::ReturnStatement(ReturnStatement && src) noexcept {}

//ReturnStatement& operator=(const ReturnStatement&& src) noexcept {}

//ReturnStatement::ReturnStatement(const ReturnStatement & copy) {}

ReturnStatement::~ReturnStatement() {

}

// Expression
std::string ExpressionStatement::getTokenLiteral() const {
	return expression_token_->getLiteral();
}

void ExpressionStatement::statementNode() const {

}

ExpressionStatement::ExpressionStatement(const Token * expression_token, Expression * expression) : expression_token_(expression_token), expression_(expression) {
	logPrint("ExpressionStatement 생성자");
}

//ExpressionStatement::ExpressionStatement(const ExpressionStatement & copy) {
//	logPrint("ExpressionStatement 복사 생성자");
//}

//ExpressionStatement& ExpressionStatement::operator=(const ExpressionStatement& src) {
//	logPrint("ExpressionStatement 대입 연산자");
//
//}

//ExpressionStatement::ExpressionStatement(ExpressionStatement && src) noexcept {
//	logPrint("ExpressionStatement 이동 생성자");
//}

//ExpressionStatement& ExpressionStatement::operator=(const ExpressionStatement&& src) noexcept {
//	logPrint("ExpressionStatement 이동 대입 연산자");
//
//}

ExpressionStatement::~ExpressionStatement() {

}

Expression* ExpressionStatement::getExpression() const {
    return expression_;
}