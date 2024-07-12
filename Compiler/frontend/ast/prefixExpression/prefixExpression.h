#pragma once

#include "../expression.h"
#include "../../token/token.h"

class PrefixExpression : public Expression{
private:
	const Token* prefix_token_;
	std::string operator_; // "!", "-"
	Expression* right_;

public:
	std::string getTokenLiteral() const;
	void expressionNode() const override;
};