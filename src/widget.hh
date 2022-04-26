#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

  public:
    QFont iconfont; //图标字体

    Widget(QWidget *parent = nullptr);
    ~Widget();

    void setStyle();
    void initIconFont();
    void initUI();

  private:
    Ui::Widget *ui;
};
