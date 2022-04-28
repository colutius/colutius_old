#include "mainwidget.hh"
#include "loginwidget.hh"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("Colutius");
    initUI();
    initConnect();
    setStyle();
}

MainWidget::~MainWidget()
{
    //释放Server内存
    foreach (Server *server, this->serverList)
    {
        delete server;
    }
    delete ui;
}

//初始化UI
void MainWidget::initUI()
{
    //禁用侧边栏滚动条
    // ui->serverList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->serverList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //加载字体图标库
    int fontId = QFontDatabase::addApplicationFont(":/font/iconfont/iconfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    const auto &fontname = fontFamilies.at(0);
    QFont iconfont;
    iconfont.setFamily(fontname);
    iconfont.setPointSize(40);
    //设置图标
    ui->sendBtn->setFont(iconfont);
    ui->sendBtn->setText(QChar(0xe60c));
    ui->addServerBtn->setFont(iconfont);
    ui->addServerBtn->setText(QChar(0xe696));
    ui->settingBtn->setFont(iconfont);
    ui->settingBtn->setText(QChar(0xe8b8));
}

//设置qss样式
void MainWidget::setStyle()
{
    QFile qssfile(":/qss/Widget.qss");
    qssfile.open(QFile::ReadOnly);
    QString str = qssfile.readAll();
    this->setStyleSheet(str);
}

//初始化信号槽
void MainWidget::initConnect()
{
    connect(ui->addServerBtn, &QPushButton::clicked, this, &MainWidget::login);
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWidget::sendMsg);
    connect(ui->settingBtn, &QPushButton::clicked, this, &MainWidget::setting);
}

//添加服务器
void MainWidget::addServer()
{
    //跳转结束，马上删除凑和连接
    this->newServer->socket->tcpSocket->disconnect(this);

    //添加到服务器列表
    this->serverList.append(this->newServer);
    //添加到侧边栏
    ui->serverList->addItem(this->newServer->serverItem);
    connect(this->newServer->socket->tcpSocket, &QTcpSocket::readyRead, this, &MainWidget::receiveMsg);
    this->newServer = nullptr;
}

//发送消息
void MainWidget::sendMsg()
{
    QString msg = ui->msgEdit->text();
    // TODO判断当前所在服务器及频道
    int currentServerIndex = 0;
    // 发送消息
    if (serverList.at(currentServerIndex)->sendMsg(msg))
    {
        qDebug() << "发送成功";
        QListWidgetItem *msgBubble = new QListWidgetItem(msg);
        msgBubble->setTextAlignment(2);
        ui->msgList->addItem(msgBubble);
    }
}

//接收消息
void MainWidget::receiveMsg()
{
    foreach (Server *server, this->serverList)
    {
        QByteArray buf = server->socket->tcpSocket->readAll();
        if (buf.size() > 0)
        {
            QListWidgetItem *msg = new QListWidgetItem(buf);
            ui->msgList->addItem(msg);
            if (QString(buf).split(" ")[0] == "PING")
            {
                server->sendMsg("PONG " + QString(buf).split(" ")[1]);
            }
        }
    }
}

//打开设置页
void MainWidget::setting()
{
    this->settingPage = new Config();
}

//打开登录页
void MainWidget::login()
{
    this->newServer = new Server;
    this->loginPage = new LoginWidget(newServer);

    // addServer();
    //实测只有这个readyRead信号能用，其他像connected甚至自定义信号都用不了
    //不知道什么原因！！！！！！焯！
    //因为连接到服务器服务器肯定会发送数据，这个信号也一定会被触发，所以可以用这个信号凑和
    //不过这是一次性的用法，跳转之后应该马上删除
    //如果没有跳转，在对话框的析构函数中删除连接
    connect(this->newServer->socket->tcpSocket, &QTcpSocket::readyRead, this, &MainWidget::addServer);
}
