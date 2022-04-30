#pragma once

#include "../server.hh"
#include "../socket.hh"
#include <QDialog>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QList>
#include <QRandomGenerator>
namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QDialog
{
    Q_OBJECT

  public:
    Server *server;       // server实例
    QList<QColor> colors; //随机颜色列表

    explicit LoginWidget(Server *server, QDialog *parent = nullptr);
    ~LoginWidget() override;

    void initConnect();    //初始化信号槽
    void connect2Server(); //连接到服务器
    void login();          //登录
    void setStyle();

  private:
    Ui::LoginWidget *ui;
};
