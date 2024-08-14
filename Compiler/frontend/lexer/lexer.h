#pragma once
// lexer

#include <string>

#include "../../globalUtils.h"
#include "../token/token.h"

class Lexer {
  private:
    std::string input_;
    int position_;     // 현재 위치
    int readPosition_; // 다음 위치
    char ch_;

  public:
    Lexer(const std::string &input);
    ~Lexer();
    Lexer(const Lexer &copy);
    Lexer &operator=(const Lexer &lexer);
    Lexer(Lexer &&src) noexcept; // 이동 생성자
    Lexer &operator=(Lexer &&src) noexcept;

    void skipWhitespace();
    void readChar();
    char peekChar();
    std::string readIdentifier();
    std::string readNumber();
    std::unique_ptr<Token> nextToken();

    const std::string &getInput() const;
    int getPosition() const;
    int getReadPosition() const;
};
