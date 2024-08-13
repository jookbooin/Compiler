#pragma once

#include "../../token/token.h"
#include "../expression.h"

class InfixExpression : public Expression {
  private:
    std::unique_ptr<Token> infix_token_;
    std::unique_ptr<Expression> left_expression_;
    std::string operator_;
    std::unique_ptr<Expression> right_expression_;

  public:
    InfixExpression(std::unique_ptr<Token> infix_token,
                    std::unique_ptr<Expression> left,
                    std::unique_ptr<Expression> right);
    ~InfixExpression();

    std::string getTokenLiteral() const;
    void expressionNode() const override;

    std::string getOperator() const;
    // Expression* getLeftExpression();
    // Expression* getRightExpression();

    static std::unique_ptr<InfixExpression> createUniqueOf(std::unique_ptr<Token> infix_token,
                                                           std::unique_ptr<Expression> left,
                                                           std::unique_ptr<Expression> right);
};