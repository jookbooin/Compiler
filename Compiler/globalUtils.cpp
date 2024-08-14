#include "globalUtils.h"

void logPrint(const std::string &log) {
    std::cout << log << std::endl;
}

bool is_digit(std::string str) {
    return atoi(str.c_str()) != 0 || str.compare("0") == 0;
}