#include <iostream>
#include <string>
#include <event.h>
#include <map>

class A
{
public:
    A()
    {
        s = 0;
    }

    bool operator<(const A& b) const
    {
        return true;
    }
private:
    struct event ev;
    int s;
};

int main()
{
    std::map<A, int> m;
    A a;
    m[a] = 10;

    std::cout << m[a] << std::endl;

    return 0;
}

