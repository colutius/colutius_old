#include "thread.hh"

Thread::Thread(Socket *socket)
{
    this->socket = socket;
}

Thread::~Thread()
{
    this->stop();
    this->wait();
    qDebug() << "thread exit!";
}

void Thread::run()
{
    while (this->runFlag)
    {
        if (receiveData().length() == 0)
        {
            continue;
        }
        else
        {
            // qDebug() << "接收到数据" + receiveData();
            //  TODO显示接收到的消息
        }
    }
}

void Thread::stop()
{
    this->runFlag = false;
}
QString Thread::receiveData()
{
    return this->socket->receiveData();
}
