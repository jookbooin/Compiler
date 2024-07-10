#pragma once
// lexer

#include <string>

#include "../token/token.h"
#include "../../globalUtils.h"

class Lexer {
private:
	std::string input_;
	int position_; // 현재 위치
	int readPosition_; // 다음 위치
	char ch_;
	
public:
	void skipWhitespace();
	void readChar();
	char peekChar();
	std::string readIdentifier();
	std::string readNumber();
	Token* nextToken();

	int getPosition() const;
	int getReadPosition() const;

	Lexer(const std::string& input);
	static Lexer* createLexerFromInput(const std::string& input);
	
	Lexer& operator=(const Lexer& lexer);

	Lexer(Lexer&& src) noexcept; // 이동 생성자
	Lexer& operator=(Lexer&& src) noexcept ;

	Lexer(const Lexer& copy);
	~Lexer();

};
