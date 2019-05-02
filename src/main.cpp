#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Add style css on mainwindow
    QFile file(":/Style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    w.setStyleSheet(styleSheet);

    w.show();


    return a.exec();
}
