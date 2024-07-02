#include "identifier.h"

std::string Identifier::getTokenLiteral() const {
	return token_->getLiteral();
}

void Identifier::expressionNode() const {

}

Identifier::Identifier(const Token* const token, const std::string& value) :token_(token), value_(value) {
	logPrint("Identifier 생성자");
}

std::string Identifier::getValue() const {
	return value_;
}

Identifier* Identifier::createIdentifierFromToken(const Token* const curtoken) {
	return new Identifier(curtoken, curtoken->getLiteral());
}

//Identifier::Identifier(const Identifier& copy) {
//
//}

Identifier::~Identifier() {

}