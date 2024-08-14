#include "exception.h"

Exception::Exception(std::string message) : message_(message) {
}

void Exception::setMessage(std::string message) {
    message_ = std::move(message);
}

const char *Exception::what() const noexcept {
    return message_.c_str();
}

// ParsingException
ParsingException::ParsingException(const std::string &message) : Exception(message) {
}