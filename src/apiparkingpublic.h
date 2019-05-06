#ifndef APIPARKINGPUBLIC_H
#define APIPARKINGPUBLIC_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "utilitaire.h"
#include "widgetmap.h"
#include "icon.h"
#include "coordtoaddr.h"
#include "Abstract_API.h"

typedef struct _voie{
    QString rue;
    int codePostal;

    bool operator==(const struct _voie& v){
        return (v.rue == rue && v.codePostal == codePostal);
    }
}Voie;

typedef struct{
    Voie v;
    QString tarif;
    double latitude;
    double longitude;
    int nb;
} parkingPublic;

class apiParkingPublic : public Abstract_API
{
    Q_OBJECT
public:
    apiParkingPublic();
    ~apiParkingPublic() override;
    API_index getId() override;
    QPixmap getPixmap() override;

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QList<parkingPublic> *listParkingPublic = new QList<parkingPublic>();
    QList<Voie> *listVoie = new QList<Voie>();
    QList<GeoObj> listGeoObj;
    QString latCentre;
    QString lonCentre;
    QString rayon = "1000";

    void copyGeoObj();

private slots:
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // APIPARKINGPUBLIC_H
