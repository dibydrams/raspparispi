#ifndef APIRATP_GLOBAL_H
#define APIRATP_GLOBAL_H

#include "Abstract_API.h"
#include "icon.h"
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
    API_index getId() override;
    QPixmap getPixmap() override;

    WidgetMap widgetmap;

    QSettings *m_settings;

    QList<GeoObj> geoList;
    QList<QPointF> pointList;
    QList<StopPoint> stopPointList;
    QList<Transport> transportList;
    QList<Transport> busList;
    QList<Transport> metroList;
    QList<Transport> railList;

    int indexTranspForUniReq;
    int indexStationForUniReq;

    void FilledTransportLists();

private:
    QJsonDocument perimetreStifJson;
    QJsonDocument referentielStifJson;

    void GeoPoints();
    void PeriStifJson();
    void RefStifJson();

public slots:
    void getInfo() override;

private slots:
    QJsonDocument LoadJson(QString fileName);

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIRATP_GLOBAL_H
