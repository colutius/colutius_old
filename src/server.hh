#pragma once
#include "socket.hh"
#include "thread.hh"
#include <QString>

class Server
{
  public:
    QString host; //服务器地址
    int port;     //服务器端口
    QString nick; //昵称
    QString user; //用户

    Socket *socket;
    Thread *thread; //消息监听线程

    Server();
    ~Server();

    bool connect();            //连接服务器
    void sendMsg(QString msg); //发送消息
    void receiveData(QString msg);
};
