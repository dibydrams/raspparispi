#ifndef DIALOG_H
#define DIALOG_H

//#include "mainwindow.h"
#include <QDialog>
#include <QMainWindow>
#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <meteo.h>
#include <pollution.h>
#include <indiceuv.h>
#include <prevision.h>
#include <QTableWidgetItem>
#include <QtCharts/QBarSet>
#include <QGridLayout>
#include <QChart>
#include <QChartView>
#include <QDialog>
#include <QtCharts>
#include "dialogtraduction.h"

#include "ui_dialogmeteo.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setvignette();

private:

    Ui::Dialog *ui;

    meteo *m_meteo;
    Pollution *p_pollution;
    IndiceUV *i_indice;
    Prevision *pm_prevision;
    Dialogtraduction *l_lang;
    QStandardItemModel *table;
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QGridLayout* gridLayout;
    QStandardItem *item1 = new QStandardItem;
    QStandardItem *item2 = new QStandardItem;
    QStandardItem *item3 = new QStandardItem;
    QStandardItem *item4 = new QStandardItem;
    QStandardItem *item5 = new QStandardItem;
    QStandardItem *item6 = new QStandardItem;
    QStandardItem *item7 = new QStandardItem;



private slots:

void printHashmeteo();
void printHashprevision();
QHash <QString, QVariant> printHashpollution();
void printHashindice();
void pollutionChart();
void AQI();
void Icon();
void loadlanguage(QString lang);
//void updatedial();


};

#endif // DIALOG_H
