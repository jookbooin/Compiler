#include "prefixExpression.h"

std::string PrefixExpression::getTokenLiteral() const {
	return prefix_token_->getLiteral();
}

void PrefixExpression::expressionNode() const {

}

PrefixExpression::PrefixExpression(const Token* prefix_token, Expression* expression) : prefix_token_(prefix_token),
	operator_(prefix_token->getLiteral()),
	right_(expression){

}

PrefixExpression* PrefixExpression::createPrefixExpressionOf(const Token* prefix_token, Expression* expression) {
	return new PrefixExpression(prefix_token, expression);
}

std::string PrefixExpression::getOperator() const {
	return operator_;
}

Expression* PrefixExpression::getRightExpression() const {
	return right_;
}