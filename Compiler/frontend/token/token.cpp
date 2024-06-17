#include "token.h"

Token::Token() : type_(TokenTypes::ILLEGAL), literal_("") {}

Token::Token(const TokenType type, const std::string literal)
    : type_(type), literal_(literal) {}