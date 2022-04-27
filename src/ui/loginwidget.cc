#include "loginwidget.hh"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(Server *server, QWidget *parent) : QWidget(parent), ui(new Ui::LoginWidget)
{
    this->server = server;
    ui->setupUi(this);
    initConnect();
    this->show();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//初始化信号槽
void LoginWidget::initConnect()
{
    connect(ui->connectBtn, &QPushButton::clicked, this, &LoginWidget::connect2Server);
}

//连接到服务器
bool LoginWidget::connect2Server()
{
    //获取窗口输入
    this->server->host = ui->hostEdit->text();
    this->server->port = ui->portEdit->text().toInt();
    this->server->nick = ui->nickEdit->text();
    this->server->user = ui->userEdit->text();
    this->server->serverItem->setText(this->server->host.at(0));
    //连接到服务器
    if (this->server->connect())
    {
        this->close();
        return true;
    }
    return false;
}
