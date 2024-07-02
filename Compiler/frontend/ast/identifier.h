#pragma once
// identifier

#include <string>
#include "Expression.h"
#include "../token/token.h"
#include "../../globalUtils.h"

class Identifier : public Expression {
private:
	const Token* token_; // token 객체가 변하지 않는다
	std::string value_;

public:
	std::string getTokenLiteral() const override;
	std::string getValue() const;
	void expressionNode() const override;

	static Identifier* createIdentifierFromToken(const Token* const curtoken);
	Identifier(const Token* const token, const std::string& value);
	//Identifier(const Identifier& copy);
	~Identifier();

};