#include "pch.h"
#include "CppUnitTest.h"
#include "../Compiler/frontend/token/token.h"
#include "../Compiler/frontend/token/token.cpp"

#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tokenTest
{

	TEST_CLASS(tokenTest) {

public:

	TEST_METHOD(tokenMethod) {
		Token* tok = new Token(TokenTypes::INT, "1");
		Assert::AreEqual(TokenTypes::INT, tok->getType());
		delete tok;  
	}

	};
}
