#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>

#include <iostream>

void print()
{
    std::cout << "hello, World!\n";
}

void quit(muduo::net::EventLoop *loop)
{
    loop->quit();
}

int main()
{
    muduo::net::EventLoop loop;
    loop.runAfter(5, print);
    loop.runAfter(10, boost::bind(quit, &loop));
    loop.loop();
}
