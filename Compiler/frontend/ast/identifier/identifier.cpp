#include "identifier.h"

Identifier::Identifier(std::unique_ptr<Token> token) : value_(token->getLiteral()) {
    token_ = std::move(token);
    logPrint("Identifier 생성자");
}

Identifier::~Identifier() {
}

Identifier::Identifier(Identifier &&src) noexcept
    : token_(std::move(src.token_)), value_(std::move(src.value_)) {
    logPrint("Identifier 이동 생성자");
}

// 이동 대입 연산자 구현
Identifier &Identifier::operator=(Identifier &&src) noexcept {
    if (this != &src) { // 자기 대입 방지
        token_ = std::move(src.token_);
        value_ = std::move(src.value_);
        logPrint("Identifier 이동 대입 연산자");
    }
    return *this;
}

std::string Identifier::getTokenLiteral() const {
    return token_->getLiteral();
}

void Identifier::expressionNode() const {
}

std::string Identifier::getValue() const {
    return value_;
}

std::unique_ptr<Identifier> Identifier::createUniqueFrom(std::unique_ptr<Token> curtoken) {
    return std::make_unique<Identifier>(std::move(curtoken));
}
