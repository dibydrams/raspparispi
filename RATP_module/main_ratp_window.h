#ifndef MAIN_RATP_WINDOW_H
#define MAIN_RATP_WINDOW_H

#include "stoppoint.h"
#include "tools.h"
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
    QNetworkReply *replyGlobal;
    QNetworkReply *replyUni;
    QByteArray *replydata;
    QJsonArray resultArray;
    QJsonObject rootObject;
    QJsonDocument perimetreStifJson;
    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;
    static QList<QPointF> StaticpointList;
    static QList<StopPoint> StaticstopPointList;

    void DoGlobalRequest();
    void DoUniRequest(int _index);
    void ReadSaveStifJson();
    //    void NetworkCleanup();
public slots:
    void replyFinishedGlobal();
    void replyFinishedUni();
    void ShowUni();
    void GetUniReqIndex(int);

private:
    Ui::Main_RATP_Window *ui;
};

#endif // MAIN_RATP_WINDOW_H
