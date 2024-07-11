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
	
	extern std::map<TokenType, Priority> priority_map ;
}