#include "lexer.h"

// front
Token* newToken(const TokenType tokenType, const char ch) {
	return new Token(tokenType, std::string(1, ch));
}

bool isLetter(const char ch) {
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool isDigit(const char ch) {
	return '0' <= ch && ch <= '9';
}

void Lexer::skipWhitespace() {
	while (ch_ == ' ' || ch_ == '\t' || ch_ == '\n' || ch_ == '\r') {
		readChar();
	}
}

// impl
// lexer가 보고 있는 위치를 다음으로 이동시킨다.
void Lexer::readChar() {
	if (readPosition_ >= input_.size()) {
		ch_ = 0;
	} else {
		ch_ = input_[readPosition_];
	}

	position_ = readPosition_;
	readPosition_ += 1;
}

// 
char Lexer::peekChar() {
	if (readPosition_ >= input_.size()) {
		return 0;
	} else {
		return input_[readPosition_];
	}
}

// 연속되는 식별자
std::string Lexer::readIdentifier() {
	int start_pos = position_;
	while (isLetter(ch_)) {
		readChar();
	}
	return input_.substr(start_pos, position_ - start_pos);
}

std::string Lexer::readNumber() {
	int start_pos = position_;
	while (isDigit(ch_)) {
		readChar();
	}
	return input_.substr(start_pos, position_ - start_pos);
}

Token* Lexer::nextToken() {
	Token* tok;
	skipWhitespace();

	switch (ch_) {
		case '=':
			if (peekChar() == '=') {
				char ch = ch_;
				readChar();
				std::string literal = std::string(1, ch) + std::string(1, ch_);
				tok = new Token(TokenTypes::EQ, literal);
			} else {
				tok = newToken(TokenTypes::ASSIGN, ch_);
			}
			break;
		case '+':
			tok = newToken(TokenTypes::PLUS, ch_);
			break;
		case '-':
			tok = newToken(TokenTypes::MINUS, ch_);
			break;
		case '!':
			if (peekChar() == '=') {
				char ch = ch_;
				readChar();
				std::string literal = std::string(1, ch) + std::string(1, ch_);
				tok = new Token(TokenTypes::NOT_EQ, literal);
			} else {
				tok = newToken(TokenTypes::BANG, ch_);
			}
			break;
		case '/':
			tok = newToken(TokenTypes::SLASH, ch_);
			break;
		case '*':
			tok = newToken(TokenTypes::ASTERISK, ch_);
			break;
		case '<':
			tok = newToken(TokenTypes::LT, ch_);
			break;
		case '>':
			tok = newToken(TokenTypes::GT, ch_);
			break;
		case ';':
			tok = newToken(TokenTypes::SEMICOLON, ch_);
			break;
		case ',':
			tok = newToken(TokenTypes::COMMA, ch_);
			break;
		case '{':
			tok = newToken(TokenTypes::LBRACE, ch_);
			break;
		case '}':
			tok = newToken(TokenTypes::RBRACE, ch_);
			break;
		case '(':
			tok = newToken(TokenTypes::LPAREN, ch_);
			break;
		case ')':
			tok = newToken(TokenTypes::RPAREN, ch_);
			break;
		case 0:
			tok = new Token(TokenTypes::kEOF, "");
			break;
		default:
			if (isLetter(ch_)) {
				std::string literal = readIdentifier();
				TokenType type = TokenTypes::lookupIdent(literal);

				tok = new Token(type, literal);
				return tok;
			} else if (isDigit(ch_)) {
				std::string literal = readNumber();
				TokenType type = TokenTypes::INT;

				tok = new Token(type, literal);
				return tok;
			} else {
				tok = newToken(TokenTypes::ILLEGAL, ch_);
			}
	}

	readChar();
	return tok;
}

int Lexer::getPosition() const {
	return position_;
}

int Lexer::getReadPosition() const {
	return readPosition_;
}

Lexer::Lexer(const std::string& input)
	: input_(input), position_(0), readPosition_(0) {
	logPrint("lexer 생성자");
	readChar();
}

Lexer* Lexer::createLexerFromInput(const std::string& input) {
	Lexer* lx = new Lexer(input);
	return lx;
}

Lexer::Lexer(const Lexer& copy) :input_(copy.input_), position_(copy.position_), readPosition_(copy.readPosition_), ch_(copy.ch_) {
	logPrint("lexer 복사생성자");
}

Lexer& Lexer::operator=(const Lexer& lexer) {

	logPrint("lexer operator=");

	if (this != &lexer) {
		input_ = lexer.input_;
		position_ = lexer.position_;
		readPosition_ = lexer.readPosition_;
		ch_ = lexer.ch_;
	}
	return *this;
}

Lexer::Lexer(Lexer&& src) noexcept :
	input_(std::move(src.input_)),
	position_(src.position_),
	readPosition_(src.readPosition_),
	ch_(src.ch_) {

	logPrint("lexer 이동생성자");
}

Lexer& Lexer::operator=(Lexer&& src) noexcept {
    logPrint("lexer 이동 대입 연산자");

    if (this != &src) {
        input_ = std::move(src.input_);
        position_ = src.position_;
        readPosition_ = src.readPosition_;
        ch_ = src.ch_;
    }

    return *this;
}

Lexer::~Lexer() {}

