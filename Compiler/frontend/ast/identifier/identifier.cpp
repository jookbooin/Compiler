#include "identifier.h"

std::string Identifier::getTokenLiteral() const {
	return token_->getLiteral();
}

void Identifier::expressionNode() const {

}

Identifier::Identifier(const Token* const token) :token_(token), value_(token->getLiteral()) {
	logPrint("Identifier 생성자");
}

std::string Identifier::getValue() const {
	return value_;
}

Identifier* Identifier::createIdentifierFromToken(const Token* const curtoken) {
	return new Identifier(curtoken);
}

//Identifier& Identifier::operator=(const Identifier& src) {}

//Identifier::Identifier(const Identifier&& src) {}

//Identifier& Identifier::operator=(const Identifier&& src) {}

//Identifier::Identifier(const Identifier& copy) {}

Identifier::~Identifier() {

}