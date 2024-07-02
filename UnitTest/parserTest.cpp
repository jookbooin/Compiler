#include "pch.h"
#include "CppUnitTest.h"

#include "../Compiler/globalUtils.h"
#include "../Compiler/globalUtils.cpp"
#include "../Compiler/frontend/token/token.h"
#include "../Compiler/frontend/token/token.cpp"
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

		std::string input = R"(
	let x = 5;
	let y = 10;
	let foobar = 838383;)";

		struct Test {
			std::string expectedIdentifier;
		};

		std::vector<Test> tests = { {"x"}, {"y"}, {"foobar"} };
public:

	TEST_METHOD(testLet) {
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

	};

};