#include "config.hh"
#include "ui_config.h"

Config::Config(QDialog *parent) : QDialog(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    //模态对话框
    this->setModal(true);
    this->show();
}

Config::~Config()
{
    delete ui;
}
