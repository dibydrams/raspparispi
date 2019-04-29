#ifndef APIRATP_GLOBAL_H
#define APIRATP_GLOBAL_H

#include "Abstract_API.h"
#include "stoppoint.h"
#include "transport.h"
#include "uiratp.h"
#include "widgetmap.h"

#include <QFile>
#include <QJsonDocument>
#include <QList>
#include <QObject>



class ApiRatp_Global : public Abstract_API
{
    Q_OBJECT

public:
    ApiRatp_Global();
    int getId() override;
    QPixmap getPixmap() override;

    Uiratp *uiratp;
    WidgetMap widgetmap;

    QJsonDocument perimetreStifJson;
    QJsonDocument referentielStifJson;

    QList<GeoObj> geoList;
    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;
    QList<Transport> busList;
    QList<Transport> metroList;
    QList<Transport> rerList;

    int indexTranspForUniReq;
    int indexStationForUniReq;



private:
    void GeoPoints();
    void PeriStifJson();
    void RefStifJson();

private slots:
    void getInfo() override;
    QJsonDocument LoadJson(QString fileName);
};

#endif // APIRATP_GLOBAL_H
