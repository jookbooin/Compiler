#include "infixExpression.h"

InfixExpression::InfixExpression(std::unique_ptr<Token> infix_token,
                                 std::unique_ptr<Expression> left,
                                 std::unique_ptr<Expression> right)
    : infix_token_(std::move(infix_token)), operator_(infix_token_->getLiteral()),
      left_expression_(std::move(left)), right_expression_(std::move(right)) {
    logPrint("InfixExpression 생성자");
}

InfixExpression::~InfixExpression() {
    logPrint("InfixExpression 소멸자");
}

std::string InfixExpression::getTokenLiteral() const {
    return infix_token_->getLiteral();
}

void InfixExpression::expressionNode() const {
}

std::string InfixExpression::getOperator() const {
    return operator_;
}

// Expression* InfixExpression::getLeftExpression() {
//	return left_expression_;
// }
//
// Expression* InfixExpression::getRightExpression() {
//	return right_expression_;
// }

std::unique_ptr<InfixExpression>
InfixExpression::createUniqueOf(std::unique_ptr<Token> infix_token,
                                std::unique_ptr<Expression> left,
                                std::unique_ptr<Expression> right) {
    return std::make_unique<InfixExpression>(
        std::move(infix_token), std::move(left), std::move(right));
}