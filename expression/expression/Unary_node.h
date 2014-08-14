#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "Expr_node.h"
#include <string>
#include "Expr.h"
using namespace std;

class Unary_node : public Expr_node
{
	friend class Expr;
public:
	Unary_node(const string &a, Expr b);
	void print(ostream &o) const;
	int eval() const;
private:
	string op;
	Expr opnd;
};

#endif