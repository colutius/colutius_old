#pragma once

#include <QFile>
#include <QWidget>
namespace Ui
{
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

  public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    void setStyle();

  private:
    Ui::Login *ui;
};
