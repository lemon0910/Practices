#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "Expr_node.h"
#include <string>
#include "Expr.h"

class Binary_node : public Expr_node
{
	friend class Expr;
public:
	Binary_node(const string &a, Expr b, Expr c);
	void print(ostream& o) const;
	int eval() const;
private:
	string op;
	Expr left;
	Expr right;
};

#endif