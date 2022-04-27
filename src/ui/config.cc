#include "config.hh"
#include "ui_config.h"

Config::Config(QWidget *parent) : QWidget(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    this->show();
}

Config::~Config()
{
    delete ui;
}
