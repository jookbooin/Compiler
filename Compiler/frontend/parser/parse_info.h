#pragma once

#include "../token/token.h"

namespace Operator {

enum Precedence {
    LOWEST = 1,
    EQUALS,      // ==
    LESSGREATER, // > or <
    SUM,         // +
    PRODUCT,     // *
    PREFIX,      // -X or !X
    CALL         // myFunction(X)
};

extern std::map<TokenType, Precedence> priority_map;
} // namespace Operator