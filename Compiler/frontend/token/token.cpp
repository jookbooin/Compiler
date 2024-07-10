#include "token.h"

TokenType Token::getType() const {
	return type_;
}

std::string Token::getLiteral() const {
	return literal_;
}

Token::Token(const TokenType type, const std::string literal) : type_(type), literal_(literal) {
}

Token::Token() : type_(TokenTypes::ILLEGAL), literal_("") {}

Token& Token::operator=(const Token& token) {
	// 자기 자신 검사 
	if (this != &token) {
		type_ = token.type_;
		literal_ = token.literal_;
	}

	return *this;
}

Token::Token(const Token&& token) noexcept {

}

Token& Token::operator=(const Token&& src) noexcept {

}

Token::Token(const Token& copy) : type_(copy.type_), literal_(copy.literal_) {}

Token::~Token() {}
//Token::Token(const std::string literal) : literal_(literal){}