#include "prefixExpression.h"

std::string PrefixExpression::getTokenLiteral() const {
	return prefix_token_->getLiteral();
}

void PrefixExpression::expressionNode() const {

}

PrefixExpression::PrefixExpression(const Token* prefix_token, Expression* right) : prefix_token_(prefix_token),
operator_(prefix_token->getLiteral()),
right_expression_(right) {

}

PrefixExpression* PrefixExpression::createPrefixExpressionOf(const Token* prefix_token, Expression* right) {
	return new PrefixExpression(prefix_token, right);
}

std::string PrefixExpression::getOperator() const {
	return operator_;
}

Expression* PrefixExpression::getRightExpression() const {
	return right_expression_;
}