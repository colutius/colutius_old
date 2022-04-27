#pragma once

#include "../server.hh"
#include "loginwidget.hh"
#include <QList>
#include <QWidget>
namespace Ui
{
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

  public:
    QList<Server *> serverList; //服务器列表

    LoginWidget *w; //登陆窗口实例

    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void initConnect();
    void addServer(); //添加服务器
    void sendMsg();   //发送消息
    void setting();   //打开设置页
  private:
    Ui::MainWidget *ui;
};
