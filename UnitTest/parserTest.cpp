#include "pch.h"
#include "CppUnitTest.h"

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


#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace parserTest
{

	TEST_CLASS(parserTest) {


public:

	TEST_METHOD(testLet) {

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

	TEST_METHOD(testReturn) {
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

	TEST_METHOD(testExpression) {
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

	};

};