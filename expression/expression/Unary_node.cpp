#include "Unary_node.h"

Unary_node::Unary_node(const string &a, Expr b) : op(a), opnd(b)
{}
void Unary_node::print(ostream &o) const
{
	o << "(" << op << opnd << ")";
}
int Unary_node::eval() const
{
	if (op == "-")
		return -opnd.eval();

	cerr << "error -" << endl;
	return -1;
}