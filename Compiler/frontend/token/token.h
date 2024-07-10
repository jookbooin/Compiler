#pragma once

#include "token_type.h"

class Token {
private:
	TokenType type_;
	std::string literal_;

public:
	Token();

	//Token(const std::string literal);
	TokenType getType() const;
	std::string getLiteral() const;

	Token(const TokenType type, const std::string literal);
	Token& operator=(const Token& token);
	Token(const Token&& token) noexcept;
	Token& operator=(const Token&& src) noexcept;
	Token(const Token& copy);
	~Token();
};
