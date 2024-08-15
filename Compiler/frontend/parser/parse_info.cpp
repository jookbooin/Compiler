#include "parse_info.h"

namespace Operator {

std::map<TokenType, Precedence> priority_map = {{TokenTypes::EQ, EQUALS},       // 2
                                                {TokenTypes::NOT_EQ, EQUALS},
                                                {TokenTypes::LT, LESSGREATER},  // 3
                                                {TokenTypes::GT, LESSGREATER},
                                                {TokenTypes::PLUS, SUM},        // 4
                                                {TokenTypes::MINUS, SUM},
                                                {TokenTypes::SLASH, PRODUCT},   // 5
                                                {TokenTypes::ASTERISK, PRODUCT},
                                                {TokenTypes::LPAREN, CALL}};    // 6
}