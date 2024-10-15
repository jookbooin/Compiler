#include "ifExpression.h"

IfExpression::IfExpression(std::unique_ptr<Token> if_token,
                           std::unique_ptr<Expression> condition,
                           std::unique_ptr<BlockStatement> consequence)
    : if_token_(std::move(if_token)), condition_(std::move(condition)),
      consequence_(std::move(consequence)), alternative_(nullptr) {
    logPrint("IfExpression 생성자");
}

IfExpression::~IfExpression() {
    logPrint("IfExpression 소멸자");
}

IfExpression::IfExpression(IfExpression &&src) noexcept
    : if_token_(std::move(src.if_token_)), condition_(std::move(src.condition_)),
      consequence_(std::move(src.consequence_)), alternative_(std::move(src.alternative_)) {
    logPrint("IfExpression 이동 생성자");
}

IfExpression &IfExpression::operator=(IfExpression &&src) noexcept {
    logPrint("IfExpression 이동 대입 연산자");
    if (this != &src) {
        if_token_ = std::move(src.if_token_);
        condition_ = std::move(src.condition_);
        consequence_ = std::move(src.consequence_);
        if (src.alternative_)
            alternative_ = std::move(src.alternative_);
    }

    return *this;
}

std::string IfExpression::getTokenLiteral() const {
    return if_token_->getLiteral();
}

void IfExpression::expressionNode() const {
}

const Expression *IfExpression::getCondition() const {
    return condition_.get();
}

const Statement *IfExpression::getConsequence() const {
    return consequence_.get();
}

const Statement *IfExpression::getAlternative() const {
    return alternative_.get();
}

void IfExpression::setAlternative(std::unique_ptr<BlockStatement> alternative) {
    alternative_ = std::move(alternative);
}

std::unique_ptr<IfExpression> IfExpression::createOf(std::unique_ptr<Token> if_token,
                                                     std::unique_ptr<Expression> condition,
                                                     std::unique_ptr<BlockStatement> consequence) {
    return std::make_unique<IfExpression>(
        std::move(if_token), std::move(condition), std::move(consequence));
}