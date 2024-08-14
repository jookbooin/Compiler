
#include "frontend/lexer/lexer.h"
#include "frontend/parser/parser.h"
#include "frontend/repl/repl.h"
#include "globalUtils.h"
#include <iostream>

int main() {

    // start();
    std::string input = "let five = 5;";

    Lexer lx(input);
    std::cout << lx.getInput() << std::endl;
    Parser parser(std::move(lx));

    // std::cout <<lx.getInput() << std::endl; // 이동되었기 떄문에 나오지 않음

    return 0;
}
