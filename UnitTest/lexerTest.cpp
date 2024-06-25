#include "pch.h"
#include "CppUnitTest.h"
#include "../Compiler/frontend/token/token.h"
#include "../Compiler/frontend/token/token.cpp"
#include "../Compiler/frontend/lexer/lexer.h"
#include "../Compiler/frontend/lexer/lexer.cpp"

#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lexerTest
{

	TEST_CLASS(lexerTest) {

public:

	struct Test {
		TokenType expectedType;
		std::string expectedLiteral;
	};

	const std::vector<Test> tests = {
		{TokenTypes::LET, "let"},
		{TokenTypes::IDENT, "five"},
		{TokenTypes::ASSIGN, "="},
		{TokenTypes::INT, "5"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::LET, "let"},
		{TokenTypes::IDENT, "ten"},
		{TokenTypes::ASSIGN, "="},
		{TokenTypes::INT, "10"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::LET, "let"},
		{TokenTypes::IDENT, "add"},
		{TokenTypes::ASSIGN, "="},
		{TokenTypes::FUNCTION, "fn"},
		{TokenTypes::LPAREN, "("},
		{TokenTypes::IDENT, "x"},
		{TokenTypes::COMMA, ","},
		{TokenTypes::IDENT, "y"},
		{TokenTypes::RPAREN, ")"},
		{TokenTypes::LBRACE, "{"},
		{TokenTypes::IDENT, "x"},
		{TokenTypes::PLUS, "+"},
		{TokenTypes::IDENT, "y"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::RBRACE, "}"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::LET, "let"},
		{TokenTypes::IDENT, "result"},
		{TokenTypes::ASSIGN, "="},
		{TokenTypes::IDENT, "add"},
		{TokenTypes::LPAREN, "("},
		{TokenTypes::IDENT, "five"},
		{TokenTypes::COMMA, ","},
		{TokenTypes::IDENT, "ten"},
		{TokenTypes::RPAREN, ")"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::BANG, "!"},
		{TokenTypes::MINUS, "-"},
		{TokenTypes::SLASH, "/"},
		{TokenTypes::ASTERISK, "*"},
		{TokenTypes::INT, "5"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::INT, "5"},
		{TokenTypes::LT, "<"},
		{TokenTypes::INT, "10"},
		{TokenTypes::GT, ">"},
		{TokenTypes::INT, "5"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::IF, "if"},
		{TokenTypes::LPAREN, "("},
		{TokenTypes::INT, "5"},
		{TokenTypes::LT, "<"},
		{TokenTypes::INT, "10"},
		{TokenTypes::RPAREN, ")"},
		{TokenTypes::LBRACE, "{"},
		{TokenTypes::RETURN, "return"},
		{TokenTypes::TRUE, "true"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::RBRACE, "}"},
		{TokenTypes::ELSE, "else"},
		{TokenTypes::LBRACE, "{"},
		{TokenTypes::RETURN, "return"},
		{TokenTypes::FALSE, "false"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::RBRACE, "}"},
		{TokenTypes::INT, "10"},
		{TokenTypes::EQ, "=="},
		{TokenTypes::INT, "10"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::INT, "10"},
		{TokenTypes::NOT_EQ, "!="},
		{TokenTypes::INT, "9"},
		{TokenTypes::SEMICOLON, ";"},
		{TokenTypes::kEOF, ""}
	};


	std::string input = R"(let five = 5;
	let ten = 10;
	let add = fn(x, y) {
		x + y;
	};
	let result = add(five, ten);

	!-/*5;
	5 < 10 > 5;

	if (5 < 10) {
		return true;
	} else {
		return false;
	}
	
	10 == 10;
	10 != 9;
	)";

	TEST_METHOD(lexerMethod) {

		Lexer* lx = Lexer::createLexer(input);
		
		for (const auto& test : tests) {
			Token* tok = lx->nextToken();

			Assert::AreEqual(test.expectedType, tok->getType());
			Assert::AreEqual(test.expectedLiteral, tok->getLiteral());

			delete tok; // 동적으로 생성된 토큰을 해제
		}
		
		delete lx;

	}

	};
}
