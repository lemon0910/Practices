#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <string>

class Foo
{
public:
    void methodA()
    {
        std::cout << "hello Foo" << std::endl;
    }

    void methodInt(int a)
    {
        std::cout << a << std::endl;
    }

    void methodString(const std::string& str)
    {
        std::cout << str << std::endl;
    }
};

class Bar
{
public:
    void methodB()
    {
        std::cout << "hello bar" << std::endl;
    }
};

int main()
{
    boost::function<void()> f1;

    Foo foo;
    f1 = boost::bind(&Foo::methodA, &foo);
    f1();

    Bar bar;
    f1 = boost::bind(&Bar::methodB, &bar);
    f1();

    f1 = boost::bind(&Foo::methodInt, &foo, 42);
    f1();

    f1 = boost::bind(&Foo::methodString, &foo, "hello");
    f1();

    boost::function<void(int)> f2;
    f2 = boost::bind(&Foo::methodInt, &foo, _1);
    f2(53);

    return 0;
}
