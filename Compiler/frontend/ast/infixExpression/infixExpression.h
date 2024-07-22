#pragma once

#include "../expression.h"
#include "../../token/token.h"

class InfixExpression : public Expression {
private:
	const Token* infix_token_;
	Expression* left_expression_;
	std::string operator_;
	Expression* right_expression_;

	InfixExpression(const Token* infix_token, Expression* left, Expression* right);
public:
	std::string getTokenLiteral() const;
	void expressionNode() const override;

	std::string getOperator() const;
	Expression* getLeftExpression();
	Expression* getRightExpression();

	static InfixExpression* createInfixExpressionOf(const Token* infix_token, Expression* left, Expression* right);

};