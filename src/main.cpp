#include "mainwindow.h"
#include <QApplication>
#include "dialogtraduction.h"
#include <QTranslator>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    /*QTranslator translator;
    qDebug()<< translator.load(":/Traduction/src_en.qm");
    qDebug() <<   a.installTranslator(&translator);*/


    MainWindow w;

    // Add style css on mainwindow
    QFile file(":/Style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    w.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}
