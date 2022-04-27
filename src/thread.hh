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
    void run();
    void stop();
    QString receiveData(); //接收数据
};
