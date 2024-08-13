#include "integer_literal.h"

IntegerLiteral::IntegerLiteral(std::unique_ptr<Token> token) : value_(stoi(token->getLiteral())) {
    integer_token_ = std::move(token);
    logPrint("IntegerLiteral 일반 생성자");
}

IntegerLiteral::~IntegerLiteral() {
}

IntegerLiteral::IntegerLiteral(IntegerLiteral &&src) noexcept : value_(src.value_) {
    integer_token_ = std::move(src.integer_token_);
}

std::string IntegerLiteral::getTokenLiteral() const {
    return std::to_string(value_);
}

void IntegerLiteral::expressionNode() const {
}

int IntegerLiteral::getValue() const {
    return value_;
}

std::unique_ptr<IntegerLiteral> IntegerLiteral::createUniqueFrom(std::unique_ptr<Token> curtoken) {

    if (is_digit(curtoken->getLiteral())) {
        return std::make_unique<IntegerLiteral>(std::move(curtoken));
    } else {

        // Token을 지워야 하나?
        std::string msg = "could not parse \"" + curtoken->getLiteral() + "\" as integer";
        throw new ParsingException(msg);
    }
}