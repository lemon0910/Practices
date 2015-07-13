#include "Expr.h"
#include "Unary_node.h"
#include "Int_node.h"
#include "Binary_node.h"

Expr::Expr(int n)
{
	p = new Int_node(n);
}
Expr::Expr(const string &op, Expr t)
{
	p = new Unary_node(op, t);
}
Expr::Expr(const string &op, Expr left, Expr right)
{
	p = new Binary_node(op, left, right);
}
Expr::Expr(const Expr& t)
{
	p = t.p;
	++p->use;
}
Expr& Expr::operator==(const Expr& rhs)
{
	rhs.p->use++;
	if (--p->use == 0)
		delete p;
	p = rhs.p;
	return *this;
}
int Expr::eval() const
{
	return p->eval();
}
Expr::~Expr()
{
	if (--p->use == 0)
		delete p;
}

ostream& operator<<(ostream& o, const Expr& t)
{
	t.p->print(o);
	return o;
}