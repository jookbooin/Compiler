#pragma once

#include "../token/token.h"

namespace Operator {

enum Precedence {
    LOWEST = 1,  // )
    EQUALS,      // == or !=
    LESSGREATER, // > or <
    SUM,         // + or -
    PRODUCT,     // * or /
    PREFIX,      // -X or !X
    CALL         // ( 
};

extern std::map<TokenType, Precedence> priority_map;
} // namespace Operator