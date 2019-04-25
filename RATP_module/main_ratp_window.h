#ifndef MAIN_RATP_WINDOW_H
#define MAIN_RATP_WINDOW_H

#include "stoppoint.h"
#include "tools.h"
#include "transport.h"
#include "unirequest.h"

#include <QDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class Main_RATP_Window;
}

class Main_RATP_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Main_RATP_Window(QWidget *parent = nullptr);
    ~Main_RATP_Window();

    UniRequest *uniReqWindow;

    QString keyapi = "Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz";
    QNetworkAccessManager *manager;
    QNetworkRequest *requestGlobal;
    QNetworkRequest *requestUni;
    QNetworkRequest *requestStation;
    QNetworkReply *replyGlobal;
    QNetworkReply *replyUni;
    QNetworkReply *replyStation;
    QByteArray *replydata;
    QJsonArray resultArray;
    QJsonObject rootObject;
    QJsonDocument perimetreStifJson;
    QJsonDocument referentielStifJson;
    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;
    QList<Transport> busList;
    QList<Transport> metroList;
    QList<Transport> rerList;

    void DoGlobalRequest();
    void DoUniRequest();
    void PeriJson();
    void RefJson();
    //    void NetworkCleanup();
    void DoUniRequest(int);
    void DoStationOnlyRequest();
public slots:
    void replyFinishedGlobal();
    void replyFinishedUni();
    void replyFinishedStation();
    void ShowTransports();
    void ShowTransportStopPoints(int);

private:
    Ui::Main_RATP_Window *ui;
};

#endif // MAIN_RATP_WINDOW_H
