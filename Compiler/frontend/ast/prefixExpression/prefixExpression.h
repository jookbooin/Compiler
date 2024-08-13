#pragma once

#include "../../token/token.h"
#include "../expression.h"

class PrefixExpression : public Expression {
  private:
    std::unique_ptr<Token> prefix_token_;
    std::string operator_; // "!", "-"
    std::unique_ptr<Expression> right_expression_;

  public:
    PrefixExpression(std::unique_ptr<Token> prefix_token, std::unique_ptr<Expression> right);
    ~PrefixExpression();
    PrefixExpression(const PrefixExpression &copy) = delete;

    std::string getTokenLiteral() const;
    void expressionNode() const override;

    std::string getOperator() const;
    Expression *getRightExpression() const;

    static std::unique_ptr<PrefixExpression> createUniqueOf(std::unique_ptr<Token> prefix_token,
                                                            std::unique_ptr<Expression> right);
};