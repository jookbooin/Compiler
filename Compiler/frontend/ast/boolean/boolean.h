#pragma once
// Boolean

#include "../../../globalUtils.h"
#include "../../token/token.h"
#include "../expression.h"

class Boolean : public Expression {
  private:
    std::unique_ptr<Token> bool_token_; // { type_ = 'TRUE', literal_ = "true" }
    bool value_;                        // true
  public:
    Boolean(std::unique_ptr<Token> token, bool flag);
    ~Boolean();
    Boolean(const Boolean &copy) = delete;
    Boolean &operator=(const Boolean &src) = delete;
    Boolean(Boolean &&src) noexcept;
    Boolean &operator=(Boolean &&src) noexcept;

    std::string getTokenLiteral() const;
    void expressionNode() const override;
    bool getValue() const;

    static std::unique_ptr<Boolean> createUniqueOf(std::unique_ptr<Token> token, bool value);
};