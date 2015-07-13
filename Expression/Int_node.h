#ifndef INT_NODE_H
#define INT_NODE_H

#include "Expr_node.h"
using namespace std;

class Int_node : public Expr_node
{
	friend class Expr;
public:
	Int_node(int k);
	void print(ostream& o) const;
	int eval() const;

private:
	int n;
};

#endif