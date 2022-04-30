#include "config.hh"
#include "ui_config.h"

Config::Config(QDialog *parent) : QDialog(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    QImage logo;
    logo.load(":/img/img/icon.svg");
    ui->logoView->setPixmap(QPixmap::fromImage(logo).scaled(200, 200));
    //模态对话框
    this->setModal(true);
    this->show();
}

Config::~Config()
{
    delete ui;
}
