#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:

    Ui::MainWindow *ui;

private slots:
   void dialog();



};

#endif // MAINWINDOW_H
