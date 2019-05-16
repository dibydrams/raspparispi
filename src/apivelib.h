#ifndef APIVELIB_H
#define APIVELIB_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "utilitaire.h"
#include "widgetmap.h"
#include "icon.h"

#include "Abstract_API.h"

typedef struct{
    QString name;
    QString status;
    int emplacementsVides;
    int velosElectriqueDisponibles;
    int velosMecaniqueDisponibles;
    double latitude;
    double longitude;
}velib;

class apiVelib : public Abstract_API
{
    Q_OBJECT

public:
    apiVelib();
    ~apiVelib() override;
    API_index getId() override;
    QPixmap getPixmap() override;

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QList<velib> *listVelib = new QList<velib>();
    QList<GeoObj> listGeoObj;
    QString latCentre;
    QString lonCentre;

private slots:
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIVELIB_H
