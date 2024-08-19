#include "ast.h"

// Program
Program::Program() {
}

Program::~Program() {
}

std::string Program::getTokenLiteral() const {
    if (!statements_.empty() && statements_.front() != nullptr) {
        return statements_.front()->getTokenLiteral();
    }

    return "Program empty!";
}

void Program::addStatement(std::unique_ptr<Statement> stmt) {
    statements_.push_back(std::move(stmt));
}

Program *Program::create() {
    return new Program();
}

const std::vector<std::unique_ptr<Statement>> &Program::getStatements() const {
    return statements_;
}

// LetStatement
LetStatement::LetStatement(std::unique_ptr<Token> let_token,
                           std::unique_ptr<Identifier> name,
                           std::unique_ptr<Expression> value)
    : let_token_(std::move(let_token)), variable_name_(std::move(name)), value_(std::move(value)) {
    logPrint("LetStatement 생성자");
}

LetStatement::~LetStatement() {
    logPrint("LetStatement 소멸자");
}

LetStatement::LetStatement(LetStatement &&src) noexcept
    : let_token_(std::move(src.let_token_)), variable_name_(std::move(src.variable_name_)),
      value_(std::move(src.value_)) {
    logPrint("LetStatement 이동 생성자");
}

LetStatement &LetStatement::operator=(LetStatement &&src) noexcept {
    if (this != &src) {
        let_token_ = std::move(src.let_token_);
        variable_name_ = std::move(src.variable_name_);
        value_ = std::move(src.value_);
        logPrint("LetStatement 이동 대입 연산자");
    }
    return *this;
}

std::string LetStatement::getTokenLiteral() const {
    return let_token_->getLiteral();
}

void LetStatement::statementNode() const {
}

const Identifier *LetStatement::getVariableName() const {
    return variable_name_.get();
}

const Expression *LetStatement::getValue() const {
    return value_.get();
}

std::unique_ptr<LetStatement> LetStatement::createUniqueOf(std::unique_ptr<Token> let_token,
                                                           std::unique_ptr<Identifier> name,
                                                           std::unique_ptr<Expression> value) {
    return std::make_unique<LetStatement>(std::move(let_token), std::move(name), std::move(value));
}

// ReturnStatement
ReturnStatement::ReturnStatement(std::unique_ptr<Token> return_token,
                                 std::unique_ptr<Expression> value)
    : return_token_(std::move(return_token)), value_(std::move(value)) {
    logPrint("ReturnStatement 생성자");
}

ReturnStatement::~ReturnStatement() {
    logPrint("ReturnStatement 소멸자");
}

ReturnStatement::ReturnStatement(ReturnStatement &&src) noexcept
    : return_token_(std::move(src.return_token_)), value_(std::move(src.value_)) {
    logPrint("ReturnStatement 이동생성자");
}

std::string ReturnStatement::getTokenLiteral() const {
    return return_token_->getLiteral();
}

void ReturnStatement::statementNode() const {
}

const Expression *ReturnStatement::getValue() const {
    return value_.get();
}

std::unique_ptr<ReturnStatement>
ReturnStatement::createUniqueOf(std::unique_ptr<Token> return_token,
                                std::unique_ptr<Expression> value) {
    return std::make_unique<ReturnStatement>(std::move(return_token), std::move(value));
}

// ExpressionStatement
// ExpressionStatement::ExpressionStatement(std::unique_ptr<Token> expression_token,
//                                         std::unique_ptr<Expression> expression)
//    : expression_token_(std::move(expression_token)), expression_(std::move(expression)) {
//    logPrint("ExpressionStatement 생성자");
//}

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expression)
    : expression_(std::move(expression)) {
    logPrint("ExpressionStatement 생성자");
}

ExpressionStatement::~ExpressionStatement() {
    logPrint("ExpressionStatement 소멸자");
}

// ExpressionStatement::ExpressionStatement(ExpressionStatement &&src) noexcept
//     : expression_token_(std::move(src.expression_token_)),
//     expression_(std::move(src.expression_)) { logPrint("ExpressionStatement 이동 생성자");
// }

ExpressionStatement::ExpressionStatement(ExpressionStatement &&src) noexcept
    : expression_(std::move(src.expression_)) {
    logPrint("ExpressionStatement 이동 생성자");
}

std::string ExpressionStatement::getTokenLiteral() const {
    return expression_->getTokenLiteral();
}

void ExpressionStatement::statementNode() const {
}

const Expression *ExpressionStatement::getExpression() const {
    return expression_.get();
}

// std::unique_ptr<ExpressionStatement>
// ExpressionStatement::createUniqueOf(std::unique_ptr<Token> expression_token,
//                                     std::unique_ptr<Expression> expression) {
//     return std::make_unique<ExpressionStatement>(std::move(expression_token),
//                                                  std::move(expression));
// }

std::unique_ptr<ExpressionStatement>
ExpressionStatement::createUniqueFrom(std::unique_ptr<Expression> expression) {
    return std::make_unique<ExpressionStatement>(std::move(expression));
}

BlockStatement::BlockStatement(std::unique_ptr<Token> token)
    : block_init_token_(std::move(token)), block_end_token_(nullptr) {
    logPrint("BlockStatement 생성자");
}

BlockStatement::~BlockStatement() {
    logPrint("BlockStatement 소멸자");
}

BlockStatement::BlockStatement(BlockStatement &&src) noexcept
    : block_init_token_(std::move(src.block_init_token_)),
      statements_(std::move(src.statements_)),
      block_end_token_(std::move(src.block_end_token_)) {
    logPrint("BlockStatement 이동 생성자");
}

BlockStatement &BlockStatement::operator=(BlockStatement &&src) noexcept {
    if (this != &src) {
        block_init_token_ = std::move(src.block_init_token_);
        statements_ = std::move(src.statements_);
        block_end_token_ = std::move(src.block_end_token_);
        logPrint("BlockStatement 이동 대입 연산자");
    }
    return *this;
}

std::string BlockStatement::getTokenLiteral() const {
    std::string end_token_literal = block_end_token_ ? block_end_token_->getLiteral() : "";
    return block_init_token_->getLiteral() + " " + end_token_literal; // { }
}


void BlockStatement::statementNode() const {
}

void BlockStatement::addStatement(std::unique_ptr<Statement> stmt) {
    statements_.push_back(std::move(stmt));
}

void BlockStatement::setBlockEndToken(std::unique_ptr<Token> rbrace_token) {
    block_end_token_ = std::move(rbrace_token);
}

const std::vector<std::unique_ptr<Statement>>& BlockStatement::getStatements() const {
    return statements_;
}

std::unique_ptr<BlockStatement> BlockStatement::createFrom(std::unique_ptr<Token> block_init_token) {
    return std::make_unique<BlockStatement>(std::move(block_init_token));
}