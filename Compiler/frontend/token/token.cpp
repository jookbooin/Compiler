#include "token.h"

Token::Token(const TokenType &type, const std::string &literal) : type_(type), literal_(literal) {
}

Token::Token() : type_(TokenTypes::ILLEGAL), literal_("") {
}

Token::~Token() {
}

Token::Token(const Token &copy) : type_(copy.type_), literal_(copy.literal_) {
}

Token &Token::operator=(const Token &token) {
    // 자기 자신 검사
    if (this != &token) {
        type_ = token.type_;
        literal_ = token.literal_;
    }

    return *this;
}

Token::Token(Token &&src) noexcept
    : type_(std::move(src.type_)), literal_(std::move(src.literal_)) {
    logPrint("token 이동 생성자");
}

Token &Token::operator=(Token &&src) noexcept {
    logPrint("token 이동 대입 연산자");
    if (this != &src) {
        type_ = std::move(src.type_);
        literal_ = std::move(src.literal_);
    }
    return *this;
}

const TokenType &Token::getType() const {
    return type_;
}

const std::string &Token::getLiteral() const {
    return literal_;
}