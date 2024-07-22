#include "integer_literal.h"

std::string IntegerLiteral::getTokenLiteral() const {
	return std::to_string(value_);
}

void IntegerLiteral::expressionNode() const {

}

int IntegerLiteral::getValue() const {
	return value_;
}

IntegerLiteral* IntegerLiteral::createIntegerLiteralFromToken(const Token* curtoken) {

	if (is_digit(curtoken ->getLiteral())) {
		return new IntegerLiteral(curtoken);
	} else {
		
		// Token을 지워야 하나?
		std::string msg = "could not parse \"" + curtoken->getLiteral() + "\" as integer";
		throw new ParsingException(msg);
	}
	
}

IntegerLiteral::IntegerLiteral(const IntegerLiteral& copy) {}

//IntegerLiteral::IntegerLiteral& operator=(const IntegerLiteral& src) {}

IntegerLiteral::IntegerLiteral(const IntegerLiteral&& src) {}

//IntegerLiteral::IntegerLiteral& operator=(const IntegerLiteral&& src) {}

IntegerLiteral::IntegerLiteral(const Token* token) : integer_token_(token), value_(stoi(token->getLiteral())) {
	logPrint("IntegerLiteral 일반 생성자");
}

IntegerLiteral::~IntegerLiteral() {

}