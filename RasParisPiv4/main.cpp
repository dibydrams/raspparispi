#include "mainwindow.h"
#include "meteo.h"
#include "pollution.h"
#include <QApplication>
#include "indiceuv.h"
#include <QHash>
#include <QVariantHash>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
