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
void Socket::connect(QString host, int port)
{
    // TODO连接到服务器
    tcpSocket->connectToHost(host, port);
}

//断开连接
bool Socket::closeConnect()
{
    if (this->tcpSocket->isOpen())
    {
        this->tcpSocket->close();
        return true;
    }
    return false;
}

//登录
bool Socket::login(QString nick, QString user)
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
int Socket::sendMsg(QString msg)
{
    QByteArray buf = msg.toUtf8().append("\n");
    return tcpSocket->write(buf);
}
