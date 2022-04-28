#pragma once

#include <QTcpSocket>

class Socket
{
  public:
    QTcpSocket *tcpSocket;

    Socket();
    ~Socket();

    void connect(QString host, int port);   //连接到服务器
    bool closeConnect();                    //断开服务器连接
    bool login(QString nick, QString user); //登录服务器
    QString receiveData();                  //接收数据
    int sendMsg(QString msg);               //发送消息
};
