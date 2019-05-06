#include "apivelib.h"

apiVelib::apiVelib()
{

}

apiVelib::~apiVelib()
{
    delete networkManager;
    delete listVelib;
}

Abstract_API::API_index apiVelib::getId()
{
    return VELIB;
}

QPixmap apiVelib::getPixmap()
{
    return QPixmap(":/Icons/iconvelib.png");
}

void apiVelib::API_Results(QNetworkReply *reply)
{
    listGeoObj.clear();
    listVelib->clear();
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
            if(status == "Opérationnelle")
                gObj.pixmap = Icon::iconMapOffStr(getPixmap(), QString::number(velo.velosDisponibles), QColor(214, 171, 220));
            else if(status == "Fermée")
                gObj.pixmap = Icon::iconMapOffClose(getPixmap(), QColor(214, 171, 220));
            else
                gObj.pixmap = Icon::iconMapOffStr(QPixmap(":/Icons/iconvelibwork.png"), QString::number(velo.velosDisponibles), QColor(214, 171, 220));

            listGeoObj << gObj;
        }
    }

    emit callFinished(listGeoObj, VELIB);
}

void apiVelib::getInfo()
{
    networkManager = new QNetworkAccessManager(this);
    WidgetMap map;
    latCentre = QString::number(map.m_centreLatitude, 'g', 13);
    lonCentre = QString::number(map.m_centreLongitude, 'g', 13);
    QString rayon = "1000";
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=velib-disponibilite-en-temps-reel&rows=-1&facet=overflowactivation&facet=creditcard&facet=kioskstate&facet=station_state&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon);
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
    QApplication::setOverrideCursor(Qt::WaitCursor);
}
