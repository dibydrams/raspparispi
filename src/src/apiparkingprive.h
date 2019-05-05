#ifndef APIPARKINGPRIVE_H
#define APIPARKINGPRIVE_H

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
    QString address;
    QString tarif1h;
    QString horaire;
    int plPMR;
    int plMoto;
    QString tarif1hMoto;
    QString velo;
    QString vElec;
    QString autopartage;
    int hauteur;
    double latitude;
    double longitude;
} parkingPrive;

class apiParkingPrive : public Abstract_API
{
    Q_OBJECT
public:
    apiParkingPrive();
    ~apiParkingPrive() override;
    int getId() override;
    QPixmap getPixmap() override;

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QList<parkingPrive> *listParkingPrive = new QList<parkingPrive>();
    QList<GeoObj> listGeoObj;
    QString latCentre;
    QString lonCentre;
    QString rayon = "1000";

private slots:
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIPARKINGPRIVE_H
