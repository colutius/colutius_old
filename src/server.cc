#include "server.hh"

Server::Server(QObject *parent) : QObject{parent}
{
    // 初始化
    this->socket = new Socket;
    this->serverItem = new QListWidgetItem;
    // QListWidgetItem居中显示
    this->serverItem->setTextAlignment(4);
    // this->serverAction = new QAction;
    // this->serverBtn = new QPushButton;
    // this->serverBtn->setMaximumSize(35, 50);
    // this->serverBtn->setMinimumSize(35, 50);
    QObject::connect(this->socket->tcpSocket, &QTcpSocket::readyRead, this, &Server::readyRead);
}
Server::~Server()
{
    delete this->serverItem;
    delete this->socket;
    foreach (QListWidgetItem *channelItem, this->channelList)
    {
        delete channelItem;
    }
}

//连接服务器
void Server::connect() const
{
    this->socket->connect(this->host, this->port);
}

//登录
bool Server::login() const
{
    return this->socket->login(this->nick, this->user);
}

//发送消息
int Server::sendMsg(const QString &msg) const
{
    return this->socket->sendMsg(msg);
}

void Server::readyRead()
{
    this->isReadyRead = true;
}
