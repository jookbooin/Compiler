#pragma once
// identifier

#include "../../globalUtils.h"
#include "../../token/token.h"
#include "../expression.h"
#include <string>

class Identifier : public Expression {
  private:
    std::unique_ptr<Token> token_;
    std::string value_;

  public:
    Identifier(std::unique_ptr<Token> token);
    ~Identifier();
    Identifier(const Identifier &copy) = delete;
    Identifier &operator=(const Identifier &src) = delete;
    Identifier(Identifier &&src) noexcept;
    Identifier &operator=(Identifier &&src) noexcept;

    std::string getTokenLiteral() const override;
    void expressionNode() const override;
    std::string getValue() const;

    static std::unique_ptr<Identifier> createUniqueFrom(std::unique_ptr<Token> curtoken);
};