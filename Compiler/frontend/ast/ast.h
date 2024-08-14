#pragma once
// ast

#include "../../globalUtils.h"
#include "../token/token.h"
#include "expression.h"
#include "identifier/identifier.h"
#include "node.h"
#include "statement.h"
#include <string>
#include <vector>

class Program : public Node { // 1개 생성
  private:
    std::vector<std::unique_ptr<Statement>> statements_;

  public:
    std::string getTokenLiteral() const override;
    void addStatement(std::unique_ptr<Statement> stm);

    Program();
    ~Program();
    Program(const Program &copy) = delete;
    Program &operator=(const Program &src) = delete;

    const std::vector<std::unique_ptr<Statement>> &getStatements() const;
    static Program *create();
};

// 템플릿 ??
class LetStatement : public Statement {
  private:
    std::unique_ptr<Token> let_token_;
    std::unique_ptr<Identifier> variable_name_;
    std::unique_ptr<Expression> value_;

  public:
    LetStatement(std::unique_ptr<Token> let,
                 std::unique_ptr<Identifier> name,
                 std::unique_ptr<Expression> value);
    ~LetStatement();
    LetStatement(const LetStatement &copy) = delete;
    LetStatement &operator=(const LetStatement &src) = delete;
    LetStatement(LetStatement &&src) noexcept;
    LetStatement &operator=(LetStatement &&src) noexcept;

    std::string getTokenLiteral() const override;
    void statementNode() const override;

    const Identifier *getVariableName() const;
    const Expression *getValue() const;

    static std::unique_ptr<LetStatement> createUniqueOf(std::unique_ptr<Token> let_token,
                                                        std::unique_ptr<Identifier> name,
                                                        std::unique_ptr<Expression> value);
};

class ReturnStatement : public Statement {
  private:
    std::unique_ptr<Token> return_token_;
    std::unique_ptr<Expression> value_;

  public:
    ReturnStatement(std::unique_ptr<Token> token, std::unique_ptr<Expression> value);
    ~ReturnStatement();
    ReturnStatement(const ReturnStatement &copy) = delete;
    ReturnStatement &operator=(const ReturnStatement &src) = delete;
    ReturnStatement(ReturnStatement &&src) noexcept;
    ReturnStatement &operator=(ReturnStatement &&src) noexcept = delete;

    std::string getTokenLiteral() const override;
    void statementNode() const override;

    const Expression *getValue() const;

    static std::unique_ptr<ReturnStatement> createUniqueOf(std::unique_ptr<Token> return_token,
                                                           std::unique_ptr<Expression> value);
};

class ExpressionStatement : public Statement {
  private:
    // std::unique_ptr<Token> expression_token_;
    std::unique_ptr<Expression> expression_;

  public:
    // ExpressionStatement(std::unique_ptr<Token> expression_token,
    //                     std::unique_ptr<Expression> expression);
    ExpressionStatement(std::unique_ptr<Expression> expression);
    ~ExpressionStatement();
    ExpressionStatement(const ExpressionStatement &copy) = delete;
    ExpressionStatement &operator=(const ExpressionStatement &src) = delete;
    ExpressionStatement(ExpressionStatement &&src) noexcept;
    ExpressionStatement &operator=(ExpressionStatement &&src) noexcept = delete;

    std::string getTokenLiteral() const override;
    void statementNode() const override;

    Expression *getExpression() const;

    // static std::unique_ptr<ExpressionStatement>
    // createUniqueOf(std::unique_ptr<Token> return_token, std::unique_ptr<Expression> expression);
    static std::unique_ptr<ExpressionStatement>
    createUniqueFrom(std::unique_ptr<Expression> expression);
};