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

