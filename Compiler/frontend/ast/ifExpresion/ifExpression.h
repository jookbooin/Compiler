#pragma once

#include "../../token/token.h"
#include "../ast.h"
#include "../expression.h"

class IfExpression : public Expression {
  private:
    std::unique_ptr<Token> if_token_;
    std::unique_ptr<Expression> condition_;
    std::unique_ptr<BlockStatement> consequence_;
    std::unique_ptr<BlockStatement> alternative_;

  public:
    IfExpression(std::unique_ptr<Token> if_token,
                 std::unique_ptr<Expression> condition,
                 std::unique_ptr<BlockStatement> consequence);
    ~IfExpression();
    IfExpression(const IfExpression &copy) = delete;
    IfExpression &operator=(const IfExpression &src) = delete;
    IfExpression(IfExpression &&src) noexcept;
    IfExpression &operator=(IfExpression &&src) noexcept;

    std::string getTokenLiteral() const;
    void expressionNode() const override;

    const Expression *getCondition() const;
    const Statement *getConsequence() const;
    const Statement *getAlternative() const;
    void setAlternative(std::unique_ptr<BlockStatement> alternative);

    static std::unique_ptr<IfExpression> createOf(std::unique_ptr<Token> if_token,
                                                  std::unique_ptr<Expression> condition,
                                                  std::unique_ptr<BlockStatement> consequence);
};