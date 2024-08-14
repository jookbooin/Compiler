#pragma once
// expression

#include "node.h"
#include <variant>
class Expression : public Node {
  public:
    virtual void expressionNode() const = 0;
};