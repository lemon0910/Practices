//改变bar()的位置对程序造成的影响
#include <cstdio>

void foo(int)
{
    printf("int\n");
}

void bar()
{
    foo('a');
}

void foo(char)
{
    printf("char\n");
}

int main()
{
    bar();

    return 0;
}
