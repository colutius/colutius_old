#pragma once

#include <QDialog>
#include <QImage>

namespace Ui
{
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

  public:
    explicit Config(QDialog *parent = nullptr);
    ~Config() override;

  private:
    Ui::Config *ui;
};
