#pragma once

#include "../token/token.h"

namespace Operator {

	enum Priority {
		LOWEST = 1,  
		EQUALS,      // ==
		LESSGREATER, // > or <
		SUM,         // +
		PRODUCT,     // *
		PREFIX,      // -X or !X
		CALL         // myFunction(X)
	};

	std::map<TokenType, Priority> priority_map = {
		{TokenTypes::EQ,       EQUALS},
		{TokenTypes::NOT_EQ,   EQUALS},
		{TokenTypes::LT,       LESSGREATER},
		{TokenTypes::GT,       LESSGREATER},
		{TokenTypes::PLUS,     SUM},
		{TokenTypes::MINUS,    SUM},
		{TokenTypes::SLASH,    PRODUCT},
		{TokenTypes::ASTERISK, PRODUCT},
		{TokenTypes::LPAREN,   CALL}
	};
}