#pragma once
// identifier

#include <string>
#include "../expression.h"
#include "../../token/token.h"
#include "../../globalUtils.h"

class Identifier : public Expression {
private:
	const Token* token_; // token 객체가 변하지 않는다 -> 소유권 주어야 하나?
	std::string value_;

public:
	std::string getTokenLiteral() const override;
	void expressionNode() const override;
	std::string getValue() const;

	static Identifier* createIdentifierFromToken(const Token* const curtoken);

	Identifier(const Token* const token);
	//Identifier& operator=(const Identifier& src);
	//Identifier(const Identifier&& src);
	//Identifier& operator=(const Identifier&& src);
	//Identifier(const Identifier& copy);
	~Identifier();

};