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

//设置qss样式
void Widget::setStyle()
{
    QFile file(":/qss/Widget.qss"); //通过文件路径创建文件对象
    file.open(QFile::ReadOnly);     //文件打开方式
    QString str = file.readAll();   //获取qss中全部字符
    this->setStyleSheet(str);       //设置样式表
}

void Widget::initUI()
{
    initIconFont(); //加载图标字体库

    //设置按钮图标
    ui->sendBtn->setFont(iconfont);
    ui->sendBtn->setText(QChar(0xe60c));
    ui->newServerBtn->setFont(iconfont);
    ui->newServerBtn->setText(QChar(0xe696));
    ui->settingBtn->setFont(iconfont);
    ui->settingBtn->setText(QChar(0xe8b8));
    ui->server0->setFont(iconfont);
    ui->server0->setText(QChar(0xe62b));
}

//加载字体图标库
void Widget::initIconFont()
{
    int fontId = QFontDatabase::addApplicationFont(":/font/iconfont/iconfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    const auto &fontname = fontFamilies.at(0);
    this->iconfont.setFamily(fontname);
    this->iconfont.setPointSize(40);
}
