#include "boolean.h"

Boolean::Boolean(std::unique_ptr<Token> token, bool flag)
    : bool_token_(std::move(token)), value_(flag) {
    logPrint("Boolean 생성자");
}

Boolean::~Boolean() {
    logPrint("Boolean 소멸자");
}

Boolean::Boolean(Boolean &&src) noexcept
    : bool_token_(std::move(src.bool_token_)), value_(src.value_) {
    logPrint("Boolean 이동 생성자");
}

// 이동 대입 연산자
Boolean &Boolean::operator=(Boolean &&src) noexcept {
    if (this != &src) {
        bool_token_ = std::move(src.bool_token_);
        value_ = src.value_;
        logPrint("Boolean 이동 대입 연산자");
    }
    return *this;
}

std::string Boolean::getTokenLiteral() const {
    return bool_token_->getLiteral(); // true, false
}

void Boolean::expressionNode() const {
}

bool Boolean::getValue() const {
    return value_;
}

std::unique_ptr<Boolean> Boolean::createUniqueOf(std::unique_ptr<Token> token, bool value) {
    return std::make_unique<Boolean>(std::move(token), value);
}