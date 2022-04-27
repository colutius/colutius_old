#pragma once

#include "socket.hh"
#include <QThread>

class Thread : public QThread
{
  public:
    bool runFlag = true;
    Socket *socket;

    Thread(Socket *socket);
    ~Thread();

    void run();            //线程函数
    void stop();           //停止线程
    QString receiveData(); //接收数据
};
