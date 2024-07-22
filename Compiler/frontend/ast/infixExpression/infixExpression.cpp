#include "infixExpression.h"

std::string InfixExpression::getTokenLiteral() const {
	return infix_token_->getLiteral();
}

void InfixExpression::expressionNode() const {

}

std::string InfixExpression::getOperator() const {
	return operator_;
}

Expression* InfixExpression::getLeftExpression() {
	return left_expression_;
}

Expression* InfixExpression::getRightExpression() {
	return right_expression_;
}

InfixExpression::InfixExpression(const Token* infix_token, Expression* left, Expression* right) :
	infix_token_(infix_token),
	operator_(infix_token_->getLiteral()),
	left_expression_(left),
	right_expression_(right) {

}

InfixExpression* InfixExpression::createInfixExpressionOf(const Token* infix_token, Expression* left, Expression* right) {
	return new InfixExpression(infix_token, left, right);
}