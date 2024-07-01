#pragma once
// node

#include <string>
class Node {
public:
	virtual std::string tokenLiteral() const = 0;
	virtual ~Node() = default; // 가상 소멸자 
};