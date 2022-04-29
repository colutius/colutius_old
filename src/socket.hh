#pragma once

#include <QSslSocket>
#include <QTcpSocket>
class Socket
{
  public:
    QTcpSocket *tcpSocket;

    Socket();
    ~Socket();

    void connect(const QString &host, int port) const;          //连接到服务器
    bool closeConnect() const;                                  //断开服务器连接
    bool login(const QString &nick, const QString &user) const; //登录服务器
    int sendMsg(const QString &msg) const;                      //发送消息
};
