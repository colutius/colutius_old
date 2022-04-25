#include "widget.hh"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("colutius");
    initUI();

    setStyle();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setStyle()
{
    QFile file(":/qss/Widget.qss"); //通过文件路径创建文件对象
    file.open(QFile::ReadOnly);     //文件打开方式
    QString str = file.readAll();   //获取qss中全部字符
    this->setStyleSheet(str);       //设置样式表
}

void Widget::initUI()
{
    int fontId = QFontDatabase::addApplicationFont(":/iconfont/iconfont/iconfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    const auto &fontname = fontFamilies.at(0);
    font.setFamily(fontname);
    font.setPointSize(40);
    ui->sendBtn->setFont(font);
    ui->sendBtn->setText(QChar(0xe60c));
    ui->newServerBtn->setFont(font);
    ui->newServerBtn->setText(QChar(0xe696));
    ui->settingBtn->setFont(font);
    ui->settingBtn->setText(QChar(0xe8b8));
    ui->server0->setFont(font);
    ui->server0->setText(QChar(0xe62b));
}
