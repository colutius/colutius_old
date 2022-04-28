#include "server.hh"

Server::Server()
{
    this->socket = new Socket;
    this->serverItem = new QListWidgetItem;
    this->serverItem->setTextAlignment(4);
    // this->serverAction = new QAction;
    // this->serverBtn = new QPushButton;
    // this->serverBtn->setMaximumSize(35, 50);
    // this->serverBtn->setMinimumSize(35, 50);
}
Server::~Server()
{
    delete serverItem;
    delete socket;
}

//连接服务器
void Server::connect()
{
    this->socket->connect(this->host, this->port);
}

//登录
bool Server::login()
{
    return this->socket->login(this->nick, this->user);
}

//发送消息
int Server::sendMsg(QString msg)
{
    return this->socket->sendMsg(msg);
}
