#pragma once
// lexer

#include <string>

#include "../token/token.h"

class Lexer {
 private:
  std::string input_;
  int position_; // 현재 위치
  int readPosition_; // 다음 위치
  char ch_;

 public:
  void skipWhitespace();
  void readChar();
  std::string readIdentifier();
  std::string readNumber();
  Token* nextToken();

  int getPosition() const;
  int getReadPosition() const;

  Lexer(const Lexer& copy);
  Lexer(const std::string& input);
};
