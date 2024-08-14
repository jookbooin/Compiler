#include "parser.h"

Parser::~Parser() {
    logPrint("Parser 소멸자");
}

Parser::Parser(const std::string &input) : lexer_(input), curtoken_(nullptr), peektoken_(nullptr) {
    logPrint("Parser 생성자");
    initializeFuncMaps();
    advanceCurToken();
    advanceCurToken();
}

Parser::Parser(Lexer &&lx) : lexer_(std::move(lx)), curtoken_(nullptr), peektoken_(nullptr) {
    logPrint("Parser 이동 생성자");
    initializeFuncMaps();
    advanceCurToken();
    advanceCurToken();
}

// prefix
std::unique_ptr<Expression> Parser::parseIdentifier() { // TokenTypes::IDENT
    return Identifier::createUniqueFrom(std::move(curtoken_));
}

std::unique_ptr<Expression> Parser::parseIntegerLiteral() { // TokenTypes::INT
    try {
        return IntegerLiteral::createUniqueFrom(std::move(curtoken_));
    } catch (const ParsingException &e) { // string -> int 변환 불가 메서드
        addError(e.what());
        return nullptr;
    }
}

std::unique_ptr<Expression> Parser::parsePrefixExpression() {

    // 1. '-, !' operator 토큰 따로 저장
    // [ - ] 5
    std::unique_ptr<Token> prefix_token = std::move(curtoken_);

    // - → 5
    advanceCurToken();

    /*
     * 2. - [ 5 ]
     *    '5' right_expression 생성
     *    '-', '!'  RBP 전달
     */
    std::unique_ptr<Expression> right_expression =
        parseExpressionWithLeftOperatorRBP(Operator::Precedence::PREFIX);

    // [-5]
    return PrefixExpression::createUniqueOf(std::move(prefix_token), std::move(right_expression));
}

// infix
std::unique_ptr<Expression>
Parser::parseInfixExpression(std::unique_ptr<Expression> left_expression) {

    // [ + ] BP
    int left_operator_RBP = getLeftOperatorRBP();

    // 1. 1 [ + ] 2 * 3
    std::unique_ptr<Token> op_token = std::move(curtoken_);

    //  + → [ 2 ]
    advanceCurToken();

    // 2. 1 + [ 2 ] * 3
    std::unique_ptr<Expression> right_expression = parseExpressionWithLeftOperatorRBP(
        left_operator_RBP); // +(rbp), *(lbp) 비교후 expression 비교

    /*
     * left : 1
     * operator : +
     * right : ( 2 * 3 )
     *
     * (1 + ( 2 * 3 ))
     */
    return InfixExpression::createUniqueOf(
        std::move(op_token), std::move(left_expression), std::move(right_expression));
}

std::unique_ptr<Expression> Parser::parseBoolean() {
    bool flag = isCurTokenType(TokenTypes::TRUE);
    return Boolean::createUniqueOf(std::move(curtoken_),flag);
}

std::unique_ptr<Expression> Parser::parseIfExpression() {
    return nullptr;
}

std::unique_ptr<Expression> Parser::parseGroupedExpression() {
    return nullptr;
}

std::unique_ptr<Expression> Parser::parseFunctionLiteral() {
    return nullptr;
}

void Parser::registerPrefixFunc(TokenType tokenType, PrefixFuncPtr prefixFuncPtr) {
    prefix_func_map[tokenType] = prefixFuncPtr;
}

void Parser::registerInfixFunc(TokenType tokenType, InfixFuncPtr infixFuncPtr) {
    infix_func_map[tokenType] = infixFuncPtr;
}

void Parser::initializeFuncMaps() {
    // prefix
    registerPrefixFunc(TokenTypes::IDENT, &Parser::parseIdentifier);

    registerPrefixFunc(TokenTypes::INT, &Parser::parseIntegerLiteral);

    registerPrefixFunc(TokenTypes::BANG, &Parser::parsePrefixExpression);
    registerPrefixFunc(TokenTypes::MINUS, &Parser::parsePrefixExpression);

    registerPrefixFunc(TokenTypes::TRUE, &Parser::parseBoolean);
    registerPrefixFunc(TokenTypes::FALSE, &Parser::parseBoolean);

    registerPrefixFunc(TokenTypes::LPAREN, &Parser::parseGroupedExpression);

    registerPrefixFunc(TokenTypes::IF, &Parser::parseIfExpression);

    registerPrefixFunc(TokenTypes::FUNCTION, &Parser::parseFunctionLiteral);

    // infix
    registerInfixFunc(TokenTypes::PLUS, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::MINUS, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::SLASH, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::ASTERISK, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::EQ, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::NOT_EQ, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::LT, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::GT, &Parser::parseInfixExpression);
    registerInfixFunc(TokenTypes::LPAREN, &Parser::parseInfixExpression);
}

void Parser::addError(const std::string &error_info) {
    errors_.push_back(error_info);
}

const std::string &Parser::peekError(const TokenType &type) {
    std::ostringstream oss;
    oss << "expect TokenType : " << peektoken_->getType() << ", actual : " << type;

    return oss.str();
}

const std::vector<std::string> &Parser::getErrors() const {
    return errors_;
}

void Parser::advanceCurToken() {
    curtoken_ = std::move(peektoken_);
    peektoken_ = lexer_.nextToken();
}

bool Parser::isCurTokenType(const TokenType &type) {

    // curtoken nullptr
    if (!curtoken_) {
        return false;
    }

    return curtoken_->getType() == type;
}

bool Parser::isPeekTokenType(const TokenType &type) {

    // if (!peektoken_) {
    //     return false;
    // }
    return peektoken_->getType() == type;
}

bool Parser::advanceTokenIfPeekTokenTypeIs(const TokenType &type) {
    if (isPeekTokenType(type)) {
        advanceCurToken();
        return true;
    }

    return false;
}

int Parser::getCurTokenPrecedence() {
    auto it = Operator::priority_map.find(curtoken_->getType());
    if (it != Operator::priority_map.end()) {
        return it->second;
    }

    return Operator::LOWEST;
}

int Parser::getPeekTokenPrecedence() {
    auto it = Operator::priority_map.find(peektoken_->getType());
    if (it != Operator::priority_map.end()) {
        return it->second;
    }

    return Operator::LOWEST;
}

int Parser::getLeftOperatorRBP() {
    return getCurTokenPrecedence();
}

int Parser::getRightOperatorLBP() {
    return getPeekTokenPrecedence();
}

std::unique_ptr<LetStatement> Parser::parseLetStatement() {

    // if (!curtoken_) {
    //     throw ParsingException("curtoken이 nullptr");
    // }

    // 1. [ let ] five =
    std::unique_ptr<Token> let_token = std::move(curtoken_);

    // let → [ five ]
    if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::IDENT)) {
        throw ParsingException(peekError(TokenTypes::IDENT));
    }

    // 2. let [ five ] =
    std::unique_ptr<Identifier> variable_name = Identifier::createUniqueFrom(std::move(curtoken_));

    // five → [ = ]
    if (!advanceTokenIfPeekTokenTypeIs(TokenTypes::ASSIGN)) {
        throw ParsingException(peekError(TokenTypes::ASSIGN));
    }

    // 3. let five [ = ]
    advanceCurToken();

    // 4. let five = [ exp ] ;
    std::unique_ptr<Expression> expression =
        parseExpressionWithLeftOperatorRBP(Operator::Precedence::LOWEST);

    while (!isCurTokenType(TokenTypes::SEMICOLON) || isPeekTokenType(TokenTypes::SEMICOLON)) {
        advanceCurToken();
    }

    // 4. let five =  [ ; ]
    return LetStatement::createUniqueOf(
        std::move(let_token), std::move(variable_name), std::move(expression));
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement() {

    // 1. [ return ] exp
    std::unique_ptr<Token> return_token = std::move(curtoken_);

    // return → [ exp ]
    advanceCurToken();

    // 2. return [ exp ]
    std::unique_ptr<Expression> expression =
        parseExpressionWithLeftOperatorRBP(Operator::Precedence::LOWEST);

    while (!isCurTokenType(TokenTypes::SEMICOLON)) {
        advanceCurToken();
    }

    return ReturnStatement::createUniqueOf(std::move(return_token), std::move(expression));
}

std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement() {

    /**
     *  [ 1 ] + 2
     *  [ 1 ]
     */
    // std::unique_ptr<Token> prefix_token = std::move(curtoken_);
    std::unique_ptr<Expression> expression =
        parseExpressionWithLeftOperatorRBP(Operator::Precedence::LOWEST);

    // std::unique_ptr<ExpressionStatement> expression_statement =
    //     ExpressionStatement::createUniqueOf(std::move(prefix_token), std::move(expression));

    std::unique_ptr<ExpressionStatement> expression_statement =
        ExpressionStatement::createUniqueFrom(std::move(expression));

    if (isPeekTokenType(TokenTypes::SEMICOLON)) {
        advanceCurToken();
    }

    return expression_statement;
}

std::unique_ptr<Statement> Parser::parseStatementFromCurToken() {

    if (isCurTokenType(TokenTypes::LET)) {
        return parseLetStatement();
    } else if (isCurTokenType(TokenTypes::RETURN)) {
        return parseReturnStatement();
    } else {
        return parseExpressionStatement();
    }

    return nullptr;
}

/*
* program DI
  - root 1개만 있어야 하므로 참조로 전달?
*/
Program *Parser::parseProgram() {

    // 1. AST root 노드 생성
    Program *root = Program::create();

    // 2. EOF 까지 token 반복
    while (!isCurTokenType(TokenTypes::kEOF)) {

        // 3. let, return 명령문 파싱
        std::unique_ptr<Statement> stmt;

        try {
            stmt = parseStatementFromCurToken();

            // 4. Program의 Statement에 추가
            root->addStatement(std::move(stmt));
        } catch (ParsingException e) {

            // 에러 발생시 Parser::errors_ 에 에러 저장
            addError(e.what());
        }

        // 5. 다음 token 호출
        advanceCurToken();
    }

    return root;
}

/// <summary>
/// 재귀적으로 동작 /
/// 매개변수는 왼쪽 연산자의 right_binding_power을 의미 /
/// [ + (5) * ] : 5가 + , * 의 우선순위를 통해 어느것을 먼저 처리할지 결정/
/// </summary>
std::unique_ptr<Expression> Parser::parseExpressionWithLeftOperatorRBP(int left_operator_RBP) {

    // 1. prefix :1 + [ 2 ] * 3
    auto prefix_it = prefix_func_map.find(curtoken_->getType());
    if (prefix_it == prefix_func_map.end()) {
        addError("prefix_func_map에서 " + curtoken_->getType() + "을 찾을 수 없습니다."); //
        return nullptr; // 예외 발생?
    }

    PrefixFuncPtr prefix_func_ptr = prefix_it->second; // map에서 함수 포인터 가져옴

    // 2. [ 2 ]
    // 클래스 함수 포인터 → 함수 호출
    std::unique_ptr<Expression> left_expression = (this->*prefix_func_ptr)();

    // 3. infix : 1 + [ 2 ] * 3
    while (!isPeekTokenType(TokenTypes::SEMICOLON) && left_operator_RBP < getRightOperatorLBP()) {
        auto infix_it = infix_func_map.find(peektoken_->getType());
        if (infix_it == infix_func_map.end()) {
            addError("infix_func_map에서 " + peektoken_->getType() + "을 찾을 수 없습니다."); //
            return nullptr;
        }

        // 4. 1 + 2 [ * ] 3
        advanceCurToken();

        // parseInfixExpression
        InfixFuncPtr infix_func_ptr = infix_it->second;

        // 5. (1 + ( 2 * 3 ))
        left_expression = std::move((this->*infix_func_ptr)(std::move(left_expression)));
    }

    return left_expression;
}

Parser *Parser::createFrom(const std::string &input) {
    Parser *p = new Parser(input);
    return p;
}
