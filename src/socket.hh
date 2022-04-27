#pragma once
#include <QTcpSocket>

class Socket
{
  public:
    Socket();
    ~Socket();

    bool initSocket();                      //初始化socket
    bool connect(QString host, int port);   //连接到服务器
    bool closeConnect();                    //断开服务器连接
    bool login(QString nick, QString user); //登录服务器
    QString receiveData();                  //接收数据
    void sendMsg(QString msg);              //发送消息
};
