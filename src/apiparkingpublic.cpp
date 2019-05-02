#include "apiparkingpublic.h"

apiParkingPublic::apiParkingPublic()
{

}

apiParkingPublic::~apiParkingPublic()
{
    delete networkManager;
    delete listParkingPublic;
}

int apiParkingPublic::getId()
{
    return PARKING_PUBLIC;
}

QPixmap apiParkingPublic::getPixmap()
{
    return QPixmap(":/Icons/iconparkingpublic.svg");
}

void apiParkingPublic::API_Results(QNetworkReply *reply)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    QJsonArray jsarr = jsobj["records"].toArray();

    for(QJsonValue jsval : jsarr){
        parkingPublic parking;
        GeoObj gObj;
        QJsonObject jsob = jsval.toObject();
        parking.voie = jsob["fields"].toObject()["nomvoie"].toString();
        parking.regprio = jsob["fields"].toObject()["regpri"].toString();
        parking.regpart = jsob["fields"].toObject()["regpar"].toString();
        parking.tarif = jsob["fields"].toObject()["tar"].toString();
        parking.longueur = jsob["fields"].toObject()["longueur_calculee"].toDouble();
        parking.largeur = jsob["fields"].toObject()["lar"].toDouble();
        parking.parite = jsob["fields"].toObject()["parite"].toString();
        parking.latitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[1].toDouble();
        parking.longitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[0].toDouble();

        if(utilitaire::inMap(parking.latitude, parking.longitude)){
            listParkingPublic->append(parking);
            gObj.latitude = parking.latitude;
            gObj.longitude =parking.longitude;
            gObj.pixmap = QPixmap(":/Icons/iconparkingpublic.svg");

            listGeoObj << gObj;
        }
    }

    emit callFinished(listGeoObj, PARKING_PUBLIC);
}

void apiParkingPublic::getInfo()
{
    networkManager = new QNetworkAccessManager(this);
    WidgetMap map;
    latCentre = QString::number(map.m_centreLatitude, 'g', 13);
    lonCentre = QString::number(map.m_centreLongitude, 'g', 13);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=stationnement-voie-publique-emplacements&rows=-1&facet=regpri&facet=regpar&facet=typsta&facet=arrond&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon);
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
}
