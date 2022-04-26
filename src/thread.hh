#pragma once

#include "socket.hh"
#include <QThread>

class Thread : public QThread
{
  public:
    Socket *socket;
    Thread(Socket *socket);
    void run();

    QString receiveData(); //接收数据
};
