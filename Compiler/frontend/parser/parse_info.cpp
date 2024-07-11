#include "parse_info.h"


namespace Operator {

	std::map<TokenType, Priority> priority_map = {
		{TokenTypes::EQ,       EQUALS},
		{TokenTypes::NOT_EQ,   EQUALS},
		{TokenTypes::LT,       LESSGREATER},
		{TokenTypes::GT,       LESSGREATER},
		{TokenTypes::PLUS,     SUM},
		{TokenTypes::MINUS,    SUM},
		{TokenTypes::SLASH,    PRODUCT},
		{TokenTypes::ASTERISK, PRODUCT},
		{TokenTypes::LPAREN,  CALL}
	};
}