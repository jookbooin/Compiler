#pragma once

#include "../../../exception/exception.h"
#include "../../../globalUtils.h"
#include "../../token/token.h"
#include "../expression.h"

class IntegerLiteral : public Expression {
  private:
    std::unique_ptr<Token> integer_token_; // { type_ = 'INT', literal_ = "5" }
    int value_;                            // 5

  public:
    IntegerLiteral(std::unique_ptr<Token> token);
    ~IntegerLiteral();
    IntegerLiteral(const IntegerLiteral &copy) = delete;
    IntegerLiteral &operator=(const IntegerLiteral &src) = delete;
    IntegerLiteral(IntegerLiteral &&src) noexcept;
    IntegerLiteral &operator=(IntegerLiteral &&src) noexcept = delete;

    std::string getTokenLiteral() const;
    void expressionNode() const override;
    int getValue() const;

    static std::unique_ptr<IntegerLiteral> createUniqueFrom(std::unique_ptr<Token> curtoken);
};