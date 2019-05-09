#include "mainwindow.h"
#include <QApplication>
#include "dialogtraduction.h"
#include <QTranslator>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

//    //Traduction en fonction de la langue système
//    QString locale = QLocale::system().name().section('_', 0, 0);             //QLocale::system().name() renvoie le code "fr_FR" ("fr" la langue, et "FR" le pays).
//    QTranslator translator;                                                   //Grâce à section, on coupe la string en deux autours de "_" et on récupère le premier code
//    translator.load(QString(":/Traduction/src_") + locale);
//    translator.load(":/Traduction/src_en");
//    a.installTranslator(&translator);


    // Add style css on mainwindow
    QFile file(":/Style/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    w.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}
