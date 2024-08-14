#include "infixExpression.h"

InfixExpression::InfixExpression(std::unique_ptr<Token> op_token,
                                 std::unique_ptr<Expression> left,
                                 std::unique_ptr<Expression> right)
    : op_token_(std::move(op_token)), operator_(op_token_->getLiteral()),
      left_expression_(std::move(left)), right_expression_(std::move(right)) {
    logPrint("InfixExpression 생성자");
}

InfixExpression::~InfixExpression() {
    logPrint("InfixExpression 소멸자");
}

std::string InfixExpression::getTokenLiteral() const {
    return op_token_->getLiteral();
}

void InfixExpression::expressionNode() const {
}

std::string InfixExpression::getOperator() const {
    return operator_;
}

const Expression *InfixExpression::getLeftExpression() const {
    return left_expression_.get();
}

const Expression *InfixExpression::getRightExpression() const {
    return right_expression_.get();
}

std::unique_ptr<InfixExpression>
InfixExpression::createUniqueOf(std::unique_ptr<Token> op_token,
                                std::unique_ptr<Expression> left,
                                std::unique_ptr<Expression> right) {
    return std::make_unique<InfixExpression>(
        std::move(op_token), std::move(left), std::move(right));
}