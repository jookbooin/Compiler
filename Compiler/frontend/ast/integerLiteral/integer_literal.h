#pragma once

#include "../../globalUtils.h"
#include "../expression.h"
#include "../../token/token.h"
#include "../../exception/exception.h"


class IntegerLiteral : public Expression {
private:
	const Token* integer_token_; // { type_ = 'INT', literal_ = "5" }
	int value_;					 // 5
public:

	std::string getTokenLiteral() const;
	void expressionNode() const override;
	int getValue() const;

	static IntegerLiteral* createIntegerLiteralFromToken(const Token* curtoken);

	IntegerLiteral(const IntegerLiteral& copy);
	//IntegerLiteral& operator=(const IntegerLiteral& src);
	IntegerLiteral(const IntegerLiteral&& src);
	//IntegerLiteral& operator=(const IntegerLiteral&& src);

	IntegerLiteral(const Token* token);
	~IntegerLiteral();
};