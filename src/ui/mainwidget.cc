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
    connect(ui->addServerBtn, &QPushButton::clicked, this, &MainWidget::addServer);
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWidget::sendMsg);
    connect(ui->settingBtn, &QPushButton::clicked, this, &MainWidget::setting);
}

//添加服务器
void MainWidget::addServer()
{
    Server *newServer = new Server; //创建新的Server实例

    this->serverList.append(newServer);

    //打开登录窗口获取服务器信息
    this->loginPage = new LoginWidget(newServer);
    ui->serverList->addItem(newServer->serverItem);
}

//发送消息
void MainWidget::sendMsg()
{
    QString msg = ui->msgEdit->text() + "\n";
    // TODO判断当前所在服务器及频道
    int currentServerIndex = 0;
    // 发送消息
    serverList.at(currentServerIndex)->sendMsg(msg);
    QListWidgetItem *msgBubble = new QListWidgetItem(msg);
    msgBubble->setTextAlignment(2);
    ui->msgList->addItem(msgBubble);
}

//打开设置页
void MainWidget::setting()
{
    this->settingPage = new Config();
}
