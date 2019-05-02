#ifndef APIPARKINGPUBLIC_H
#define APIPARKINGPUBLIC_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "utilitaire.h"
#include "widgetmap.h"

#include "Abstract_API.h"

typedef struct{
    QString voie;
    QString regprio;
    QString regpart;
    QString tarif;
    double longueur;
    double largeur;
    QString parite;
    double latitude;
    double longitude;
} parkingPublic;

class apiParkingPublic : public Abstract_API
{
    Q_OBJECT
public:
    apiParkingPublic();
    ~apiParkingPublic() override;
    int getId() override;
    QPixmap getPixmap() override;

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QList<parkingPublic> *listParkingPublic = new QList<parkingPublic>();
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

#endif // APIPARKINGPUBLIC_H
