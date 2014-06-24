#include <muduo/base/Logging.h>
#include <muduo/net/Endian.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

#include <boost/bind.hpp>

#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class EchoClient : boost::noncopyable
{
    public:
        EchoClient(EventLoop* loop, const InetAddress& serverAddr)
            : loop_(loop),
              client_(loop, serverAddr, "EchoClient")
    {
        client_.setConnectionCallback(boost::bind(&EchoClient::onConnection, this, _1));
        client_.setMessageCallback(boost::bind(&EchoClient::onMessage, this, _1, _2, _3));
    }

    void connect()
    {
        client_.connect();
    }

    private:

    EventLoop* loop_;
    TcpClient client_;

    void onConnection(const TcpConnectionPtr& conn)
    {

        LOG_INFO << conn->localAddress().toIpPort() << " -> "
            << conn->peerAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");

        if (!conn->connected())
            loop_->quit();

        conn->send("love", 4);
    }

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time)
    {

        muduo::string msg(buf->retrieveAllAsString());
        LOG_INFO << conn->name() << " echoclient " 
                 << msg.size() << " bytes, "
                 << "data received at " << time.toString();
        conn->send(msg);
    }

};

int main(int argc, char* argv[])
{
    
    LOG_INFO << "pid = " << getpid();

    EventLoop loop;
    InetAddress serverAddr("127.0.0.1", 2007);

    EchoClient echoClient(&loop, serverAddr);
    echoClient.connect();
    loop.loop();

    return 0;
}
