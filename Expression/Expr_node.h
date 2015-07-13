#ifndef EXPR_NODE_H
#define EXPR_NODE_H

#include <iostream>
#include <ostream>
using namespace std;

class Expr;
class Expr_node
{
	friend ostream& operator<<(ostream&, const Expr&);
	friend class Expr;

protected:
	Expr_node();
	virtual void print(ostream&) const = 0;
	virtual int eval() const = 0;
	virtual ~Expr_node();

private:
	int use;
};

#endif