#include "thread.hh"

Thread::Thread(Socket *socket)
{
    this->socket = socket;
}

Thread::~Thread()
{
    this->exit();
}
void Thread::run()
{
    while (true)
    {
        if (receiveData().length() == 0)
        {
            continue;
        }
        else
        {
            qDebug() << "接收到数据" + receiveData();
            // TODO显示接收到的消息
        }
    }
}
QString Thread::receiveData()
{
    return this->socket->receiveData();
}
