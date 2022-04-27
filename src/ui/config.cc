#include "config.hh"
#include "ui_config.h"

Config::Config(QWidget *parent) : QDialog(parent), ui(new Ui::Config)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");
    this->exec();
}

Config::~Config()
{
    delete ui;
}
