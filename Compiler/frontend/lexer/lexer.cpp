#include "lexer.h"

// front
std::unique_ptr<Token> createUniqueTokenOf(const TokenType &tokenType, const char &ch) {
    return std::make_unique<Token>(tokenType, std::string(1, ch));
}

std::unique_ptr<Token> createUniqueTokenOf(const TokenType &tokenType, const std::string &str) {
    return std::make_unique<Token>(tokenType, str);
}

bool isLetter(const char ch) {
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool isDigit(const char ch) {
    return '0' <= ch && ch <= '9';
}

Lexer::Lexer(const std::string &input) : input_(input), position_(0), readPosition_(0) {
    logPrint("lexer 생성자");
    std::cout << this << std::endl;
    readChar();
}

Lexer::~Lexer() {
    logPrint("lexer 소멸자");
    std::cout << this << std::endl;
}

Lexer::Lexer(const Lexer &copy)
    : input_(copy.input_), position_(copy.position_), readPosition_(copy.readPosition_),
      ch_(copy.ch_) {
    logPrint("lexer 복사생성자");
}

Lexer &Lexer::operator=(const Lexer &lexer) {

    logPrint("lexer 대입 연산자");

    if (this != &lexer) {
        input_ = lexer.input_;
        position_ = lexer.position_;
        readPosition_ = lexer.readPosition_;
        ch_ = lexer.ch_;
    }
    return *this;
}

Lexer::Lexer(Lexer &&src) noexcept
    : input_(std::move(src.input_)), position_(src.position_), readPosition_(src.readPosition_),
      ch_(src.ch_) {

    logPrint("lexer 이동생성자");
    std::cout << this << std::endl;
}

Lexer &Lexer::operator=(Lexer &&src) noexcept {
    logPrint("lexer 이동 대입 연산자");

    if (this != &src) {
        input_ = std::move(src.input_);
        position_ = src.position_;
        readPosition_ = src.readPosition_;
        ch_ = src.ch_;
    }

    return *this;
}

void Lexer::skipWhitespace() {
    while (ch_ == ' ' || ch_ == '\t' || ch_ == '\n' || ch_ == '\r') {
        readChar();
    }
}

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

std::unique_ptr<Token> Lexer::nextToken() {
    std::unique_ptr<Token> tok;
    skipWhitespace();

    switch (ch_) {
    case '=':
        if (peekChar() == '=') {
            char ch = ch_;
            readChar();
            std::string literal = std::string(1, ch) + std::string(1, ch_);
            tok = createUniqueTokenOf(TokenTypes::EQ, literal);
        } else {
            tok = createUniqueTokenOf(TokenTypes::ASSIGN, ch_);
        }
        break;
    case '+':
        tok = createUniqueTokenOf(TokenTypes::PLUS, ch_);
        break;
    case '-':
        tok = createUniqueTokenOf(TokenTypes::MINUS, ch_);
        break;
    case '!':
        if (peekChar() == '=') {
            char ch = ch_;
            readChar();
            std::string literal = std::string(1, ch) + std::string(1, ch_);
            tok = createUniqueTokenOf(TokenTypes::NOT_EQ, literal);
        } else {
            tok = createUniqueTokenOf(TokenTypes::BANG, ch_);
        }
        break;
    case '/':
        tok = createUniqueTokenOf(TokenTypes::SLASH, ch_);
        break;
    case '*':
        tok = createUniqueTokenOf(TokenTypes::ASTERISK, ch_);
        break;
    case '<':
        tok = createUniqueTokenOf(TokenTypes::LT, ch_);
        break;
    case '>':
        tok = createUniqueTokenOf(TokenTypes::GT, ch_);
        break;
    case ';':
        tok = createUniqueTokenOf(TokenTypes::SEMICOLON, ch_);
        break;
    case ',':
        tok = createUniqueTokenOf(TokenTypes::COMMA, ch_);
        break;
    case '{':
        tok = createUniqueTokenOf(TokenTypes::LBRACE, ch_);
        break;
    case '}':
        tok = createUniqueTokenOf(TokenTypes::RBRACE, ch_);
        break;
    case '(':
        tok = createUniqueTokenOf(TokenTypes::LPAREN, ch_);
        break;
    case ')':
        tok = createUniqueTokenOf(TokenTypes::RPAREN, ch_);
        break;
    case 0:
        tok = createUniqueTokenOf(TokenTypes::kEOF, "");
        break;
    default:
        if (isLetter(ch_)) {
            std::string literal = readIdentifier();
            TokenType type = TokenTypes::getTokenTypeFromKeywords(
                literal); // let, func, boolean, if, else, Ident

            tok = createUniqueTokenOf(type, literal);
            return tok;
        } else if (isDigit(ch_)) {
            std::string literal = readNumber();
            TokenType type = TokenTypes::INT;

            tok = createUniqueTokenOf(type, literal);
            return tok;
        } else {
            tok = createUniqueTokenOf(TokenTypes::ILLEGAL, ch_);
        }
    }

    readChar();
    return tok;
}

const std::string &Lexer::getInput() const {
    return input_;
}

int Lexer::getPosition() const {
    return position_;
}

int Lexer::getReadPosition() const {
    return readPosition_;
}
