#include "Binary_node.h"

Binary_node::Binary_node(const string &a, Expr b, Expr c) : op(a), left(b), right(c)
{
}

void Binary_node::print(ostream& o) const
{
	o << "(" << left << op << right << ")";
}

int Binary_node::eval() const
{
	int op1 = left.eval();
	int op2 = right.eval();

	if (op == "-")
		return op1 - op2;
	if (op == "+")
		return op1 + op2;
	if (op == "*")
		return op1 * op2;
	if (op == "/" && op2 != 0)
		return op1 / op2;

	cerr << "error, div is 0" << endl;
	return -1;
}