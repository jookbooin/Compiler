#pragma once
// ast

#include <string>
#include <vector>
#include "../../globalUtils.h"

#include "../token/token.h"
#include "node.h"
#include "statement.h"
#include "expression.h"
#include "identifier/identifier.h"


class Program : public Node { // 1개 생성
private:
	std::vector<Statement*> statements_; // 소유권-> vector? 

public:

	std::string getTokenLiteral() const override;
	void addStatement(Statement* const stm);

	Program();
	static Program* createProgram();
	//Program(const Program& copy);
	~Program();

	const std::vector<Statement*>& getStatements() const;
};

class LetStatement : public Statement {
private:
	const Token* let_token_;
	const Identifier* variable_name_;
	Expression* value_;

public:
	std::string getTokenLiteral() const override;
	void statementNode() const override;

	const Identifier* getVariableName() const;

	LetStatement(const Token* const token, const Token* const name);
	//LetStatement& operator=(const LetStatement& src);
	//LetStatement(LetStatement&& src) noexcept;
	//LetStatement& operator=(const LetStatement&& src) noexcept;

	//LetStatement(const LetStatement& copy);
	~LetStatement();
};

class ReturnStatement : public Statement {
private:
	const Token* return_token_;
	Expression* return_value_;
public:
	std::string getTokenLiteral() const override;
	void statementNode() const override;

	ReturnStatement(const Token* const token);
	//ReturnStatement& operator=(const ReturnStatement& src);
	//ReturnStatement(ReturnStatement&& src) noexcept;
	//ReturnStatement& operator=(const ReturnStatement&& src) noexcept;

	//ReturnStatement(const ReturnStatement& copy);
	~ReturnStatement();
};

class ExpressionStatement : public Statement {
private:
	const Token* expression_token_;
	Expression* expression_;

public:
	std::string getTokenLiteral() const override;
	void statementNode() const override;

	ExpressionStatement(const Token* expression_token, Expression* expression);
	//ExpressionStatement& operator=(const ExpressionStatement& src);
	//ExpressionStatement(ExpressionStatement&& src) noexcept;
	//ExpressionStatement& operator=(const ExpressionStatement&& src) noexcept;

	//ExpressionStatement(const ExpressionStatement& copy);
	~ExpressionStatement();

	Expression* getExpression() const;

};