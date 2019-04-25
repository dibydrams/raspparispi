#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tools.h"
#include "stoppoint.h"
#include "unirequest.h"
#include "main_ratp_window.h"
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QAuthenticator>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Main_RATP_Window ratpWindow;
//    UniRequest *uniReqWindow;

//    QString keyapi = "Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz";
//    QNetworkAccessManager *manager;
//    QNetworkRequest *requestGlobal;
//    QNetworkRequest *requestUni;
//    QNetworkReply *replyGlobal;
//    QNetworkReply *replyUni;
//    QByteArray *replydata;
//    QJsonArray resultArray;
//    QJsonObject rootObject;
//    QJsonDocument perimetreStifJson;
//    QList<QPointF> pointList;
//    QList<StopPoint> stopPointList;
//    static QList<QPointF> StaticpointList;
//    static QList<StopPoint> StaticstopPointList;

//    void DoGlobalRequest();
//    void DoUniRequest(int _index);
//    void ReadSaveStifJson();
//    //    void NetworkCleanup();
//public slots:
//    void replyFinishedGlobal();
//    void replyFinishedUni();
//    void ShowUni();
//    void GetUniReqIndex(int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
