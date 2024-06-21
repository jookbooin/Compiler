#pragma once

#include <string>
#include <map>

typedef std::string TokenType;

namespace TokenTypes {
	// 상수 정의
	const TokenType ILLEGAL = "ILLEGAL";
	const TokenType kEOF = "EOF";

	// Identifiers + literals
	const TokenType IDENT = "IDENT";  // add, foobar, x, y, ...
	const TokenType INT = "INT";      // 1343456

	// Operators
	const TokenType ASSIGN = "=";
	const TokenType PLUS = "+";
	const TokenType MINUS = "-";
	const TokenType BANG = "!";
	const TokenType ASTERISK = "*";
	const TokenType SLASH = "/";
	const TokenType LT = "<";
	const TokenType GT = ">";
	const TokenType EQ = "==";
	const TokenType NOT_EQ = "!=";

	// Delimiters
	const TokenType COMMA = ",";
	const TokenType SEMICOLON = ";";
	const TokenType LPAREN = "(";
	const TokenType RPAREN = ")";
	const TokenType LBRACE = "{";
	const TokenType RBRACE = "}";

	// Keywords
	const TokenType FUNCTION = "FUNCTION";
	const TokenType LET = "LET";
	const TokenType TRUE = "TRUE";
	const TokenType FALSE = "FALSE";
	const TokenType IF = "IF";
	const TokenType ELSE = "ELSE";
	const TokenType RETURN = "RETURN";

	std::map <std::string, TokenType> keywords = {
		{"fn",FUNCTION},
		{"fn", FUNCTION},
		{"let", LET},
		{"true", TRUE},
		{"false", FALSE},
		{"if", IF},
		{"else", ELSE},
		{"return", RETURN}
	};

	// keywords 검색
	TokenType lookupIdent(const std::string ident) {
		auto it = TokenTypes::keywords.find(ident);
		if (it != TokenTypes::keywords.end()) {
			return it->second;
		}

		return TokenTypes::IDENT;
	}

}  // namespace TokenTypes

class Token {
private:
	TokenType type_;
	std::string literal_;

public:
	Token();
	//Token(const std::string literal);
	Token(const TokenType type, const std::string literal);
};
