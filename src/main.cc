#include "ui/mainwidget.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget w;
    w.show();

    return QApplication::exec();
}
