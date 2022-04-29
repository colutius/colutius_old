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
    if (!this->serverList.isEmpty())
    {
        foreach (Server *server, this->serverList)
        {
            //直接delete的话会导致退出时段错误
            server->deleteLater();
        }
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
    // 打开登录窗口
    connect(ui->addServerBtn, &QPushButton::clicked, this, &MainWidget::login);
    // 发送消息
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWidget::sendMsg);
    // 打开设置窗口
    connect(ui->settingBtn, &QPushButton::clicked, this, &MainWidget::setting);
    // 添加频道
    connect(ui->addChannelBtn, &QPushButton::clicked, this, &MainWidget::addChannel);
    // 刷新频道列表
    connect(ui->serverList, &QListWidget::currentItemChanged, this, &MainWidget::refreshChannelList);
    // 回车发送消息
    connect(ui->msgEdit, &QLineEdit::editingFinished, this, &MainWidget::sendMsg);
    // 回车添加频道
    connect(ui->channelEdit, &QLineEdit::editingFinished, this, &MainWidget::addChannel);
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
    ui->serverList->setCurrentRow(this->serverList.size() - 1);
    connect(this->newServer->socket->tcpSocket, &QTcpSocket::readyRead, this, &MainWidget::receiveMsg);
    this->newServer = nullptr;
}

// 发送消息
void MainWidget::sendMsg()
{
    // 未添加服务器忽略
    if (this->serverList.isEmpty())
    {
        return;
    }
    // 输入框为空忽略
    QString msg = ui->msgEdit->text();
    if (msg.isEmpty())
    {
        return;
    }
    ui->msgEdit->clear();
    // 判断当前所在服务器及频道
    int currentServerIndex = ui->serverList->currentRow();
    int currentChannelIndex = ui->channelList->currentRow();
    // 构造发送消息
    msg =
        "PRIVMSG " + this->serverList.at(currentServerIndex)->channelList.at(currentChannelIndex)->text() + " :" + msg;
    // 发送消息
    if (serverList.at(currentServerIndex)->sendMsg(msg))
    {
        qDebug() << "发送成功";
        auto *msgBubble = new QListWidgetItem(msg);
        msgBubble->setTextAlignment(2);
        ui->msgList->addItem(msgBubble);
    }
}

//接收消息
void MainWidget::receiveMsg()
{
    //遍历所有服务器
    foreach (Server *server, this->serverList)
    {
        if (!server->isReadyRead)
        {
            continue;
        }
        //接收消息，isReadyRead复位
        QStringList buf = QString(server->socket->tcpSocket->readAll()).split("\r\n");
        server->isReadyRead = false;
        //分别遍历处理每一行消息
        foreach (QString i, buf)
        {
            //行非空
            if (i.isEmpty())
            {
                continue;
            }
            //一条消息以空格分隔
            QStringList msg = i.split(" ");
            // PING消息，直接回复，不打印
            if (msg[0] == "PING")
            {
                server->sendMsg("PONG " + i + "\r\n");
                continue;
            }
            //用户消息，接收并打印
            //有时候接收到的数据会在其中随机某个地方多出来个\n
            //导致有可能这一行用空格分隔之后只有一组，访问msg[1]会崩溃
            //所以先判断一下length保险一些
            if (msg.length() > 1 && msg[1] == "PRIVMSG")
            {
                QString mainMsg;
                for (int i = 3; i < msg.length(); i++)
                {
                    mainMsg += (msg[i] + " ");
                }
                ui->msgList->addItem(msg[0].split("!")[0] + mainMsg);
                continue;
            }
            //服务器状态信息
            else
            {
                qDebug() << i;
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

//添加频道
void MainWidget::addChannel()
{
    //无服务器啥也不做
    if (this->serverList.isEmpty())
    {
        return;
    }
    //获取频道名称
    QString channel = ui->channelEdit->text();
    //输入框为空啥也不做
    if (channel.isEmpty())
    {
        return;
    }
    ui->channelEdit->clear();
    //获取当前选中服务器
    int serverIndex = ui->serverList->currentRow();
    //发送JOIN信号
    if (this->serverList.at(serverIndex)->sendMsg("JOIN " + channel + "\r\n"))
    {
        //界面添加频道
        this->channelItem = new QListWidgetItem(channel);
        this->serverList.at(serverIndex)->channelList.append(channelItem);
        ui->channelList->addItem(channelItem);
        ui->channelList->setCurrentRow(this->serverList.at(serverIndex)->channelList.size() - 1);
    }
}

void MainWidget::refreshChannelList()
{
    //清空频道列表
    //不能用ui.channelList->clear();clear会释放所有Item的内存，之后就用不了了
    //这里直接按数量来删除的话总会剩一个，实测+2之后可以删干净了
    for (int i = 0; i < ui->channelList->count() + 2; ++i)
    {
        QListWidgetItem *item = ui->channelList->takeItem(0);
    }

    // ui->channelList->clear();
    //  判断当前所在服务器
    int currentServerIndex = ui->serverList->currentRow();
    //添加当前选中服务器加入的频道到列表显示
    foreach (QListWidgetItem *channel, this->serverList.at(currentServerIndex)->channelList)
    {
        qDebug() << "+1";
        ui->channelList->addItem(channel);
    }
}