#include "widget.hh"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("colutius");
}

Widget::~Widget()
{
    delete ui;
}
