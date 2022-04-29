#include "socket.hh"

Socket::Socket()
{
    this->tcpSocket = new QTcpSocket;
}
Socket::~Socket()
{
    this->closeConnect();
    delete this->tcpSocket;
}

//建立连接
void Socket::connect(const QString &host, int port) const
{
    // TODO连接到服务器
    tcpSocket->connectToHost(host, port);
}

//断开连接
bool Socket::closeConnect() const
{
    if (this->tcpSocket->isOpen())
    {
        this->tcpSocket->close();
        return true;
    }
    return false;
}

//登录
bool Socket::login(const QString &nick, const QString &user) const
{
    // TODO登录到服务器
    if (this->sendMsg("NICK " + nick))
    {
        if (this->sendMsg("USER " + user + " 8 * :Colutius IRC Client"))
        {
            return true;
        }
    }
    return false;
}

//发送消息
int Socket::sendMsg(const QString &msg) const
{
    QByteArray buf = msg.toUtf8().append("\n");
    // TODO 有一处警告
    return tcpSocket->write(buf);
}
