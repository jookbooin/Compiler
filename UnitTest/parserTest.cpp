#include "pch.h"
#include "CppUnitTest.h"

#include "../Compiler/exception/exception.h"
#include "../Compiler/exception/exception.cpp"
#include "../Compiler/globalUtils.h"
#include "../Compiler/globalUtils.cpp"
#include "../Compiler/frontend/token/token.h"
#include "../Compiler/frontend/token/token.cpp"
#include "../Compiler/frontend/token/token_type.h"
#include "../Compiler/frontend/token/token_type.cpp"
#include "../Compiler/frontend/lexer/lexer.h"
#include "../Compiler/frontend/lexer/lexer.cpp"

#include "../Compiler/frontend/ast/ast.h"
#include "../Compiler/frontend/ast/ast.cpp"
#include "../Compiler/frontend/ast/identifier.h"
#include "../Compiler/frontend/ast/identifier.cpp"
#include "../Compiler/frontend/parser/parser.h"
#include "../Compiler/frontend/parser/parser.cpp"
#include "../Compiler/frontend/ast/integerLiteral/integer_literal.h"
#include "../Compiler/frontend/ast/integerLiteral/integer_literal.cpp"
#include "../Compiler/frontend/ast/prefixExpression/prefixExpression.h"
#include "../Compiler/frontend/ast/prefixExpression/prefixExpression.cpp"

#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace parserTest
{

	TEST_CLASS(parserTest) {


public:

	bool testLetStatement(Statement* s, const std::string& name) {
		if (s->getTokenLiteral() != "let") {
			return false;
		}

		LetStatement* letStatement = dynamic_cast<LetStatement*>(s);
		if (!letStatement) {
			return false;
		}

		if (letStatement->getVariableName()->getValue() != name) {
			return false;
		}

		if (letStatement->getVariableName()->getTokenLiteral() != name) {
			return false;
		}

		return true;

	}

	TEST_METHOD(test_Let) {

		std::string input = R"(
	let x = 5;
	let y = 10;
	let foobar = 838383;)";

		struct Test {
			std::string expectedIdentifier;
		};

		std::vector<Test> tests = { {"x"}, {"y"}, {"foobar"} };
		Lexer* lx = Lexer::createLexerFromInput(input);
		Parser* p = Parser::createParserFromLexer(*lx);

		Program* pg = p->parseProgram();
		Assert::AreEqual(static_cast<size_t>(3), pg->getStatements().size());

		for (int i = 0; i < tests.size(); i++) {
			Statement* stmt = pg->getStatements()[i];
			if (!testLetStatement(stmt, tests[i].expectedIdentifier)) {
				Assert::Fail(L"testLetStatement failed");
			}
		}
	}

	TEST_METHOD(test_Return) {
		std::string input = R"(
	return 5;
	return 10;
	return 838383;)";

		Lexer* lx = Lexer::createLexerFromInput(input);
		Parser* p = Parser::createParserFromLexer(*lx);

		Program* pg = p->parseProgram();
		Assert::AreEqual(static_cast<size_t>(3), pg->getStatements().size());

		for (auto vs : pg->getStatements()) {
			if (!(vs->getTokenLiteral() == "return")) {
				Assert::Fail(L"testLetStatement failed");
			}
		}
	}

	TEST_METHOD(test_Expression) {
		std::string input = R"(foobar;)";

		Lexer* lx = Lexer::createLexerFromInput(input);
		Parser* p = Parser::createParserFromLexer(*lx);

		Program* pg = p->parseProgram();
		Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

		Statement* stmt = pg->getStatements().front();
		ExpressionStatement* exprStmt = dynamic_cast<ExpressionStatement*>(stmt);
		if (exprStmt == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Expression* expr = exprStmt->getExpression();
		Identifier* ident = dynamic_cast<Identifier*>(expr);
		if (ident == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Assert::AreEqual(std::string("foobar"), ident->getTokenLiteral());
	}

	TEST_METHOD(test_IntegerLiteral) {
		std::string input = R"(5;)";

		Lexer* lx = Lexer::createLexerFromInput(input);
		Parser* p = Parser::createParserFromLexer(*lx);

		Program* pg = p->parseProgram();

		Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

		Statement* stmt = pg->getStatements().front();
		ExpressionStatement* exprStmt = dynamic_cast<ExpressionStatement*>(stmt);
		if (exprStmt == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Expression* expr = exprStmt->getExpression();
		IntegerLiteral* intl = dynamic_cast<IntegerLiteral*>(expr);
		if (intl == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Assert::AreEqual(static_cast<size_t>(5), static_cast<size_t>(intl->getValue()));

		Assert::AreEqual(std::string("5"), intl->getTokenLiteral());
	}

	TEST_METHOD(test_PrefixExpression) {

		struct PrefixTest {
			std::string input;
			std::string op;
			int value;
		};

		const std::vector<PrefixTest> v = {
			{"!5;","!",5},
			{"-15;","-",15}
		};

		for (PrefixTest pft : v) {

			Lexer* lx = Lexer::createLexerFromInput(pft.input);
			Parser* p = Parser::createParserFromLexer(*lx);

			Program* pg = p->parseProgram();

			Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

			Statement* stmt = pg->getStatements().front();
			ExpressionStatement* exprStmt = dynamic_cast<ExpressionStatement*>(stmt);
			if (exprStmt == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			Expression* expr = exprStmt->getExpression();
			PrefixExpression* pfe = dynamic_cast<PrefixExpression*>(expr);
			if (pfe == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			if (pfe->getOperator() != pft.op) {
				Assert::Fail(L"해당 연산자가 아닙니다.");
			}

			// Expression 타입 확인 == IntegerLiteral
			IntegerLiteral* intl = dynamic_cast<IntegerLiteral*>(pfe->getRightExpression());
			if (intl == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			if (intl->getValue() != pft.value) {
				Assert::Fail(L"해당 값 이 아닙니다.");
			}

			if (intl->getTokenLiteral() != std::to_string(pft.value)) {
				Assert::Fail(L"해당 값 이 아닙니다.");
			}

			delete lx;
			delete p;
			delete pg;
		}
	}

	};

};