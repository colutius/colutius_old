#include "server.hh"

Server::Server()
{
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
    delete thread;
    delete socket;
}

//连接服务器
bool Server::connect()
{
    this->socket = new Socket;
    if (this->socket->connect(this->host, this->port))
    {
        qDebug() << "连接成功！";
        if (this->socket->login(this->nick, this->user))
        {
            qDebug() << "登录成功！";
            //开启消息接收线程
            this->thread = new Thread(this->socket);
            this->thread->start();
        }
        else
        {
            qDebug() << "登录失败！";
            return false;
        }
        return true;
    }
    else
    {
        qDebug() << "连接失败！";
        return false;
    }
}

//发送消息
void Server::sendMsg(QString msg)
{
    this->socket->sendMsg(msg);
}

//接收消息
void Server::receiveData(QString msg)
{
}
