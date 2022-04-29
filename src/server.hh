#pragma once
#include "socket.hh"
#include <QAction>
#include <QListWidgetItem>
#include <QObject>
#include <QPushButton>
#include <QString>
class Server : public QObject
{
    Q_OBJECT
  public:
    QString host = "#ColutiusYyds!"; //服务器地址
    int port = 6667;                 //服务器端口
    QString nick;                    //昵称
    QString user;                    //用户

    bool isReadyRead = false;
    QListWidgetItem *serverItem;
    // QAction *serverAction;
    // QPushButton *serverBtn;

    Socket *socket;

    explicit Server(QObject *parent = nullptr);
    ~Server() override;

    void readyRead();
    void connect() const; //连接服务器
    bool login() const;
    int sendMsg(const QString &msg) const; //发送消息
};
