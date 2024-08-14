#pragma once

#include "../../globalUtils.h"
#include "token_type.h"

class Token {
  private:
    TokenType type_;
    std::string literal_;

  public:
    Token();
    Token(const TokenType &type, const std::string &literal);
    ~Token();
    Token(const Token &copy);
    Token &operator=(const Token &token);
    Token(Token &&src) noexcept;
    Token &operator=(Token &&src) noexcept;

    const TokenType &getType() const;
    const std::string &getLiteral() const;
};
