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
#include "../Compiler/frontend/ast/identifier/identifier.h"
#include "../Compiler/frontend/ast/identifier/identifier.cpp"
#include "../Compiler/frontend/parser/parser.h"
#include "../Compiler/frontend/parser/parser.cpp"
#include "../Compiler/frontend/parser/parse_info.h"
#include "../Compiler/frontend/parser/parse_info.cpp"
#include "../Compiler/frontend/ast/integerLiteral/integer_literal.h"
#include "../Compiler/frontend/ast/integerLiteral/integer_literal.cpp"
#include "../Compiler/frontend/ast/prefixExpression/prefixExpression.h"
#include "../Compiler/frontend/ast/prefixExpression/prefixExpression.cpp"
#include "../Compiler/frontend/ast/infixExpression/infixExpression.h"
#include "../Compiler/frontend/ast/infixExpression/infixExpression.cpp"

#include <vector>
#include <string>
#include <variant>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace parserTest
{

	TEST_CLASS(parserTest) {


public:

	// expected_value 값 검증용
	bool TestExpectedValue(const Expression* expression, const std::variant<int, std::string>& value) {
		switch (value.index()) {
			case 0: { // int
				const IntegerLiteral* temp = dynamic_cast<const IntegerLiteral*>(expression);
				if (temp && temp->getValue() == std::get<int>(value)) {
					return true;
				}
				break;
			}
			case 1: { // string
				const Identifier* temp = dynamic_cast<const Identifier*>(expression);
				if (temp && temp->getValue() == std::get<std::string>(value)) { 
					return true;
				}
				break;
			}
			default:
				break;
		}
		return false;
}

	bool testLetVaiableName(LetStatement* stmt, const std::string& name) {

		if (stmt->getVariableName()->getValue() != name) {
			return false;
		}

		return true;
	}

	TEST_METHOD(test_Let) {

		struct Test {
			std::string input;
			std::string expected_identifier;
			std::variant<int, std::string> expected_value;
		};

		std::vector<Test> tests = { {"let x = 5;", "x",5},
									{"let y = 10;", "y",10}, 
									{"let foobar = y;", "foobar", "y"}};
		

		for (int i = 0; i < tests.size(); i++) {
            Lexer lx(tests[i].input);
			Parser p(std::move(lx));

			Program* pg = p.parseProgram();

			Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());
			Statement* stmt = pg->getStatements()[0].get();

			if (stmt->getTokenLiteral() != "let" ) {
				Assert::Fail(L"letStatement failed");
            }

			LetStatement* temp = dynamic_cast<LetStatement*>(stmt);

			if (temp == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			if (!testLetVaiableName(temp, tests[i].expected_identifier)) {
				Assert::Fail(L"testLetStatement failed");
			}


			const Expression* expression = temp->getValue();

			if (!TestExpectedValue(expression, tests[i].expected_value)) {
                Assert::Fail(L"testLetStatement failed");
			}
			
		}
	}

	TEST_METHOD(test_Return) {

		struct Test {
			std::string input;
			std::variant<int, std::string> expected_value;
		};

		std::vector<Test> tests = { {"return 5;", 5},
									{"return foobar;", "foobar"}};
		
		for (int i = 0; i < tests.size(); i++) {
            Lexer lx(tests[i].input);
			Parser p(std::move(lx));

			Program* pg = p.parseProgram();
			Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

			Statement* stmt = pg->getStatements()[0].get();

			if (stmt->getTokenLiteral() != "return" ) {
				Assert::Fail(L"returnStatement failed");
            }

			ReturnStatement* temp = dynamic_cast<ReturnStatement*>(stmt);

			if (temp == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}
            
			const Expression* expression = temp->getValue();

			if (!TestExpectedValue(expression, tests[i].expected_value)) {
				Assert::Fail(L"returnStatement failed");
			}

		}

	}

	TEST_METHOD(test_Identifier) {
		std::string input = R"(foobar;)";

		Lexer lx(input);
		Parser p(std::move(lx));

		Program* pg = p.parseProgram();
		Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

		Statement* stmt = pg->getStatements()[0].get();
		ExpressionStatement* temp = dynamic_cast<ExpressionStatement*>(stmt);

		if (temp == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Expression* expr = temp->getExpression();
		Identifier* ident = dynamic_cast<Identifier*>(expr);

		if (ident == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Assert::AreEqual(std::string("foobar"), ident->getTokenLiteral());
	}

	TEST_METHOD(test_IntegerLiteral) {
		std::string input = R"(5;)";

		Lexer lx(input);
		Parser p(std::move(lx));

		Program* pg = p.parseProgram();
		Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

		Statement* stmt = pg->getStatements()[0].get();

		ExpressionStatement* temp = dynamic_cast<ExpressionStatement*>(stmt);

		if (temp == nullptr) {
			Assert::Fail(L"해당 타입이 아닙니다.");
		}

		Expression* expr = temp->getExpression();

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
			std::string expected_op;
			std::variant<int, std::string> expected_value;
		};

		std::vector<PrefixTest> tests = {
			{"!5;", "!", 5},
			{"-15;", "-", 15},
			{"!foobar;", "!", "foobar"},
			{"-foobar;", "-", "foobar"}
		};

		for (int i = 0; i < tests.size(); i++) {
            
			Lexer lx(tests[i].input);
			Parser p(std::move(lx));

			Program* pg = p.parseProgram();
			Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

			Statement* stmt = pg->getStatements()[0].get();
			ExpressionStatement* temp = dynamic_cast<ExpressionStatement*>(stmt);
			if (temp == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			Expression* expr = temp->getExpression();
			PrefixExpression* pexpr = dynamic_cast<PrefixExpression*>(expr);
			if (pexpr == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			if (pexpr->getOperator() != tests[i].expected_op) {
				Assert::Fail(L"해당 연산자가 아닙니다.");
			}

			const Expression* expression = pexpr->getRightExpression();

			if (!TestExpectedValue(expression, tests[i].expected_value)) {
				Assert::Fail(L".");
			}

		}
	}

	TEST_METHOD(test_InfixExpression) {

		struct InfixTest {
			std::string input;
			std::variant<int, std::string> expected_left_value;
			std::string expected_op;
			std::variant<int, std::string> expected_right_value;
		};

		const std::vector<InfixTest> tests = {
			{"5 + 5;", 5, "+", 5},
			{"5 - 5;", 5, "-", 5},
			{"5 * 5;", 5, "*", 5},
			{"5 / 5;", 5, "/", 5},
			{"5 > 5;", 5, ">", 5},
			{"5 < 5;", 5, "<", 5},
			{"5 == 5;", 5, "==", 5},
			{"5 != 5;", 5, "!=", 5},
			{"foobar + barfoo;", "foobar", "+", "barfoo"},
			{"foobar - barfoo;", "foobar", "-", "barfoo"},
			{"foobar * barfoo;", "foobar", "*", "barfoo"},
			{"foobar / barfoo;", "foobar", "/", "barfoo"},
			{"foobar > barfoo;", "foobar", ">", "barfoo"},
			{"foobar < barfoo;", "foobar", "<", "barfoo"},
			{"foobar == barfoo;", "foobar", "==", "barfoo"},
			{"foobar != barfoo;", "foobar", "!=", "barfoo"}
		};

		for (int i = 0; i < tests.size(); i++) {
            
			Lexer lx(tests[i].input);
			Parser p(std::move(lx));

 			Program* pg = p.parseProgram();
			Assert::AreEqual(static_cast<size_t>(1), pg->getStatements().size());

			Statement* stmt = pg->getStatements()[0].get();
			ExpressionStatement* temp = dynamic_cast<ExpressionStatement*>(stmt);

			if (temp == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			Expression* expr = temp->getExpression();
			InfixExpression* iexpr = dynamic_cast<InfixExpression*>(expr);
			if (iexpr == nullptr) {
				Assert::Fail(L"해당 타입이 아닙니다.");
			}

			if (iexpr->getOperator() != tests[i].expected_op) {
				Assert::Fail(L"해당 연산자가 아닙니다.");
			}

			const Expression* left_expr = iexpr->getLeftExpression();
			const Expression* right_expr = iexpr->getRightExpression();

			if (!TestExpectedValue(left_expr, tests[i].expected_left_value)) {
				Assert::Fail(L"테스트 실패.");
			}

			if (!TestExpectedValue(right_expr, tests[i].expected_right_value)) {
				Assert::Fail(L"테스트 실패.");
			}

		}

	}


	//TEST_METHOD(test_Parser) {
	//	struct ParserTest {
	//		std::string input;
	//		std::string expected;
	//	};

	//	const std::vector<ParserTest> v = {
	//		{"-a * b", "((-a) * b)"},
	//		{"!-a", "(!(-a))"},
	//		{"a + b + c", "((a + b) + c)"},
	//		{"a + b - c", "((a + b) - c)"},
	//		{"a * b * c", "((a * b) * c)"},
	//		{"a * b / c", "((a * b) / c)"},
	//		{"a + b / c", "(a + (b / c))"},
	//		{"a + b * c + d / e - f", "(((a + (b * c)) + (d / e)) - f)"},
	//		{"3 + 4; -5 * 5", "(3 + 4)((-5) * 5)"},
	//		{"5 > 4 == 3 < 4", "((5 > 4) == (3 < 4))"},
	//		{"5 < 4 != 3 > 4", "((5 < 4) != (3 > 4))"},
	//		{"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"}
	//	};

	//	for (ParserTest pt : v) {
	//		Lexer* lx = Lexer::createFrom(pt.input);
	//		Parser* p = Parser::createFrom(*lx);

	//		Program* pg = p->parseProgram();

	//		if (!checkParserErrors(p)) {
	//			Assert::Fail(L"테스트 실패.");
	//		}

	//		delete lx;
	//		delete p;
	//	}
	//}

	bool testIntegerLiteral(Expression* expression, int value) {
		IntegerLiteral* intl = dynamic_cast<IntegerLiteral*>(expression);
		if (intl == nullptr) {
			return false;
		}

		if (intl->getValue() != value) {
			return false;
		}

		if (intl->getTokenLiteral() != std::to_string(value)) {
			return false;
		}

		return true;
	}

	bool checkParserErrors(const Parser* p) {
		if (p->getErrors().size() == 0) {
			return true;
		}

		return false;
	}

	};

};