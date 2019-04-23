#include "mainwindow.h"
#include "unirequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow ratp;
    UniRequest u;
    ratp.show();

    return a.exec();
}
