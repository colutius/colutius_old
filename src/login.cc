#include "login.hh"
#include "ui_login.h"

Login::Login(QWidget *parent) : QWidget(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆");
}

Login::~Login()
{
    delete ui;
}
