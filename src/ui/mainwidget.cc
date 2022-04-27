#include "mainwidget.hh"
#include "loginwidget.hh"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("Colutius");
    this->serverNum = 0;
    initConnect();
}

MainWidget::~MainWidget()
{
    delete ui;
}

//初始化信号槽
void MainWidget::initConnect()
{
    connect(ui->addServerBtn, &QPushButton::clicked, this, &MainWidget::addServer);
}

//添加服务器
void MainWidget::addServer()
{
    Server *newServer = new Server;
    this->serverList[this->serverNum] = newServer;
    w = new LoginWidget(newServer);
    ui->serverBoxLayout->addWidget(newServer->serverBtn);
}

//发送消息
void MainWidget::sendMsg()
{
    QString msg = ui->msgEdit->text() + "\n";
    // TODO判断当前所在服务器及频道
    int currentServerIndex = 0;
    // 发送消息
    serverList[currentServerIndex]->sendMsg(msg);
}
