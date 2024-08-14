#include "prefixExpression.h"

PrefixExpression::PrefixExpression(std::unique_ptr<Token> prefix_token,
                                   std::unique_ptr<Expression> right)
    : operator_(prefix_token->getLiteral()), right_expression_(std::move(right)) {
    logPrint("PrefixExpression 생성자");
    prefix_token_ = std::move(prefix_token);
}

PrefixExpression::~PrefixExpression() {
    logPrint("PrefixExpression 소멸자");
}

std::string PrefixExpression::getTokenLiteral() const {
    return prefix_token_->getLiteral();
}

void PrefixExpression::expressionNode() const {
}

std::string PrefixExpression::getOperator() const {
    return operator_;
}

const Expression *PrefixExpression::getRightExpression() const {
    return right_expression_.get();
}

std::unique_ptr<PrefixExpression>
PrefixExpression::createUniqueOf(std::unique_ptr<Token> prefix_token,
                                 std::unique_ptr<Expression> right) {
    return std::make_unique<PrefixExpression>(std::move(prefix_token), std::move(right));
}