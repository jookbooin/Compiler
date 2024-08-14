#include "token_type.h"

namespace TokenTypes {
std::map<std::string, TokenType> keywords = {{"fn", FUNCTION},
                                             {"let", LET},
                                             {"true", TRUE},
                                             {"false", FALSE},
                                             {"if", IF},
                                             {"else", ELSE},
                                             {"return", RETURN}};

TokenType lookupIdent(const std::string ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) {
        return it->second;
    }

    return IDENT;
}
} // namespace TokenTypes