#ifndef DIALOG_H
#define DIALOG_H

#include "mainwindow.h"
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
#include <QBarSet>
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:

    Ui::Dialog *ui;

    meteo *m_meteo;
    Pollution *p_pollution;
    IndiceUV *i_indice;
    Prevision *pm_prevision;
    QTableWidgetItem *table;
    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QGridLayout* gridLayout;


private slots:

void printHashmeteo();
void printHashprevision();
QHash <QString, QVariant> printHashpollution();
void printHashindice();
void pollutionChart();
void AQI();
void Icon();
};

#endif // DIALOG_H