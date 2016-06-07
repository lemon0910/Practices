#include <muduo/net/EventLoop.h>
#include <boost/bind.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/TcpServer.h>

class EchoServer
{
public:
    explicit EchoServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress& address)
 :loop_(loop), server_(loop, address, "EchoServer")
    {
        server_.setConnectionCallback(boost::bind(&EchoServer::onConnection, this, _1));
        server_.setMessageCallback(boost::bind(&EchoServer::onMessage, this, _1, _2, _3));
    }

    void start()
    {
        server_.start();
    }

private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn)
    {
        LOG_INFO << conn->peerAddress().toIpPort() << " is connected";
    }

    void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time)
    {
        muduo::string msg(buf->retrieveAllAsString());
        conn->send(msg);
    }

private:
    muduo::net::TcpServer server_;
    muduo::net::EventLoop *loop_;
};

int main()
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress address(2007);
    EchoServer server(&loop, address);
    server.start();
    loop.loop();
}
