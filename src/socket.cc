#include "socket.hh"

Socket::Socket()
{
}
Socket::~Socket()
{
    this->closeConnect();
}

//初始化socket
bool Socket::initSocket()
{
    // TODO初始化socket
    return true;
}

//建立连接
bool Socket::connect(QString host, int port)
{
    // TODO连接到服务器
    return true;
}

//断开连接
bool Socket::closeConnect()
{
    return true;
}

//登录
bool Socket::login(QString nick, QString user)
{
    // TODO登录到服务器
    return true;
}

//接收消息
QString Socket::receiveData()
{
    // TODO从服务器接收消息
    return "hello";
}

//发送消息
void Socket::sendMsg(QString msg)
{
    // TODO发送消息
}
