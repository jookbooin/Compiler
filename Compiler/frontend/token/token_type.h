#pragma once

#include <string>
#include <map>

typedef std::string TokenType;

namespace TokenTypes {
	// 상수 정의
	const TokenType ILLEGAL = "ILLEGAL";
	const TokenType kEOF = "EOF";

	// 식별자 (Identifiers + literals)
	const TokenType IDENT = "IDENT";  // add, foobar, x, y, ...
	const TokenType INT = "INT";      // 1343456

	// 연산자 (Operators)
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


	// 구분자 (Delimiters)
	const TokenType COMMA = ",";
	const TokenType SEMICOLON = ";";
	const TokenType LPAREN = "(";
	const TokenType RPAREN = ")";
	const TokenType LBRACE = "{";
	const TokenType RBRACE = "}";

	// 예약어 (Keywords)
	const TokenType FUNCTION = "FUNCTION";
	const TokenType LET = "LET";
	const TokenType TRUE = "TRUE";
	const TokenType FALSE = "FALSE";
	const TokenType IF = "IF";
	const TokenType ELSE = "ELSE";
	const TokenType RETURN = "RETURN";

	extern std::map<std::string, TokenType> keywords ;

	// keywords 검색
	extern TokenType lookupIdent(const std::string ident);

}  // namespace TokenTypes