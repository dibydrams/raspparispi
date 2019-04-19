#include "mainwindow.h"
#include "unirequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UniRequest u;
    w.show();

    return a.exec();
}
