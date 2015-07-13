#include "mystring.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

void foo(mystring x)
{}

void bar(const mystring& x)
{}

mystring baz()
{
	mystring ret("world");
	return ret;
}

int main()
{
	mystring s0;
	mystring s1("hello");
	mystring s2(s0);
	mystring s3 = s1;
	s2 = s1;

	foo(s1);
	bar(s1);
	foo("temporary");
	bar("temporary");
	mystring s4 = baz();

	vector<mystring> svec;
	svec.push_back(s0);
	svec.push_back(s1);
	svec.push_back(baz());
	svec.push_back("goo job");

	mystring s5;
	mystring s6("hello");

	if (s5 == s6)
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;

	cout << s6[2] << endl;

	return 0;
}