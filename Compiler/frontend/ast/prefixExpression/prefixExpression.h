#pragma once

#include "../expression.h"
#include "../../token/token.h"

class PrefixExpression : public Expression{
private:
	const Token* prefix_token_;
	std::string operator_; // "!", "-"
	Expression* right_;

	PrefixExpression(const Token* prefix_token, Expression* expression);
public:
	std::string getTokenLiteral() const;
	void expressionNode() const override;

	std::string getOperator() const;
	Expression* getRightExpression() const;

	static PrefixExpression* createPrefixExpressionOf(const Token* prefix_token, Expression* expression);

};