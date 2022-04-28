#pragma once

#include <QDialog>

namespace Ui
{
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

  public:
    explicit Config(QDialog *parent = nullptr);
    ~Config();

  private:
    Ui::Config *ui;
};
