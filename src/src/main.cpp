#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include "dialogtraduction.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTranslator translator;
//    Dialogtraduction d;

//    //qDebug()<< translator.load("src_en.qm") ;
//    a.installTranslator(&translator);

    MainWindow w;

    // Add style css on mainwindow
    QFile file(":/Style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    w.setStyleSheet(styleSheet);

    /*Traducteur*/



    w.show();


    return a.exec();
}
