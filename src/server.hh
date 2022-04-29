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
    QString host; //服务器地址
    int port;     //服务器端口
    QString nick; //昵称
    QString user; //用户

    bool isReadyRead = false;
    QListWidgetItem *serverItem;
    // QAction *serverAction;
    // QPushButton *serverBtn;

    Socket *socket;

    explicit Server(QObject *parent = nullptr);
    ~Server();

    void readyRead();
    void connect(); //连接服务器
    bool login();
    int sendMsg(QString msg);      //发送消息
    void receiveData(QString msg); //接收消息
};
