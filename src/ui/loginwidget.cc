#include "loginwidget.hh"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(Server *server, QDialog *parent) : QDialog(parent), ui(new Ui::LoginWidget)
{
    //关闭对话框时调用析构函数
    this->setAttribute(Qt::WA_DeleteOnClose);
    //服务器图标随机颜色列表
    this->colors.append(QColor(0xdcff93));
    this->colors.append(QColor(0xff9b6a));
    this->colors.append(QColor(0xf1b8e4));
    this->colors.append(QColor(0xd9b8f1));
    this->colors.append(QColor(0xb8f1ed));
    this->colors.append(QColor(0xf3d64e));
    this->colors.append(QColor(0xf1ccb8));
    this->colors.append(QColor(0xed9678));

    this->server = server;
    ui->setupUi(this);
    this->setWindowTitle("登录");
    initConnect();
    setStyle();
    //模态对话框
    this->setModal(true);
    this->show();
}

LoginWidget::~LoginWidget()
{
    //没有点击连接，直接关闭对话框的时候，把server的内存释放了
    if (this->server->host == "#ColutiusYyds!")
    {
        this->server->socket->tcpSocket->disconnect();
        delete server;
    }
    delete ui;
}

//设置qss样式
void LoginWidget::setStyle()
{
    QFile qssfile(":/qss/Login.qss");
    qssfile.open(QFile::ReadOnly);
    QString str = qssfile.readAll();
    this->setStyleSheet(str);
}

//获取字母对应图标ID
QChar getFontID(QChar letter)
{
    switch (letter.unicode())
    {
    case u'a':
        return QChar(0xeb87);
    case u'b':
        return QChar(0xeb88);
    case u'c':
        return QChar(0xeb85);
    case u'd':
        return QChar(0xeb86);
    case u'e':
        return QChar(0xeb8a);
    case u'f':
        return QChar(0xeb89);
    case u'g':
        return QChar(0xeb8b);
    case u'h':
        return QChar(0xeb8d);
    case u'i':
        return QChar(0xeb8c);
    case u'j':
        return QChar(0xeb8e);
    case u'k':
        return QChar(0xeb97);
    case u'l':
        return QChar(0xeb8f);
    case u'm':
        return QChar(0xeb93);
    case u'n':
        return QChar(0xeb91);
    case u'o':
        return QChar(0xeb90);
    case u'p':
        return QChar(0xeb92);
    case u'q':
        return QChar(0xeb95);
    case u'r':
        return QChar(0xeb96);
    case u's':
        return QChar(0xeb9f);
    case u't':
        return QChar(0xeb98);
    case u'u':
        return QChar(0xeb9b);
    case u'v':
        return QChar(0xeb99);
    case u'w':
        return QChar(0xeb9a);
    case u'x':
        return QChar(0xeb9e);
    case u'y':
        return QChar(0xeb9d);
    case u'z':
        return QChar(0xeb9c);
    default:
        return QChar(0xeb94);
    }
}

//初始化信号槽
void LoginWidget::initConnect()
{
    connect(ui->connectBtn, &QPushButton::clicked, this, &LoginWidget::connect2Server);
}

//连接到服务器
void LoginWidget::connect2Server()
{

    // TODO 检查输入数据是否合法或给lineEdit添加限制，防止后续操作崩溃
    // 获取窗口输入
    this->server->host = ui->hostEdit->text();
    this->server->port = ui->portEdit->text().toInt();
    this->server->nick = ui->nickEdit->text();
    this->server->user = ui->userEdit->text();
    this->server->passwd = ui->passwdEdit->text();
    // 任意输入框为空都不能继续执行
    if (server->host.isEmpty() || server->nick.isEmpty() || server->user.isEmpty())
    {
        return;
    }
    ui->connectBtn->setEnabled(false);
    //设置字体
    int fontId = QFontDatabase::addApplicationFont(":/font/iconfont/letter.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    const auto &fontname = fontFamilies.at(0);
    QFont letterFont;
    letterFont.setFamily(fontname);
    letterFont.setPointSize(40);
    this->server->serverItem->setFont(letterFont);
    //设置server图标
    QStringList name = this->server->host.split(".");
    this->server->serverItem->setText(getFontID(name.at(1)[0]));
    //设置随机颜色
    // TODO 这里有个CLion警告，不会修
    this->server->serverItem->setForeground(this->colors.at(QRandomGenerator::global()->generate() % colors.length()));
    //连接到服务器
    this->server->connect();
    connect(this->server->socket->tcpSocket, &QTcpSocket::connected, this, &LoginWidget::login);
}

void LoginWidget::login()
{
    qDebug() << "连接成功，正在登录……";
    if (this->server->login())
    {
        qDebug() << "登录成功！";
        this->close();
    }
    else
    {
        qDebug() << "登录失败！";
        ui->connectBtn->setEnabled(true);
    }
}
