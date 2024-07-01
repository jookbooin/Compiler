#pragma once
// ast

#include <string>
#include <vector>

#include "../token/token.h"
#include "node.h"
#include "statement.h"
#include "expression.h"
#include "identifier.h"

class Program : public Node { // 1개 생성
private:
	std::vector<Statement*> statements_;
	
public:
	
	std::string tokenLiteral() const override;
	void addStatement(Statement* const stm);

	Program();
	static Program* createProgram();
	//Program(const Program& copy);
	~Program();
};