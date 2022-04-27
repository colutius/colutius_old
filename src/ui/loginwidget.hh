#pragma once

#include "../server.hh"
#include "../socket.hh"
#include <QFont>
#include <QFontDatabase>
#include <QList>
#include <QRandomGenerator>
#include <QWidget>
namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

  public:
    Server *server;       // server实例
    QList<QColor> colors; //随机颜色列表

    explicit LoginWidget(Server *server, QWidget *parent = nullptr);
    ~LoginWidget();

    void initConnect();    //初始化信号槽
    bool connect2Server(); //连接到服务器

  private:
    Ui::LoginWidget *ui;
};
