#pragma once

#include "../server.hh"
#include "config.hh"
#include "loginwidget.hh"
#include <QFile>
#include <QFont>
#include <QFontDatabase>
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
    QList<Server *> serverList;  //服务器列表
    Server *newServer = nullptr; //新建服务器实例
    // TODO 这里警告提示已匹配但从未访问
    LoginWidget *loginPage = nullptr; //登陆窗口实例
    Config *settingPage = nullptr;    //设置窗口实例

    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

    void setStyle();    //设置qss样式
    void initUI();      //初始化界面
    void initConnect(); //初始化信号槽
    void addServer();   //添加服务器
    void sendMsg();     //发送消息
    void receiveMsg();  //接收消息
    void setting();     //打开设置页
    void login();       //打开登录页
    void addChannel();  //添加频道
  private:
    Ui::MainWidget *ui;
};
