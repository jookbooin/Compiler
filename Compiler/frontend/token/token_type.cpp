#include "token_type.h"

namespace TokenTypes {
std::map<std::string, TokenType> keywords = {{"let", LET},
                                             {"return", RETURN},
                                             {"true", TRUE},
                                             {"false", FALSE},
                                             {"fn", FUNCTION},
                                             {"if", IF},
                                             {"else", ELSE}};

TokenType getTokenTypeFromKeywords(const std::string ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) {
        return it->second;
    }

    return IDENT;
}
} // namespace TokenTypes