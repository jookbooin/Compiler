#include "token.h"

std::map<std::string, TokenType> TokenTypes::keywords = {
	{"fn", TokenTypes::FUNCTION},
	{"let", TokenTypes::LET},
	{"true", TokenTypes::TRUE},
	{"false", TokenTypes::FALSE},
	{"if", TokenTypes::IF},
	{"else", TokenTypes::ELSE},
	{"return", TokenTypes::RETURN}
};

// keywords 검색
TokenType TokenTypes::lookupIdent(const std::string ident) {
	auto it = TokenTypes::keywords.find(ident);
	if (it != TokenTypes::keywords.end()) {
		return it->second;
	}

	return TokenTypes::IDENT;
}

TokenType Token::getType() const {
	return type_;
}

std::string Token::getLiteral() const {
	return literal_;
}

Token::Token(const TokenType type, const std::string literal)
	: type_(type), literal_(literal) {
}

Token::Token() : type_(TokenTypes::ILLEGAL), literal_("") {}

//Token::Token(const std::string literal) : literal_(literal){}