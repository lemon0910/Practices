#ifndef EXPR_H
#define EXPR_H
#include "Expr_node.h"
using namespace std;

class Expr
{
	friend ostream& operator<<(ostream&, const Expr&);
public:
	Expr(int n);
	Expr(const string &op, Expr t);
	Expr(const string &op, Expr left, Expr right);
	Expr(const Expr& t);
	Expr& operator==(const Expr& rhs);
	int eval() const;
	~Expr();

private:
	Expr_node *p;
};

ostream& operator<<(ostream& o, const Expr& t);

#endif