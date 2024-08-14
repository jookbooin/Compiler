#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
  public:
    Exception(std::string message);
    const char *what() const noexcept override;

  protected:
    void setMessage(std::string message);

  private:
    std::string message_;
};

class ParsingException : public Exception {
  public:
    ParsingException(const std::string &message);
};