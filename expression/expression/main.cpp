#include <iostream>
#include "Expr.h"
using namespace std;

int main()
{
	Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
	cout << t << " = " << t.eval() << endl;
	
	return 0;
}