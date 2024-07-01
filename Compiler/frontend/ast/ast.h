#pragma once
// ast

#include <string>
#include <vector>

#include "../token/token.h"
#include "node.h"
#include "statement.h"
#include "expression.h"
#include "identifier.h"

class Program : public Node { // 1개 생성
private:
	std::vector<Statement*> statements_;

public:

	std::string tokenLiteral() const override;
	void addStatement(Statement* const stm);

	Program();
	static Program* createProgram();
	//Program(const Program& copy);
	~Program();
};

class LetStatement : public Statement {
private:
	const Token* let_token_;
	const Identifier* variable_name_;
	Expression* value_;

public:
	std::string tokenLiteral() const override;
	void statementNode() const override;

	LetStatement(const Token* const token, const Token* const name);
	//LetStatement(const LetStatement& copy);
	~LetStatement();

};