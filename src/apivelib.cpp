#include "apivelib.h"

apiVelib::apiVelib()
{

}

apiVelib::~apiVelib()
{
    delete networkManager;
    delete listVelib;
}

int apiVelib::getId()
{
    return VELIB;
}

QPixmap apiVelib::getPixmap()
{
    return QPixmap(":/Icons/iconvelib.png");
}

void apiVelib::API_Results(QNetworkReply *reply)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    QJsonArray jsarr = jsobj["records"].toArray();

    for(QJsonValue jsval : jsarr){
        velib velo;
        GeoObj gObj;
        QJsonObject jsob = jsval.toObject();
        velo.name = jsob["fields"].toObject()["station_name"].toString();
        QString status = jsob["fields"].toObject()["station_state"].toString();
        velo.emplacementsVides = jsob["fields"].toObject()["nbfreeedock"].toInt();
        velo.velosDisponibles = jsob["fields"].toObject()["nbebike"].toInt();
        velo.latitude = jsob["fields"].toObject()["geo"].toArray()[0].toDouble();
        velo.longitude = jsob["fields"].toObject()["geo"].toArray()[1].toDouble();

        if(status == "Operative") status = "Opérationnelle";
        else if(status == "Close") status = "Fermée";
        else status = "En travaux";

        velo.status = status;
        if(utilitaire::inMap(velo.latitude, velo.longitude)){
            listVelib->append(velo);

            gObj.latitude = velo.latitude;
            gObj.longitude =velo.longitude;
            gObj.pixmap = QPixmap(":/Icons/iconvelibmap.png");

            listGeoObj << gObj;
        }
    }

    emit callFinished(listGeoObj, VELIB);
}

void apiVelib::getInfo()
{
    networkManager = new QNetworkAccessManager(this);
    WidgetMap map;
    latCentre = map.m_centreLatitude;
    lonCentre = map.m_centreLongitude;
    qDebug() << "latCentre: " << latCentre;
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=velib-disponibilite-en-temps-reel&rows=-1&facet=overflowactivation&facet=creditcard&facet=kioskstate&facet=station_state");
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
}
