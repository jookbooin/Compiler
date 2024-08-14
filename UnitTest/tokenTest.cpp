#include "pch.h"
#include "CppUnitTest.h"
#include "../Compiler/frontend/token/token.h"
#include "../Compiler/frontend/token/token.cpp"
#include "../Compiler/globalUtils.cpp"
#include "../Compiler/globalUtils.h"
#include "../Compiler/exception/exception.cpp"
#include "../Compiler/exception/exception.h"


#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tokenTest {

TEST_CLASS(tokenTest){

    public :

        TEST_METHOD(tokenMethod){
            std::unique_ptr<Token> tok = std::make_unique<Token>(TokenTypes::INT, "1");
Assert::AreEqual(TokenTypes::INT, tok->getType());
} // namespace tokenTest
}
;
}
