#pragma once
#include "../server.hh"
#include "../socket.hh"
#include <QWidget>

namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

  public:
    Server *server;
    explicit LoginWidget(Server *server, QWidget *parent = nullptr);
    ~LoginWidget();

    void initConnect();
    bool connect2Server();
    Ui::LoginWidget *ui;

  private:
};
