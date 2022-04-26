#include "socket.hh"

Socket::Socket()
{
}

bool Socket::initSocket()
{
    // TODO初始化socket
    return true;
}

bool Socket::connect(QString host, int port)
{
    // TODO连接到服务器
    return true;
}

bool Socket::login(QString nick, QString user)
{
    // TODO登录到服务器
    return true;
}

QString Socket::receiveData()
{
    // TODO从服务器接收消息
    return "hello";
}

void Socket::sendMsg(QString msg)
{
    // TODO发送消息
}
