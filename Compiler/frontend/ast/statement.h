#pragma once
// statement

#include "node.h"
class Statement : public Node {
  public:
    virtual void statementNode() const = 0;
};