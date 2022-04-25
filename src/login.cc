#include "login.hh"
#include "ui_login.h"

Login::Login(QWidget *parent) : QWidget(parent), ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("登陆");
    setStyle();
}

Login::~Login()
{
    delete ui;
}

void Login::setStyle()
{
    QFile file(":/qss/Login.qss"); //通过文件路径创建文件对象
    file.open(QFile::ReadOnly);    //文件打开方式
    QString str = file.readAll();  //获取qss中全部字符
    this->setStyleSheet(str);      //设置样式表
}
