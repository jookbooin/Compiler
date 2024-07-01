#include "identifier.h"

std::string Identifier::tokenLiteral() const {
	return "Identifier tokenLiteeral()";
}

void Identifier::expressionNode() const {

}

Identifier::Identifier(const Token* const token, const std::string& value) :token_(token), value_(value){
	logPrint("Identifier 생성자");
}

Identifier* Identifier::createIdentifierFromToken(const Token* const curtoken) {
	return new Identifier(curtoken,curtoken->getLiteral());
}

//Identifier::Identifier(const Identifier& copy) {
//
//}

Identifier::~Identifier() {

}