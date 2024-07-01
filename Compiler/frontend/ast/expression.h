#pragma once
// expression

#include "node.h"
class Expression : public Node {
public:
	virtual void expressionNode() const = 0;
};