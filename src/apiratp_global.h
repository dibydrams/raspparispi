#ifndef APIRATP_GLOBAL_H
#define APIRATP_GLOBAL_H

#include "Abstract_API.h"
#include "stoppoint.h"
#include "transport.h"
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

    WidgetMap widgetmap;

    QJsonDocument perimetreStifJson;
    QJsonDocument referentielStifJson;

    QList<Abstract_API::GeoObj> geoList;
    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;
    QList<Transport> busList;
    QList<Transport> metroList;
    QList<Transport> railList;

    int indexTranspForUniReq;
    int indexStationForUniReq;

private:
    void GeoPoints();
    void PeriStifJson();
    void RefStifJson();

public slots:
    void getInfo() override;

private slots:
    QJsonDocument LoadJson(QString fileName);

signals:
    void callFinished(QList<Abstract_API::GeoObj>, API_index);
};

#endif // APIRATP_GLOBAL_H
