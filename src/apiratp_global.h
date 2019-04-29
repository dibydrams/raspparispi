#ifndef APIRATP_GLOBAL_H
#define APIRATP_GLOBAL_H

#include "Abstract_API.h"
#include "stoppoint.h"
#include "uiratp.h"

#include <QFile>
#include <QJsonDocument>



class ApiRatp_Global : public Abstract_API
{
public:
    ApiRatp_Global();
    int getId() override;
    QPixmap getPixmap() override;

    Uiratp *uiratp;

    QJsonDocument perimetreStifJson;

    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;

    void replyFinishedGlobal();

    QList<GeoObj> geoList;

    void GeoPoints();
private:
    void DoStationRequest();
    void PeriStifJson();

private slots:
    void getInfo() override;
    void replyFinishedStation();
    QJsonDocument LoadJson(QString fileName);
};

#endif // APIRATP_GLOBAL_H
