#include "apiparkingpublic.h"

apiParkingPublic::apiParkingPublic()
{

}

apiParkingPublic::~apiParkingPublic()
{
    delete networkManager;
    delete listParkingPublic;
}

Abstract_API::API_index apiParkingPublic::getId()
{
    return PARKING_PUBLIC;
}

QPixmap apiParkingPublic::getPixmap()
{
    return QPixmap(":/Icons/iconparkingpublic.svg");
}

void apiParkingPublic::copyGeoObj()
{
    GeoObj gObj;
    for(parkingPublic p : *listParkingPublic){
        gObj.latitude = p.latitude;
        gObj.longitude =p.longitude;
        gObj.pixmap = Icon::iconMapOffStr(getPixmap(), QString::number(p.nb), Qt::yellow);

        listGeoObj << gObj;
    }
}

void apiParkingPublic::API_Results(QNetworkReply *reply)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();
    QJsonArray jsarr = jsobj["records"].toArray();

    for(QJsonValue jsval : jsarr){
        Voie v;
        parkingPublic p;
        QJsonObject jsob = jsval.toObject();
        v.rue = jsob["fields"].toObject()["nomvoie"].toString()+" "+jsob["fields"].toObject()["typevoie"].toString();
        v.codePostal = jsob["fields"].toObject()["arrond"].toInt() + 75000;

        if(v.rue == " "){
            double lat = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[1].toDouble();
            double lon = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[0].toDouble();

            coordToAddr *addr = new coordToAddr(this, lat, lon);
            v.rue = addr->getStreet();
            v.codePostal = addr->getPostalCode();
            qDebug() << v.rue << "\t" << v.codePostal;
        }

        if(!listVoie->contains(v)){
            p.v = v;
            p.tarif = jsob["fields"].toObject()["tar"].toString();
            p.nb = 1;
            p.latitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[1].toDouble();
            p.longitude = jsob["fields"].toObject()["geo_shape"].toObject()["coordinates"].toArray()[0].toDouble();

            if(utilitaire::inMap(p.latitude, p.longitude)){
                listParkingPublic->append(p);
                listVoie->append(v);
            }
        }

        else {
            for(int i=0; i<listParkingPublic->size(); ++i){
                if(listParkingPublic->operator[](i).v == v){
                    listParkingPublic->operator[](i).nb++;
                    break;
                }
            }
        }

    }

    copyGeoObj();
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
    QApplication::setOverrideCursor(Qt::WaitCursor);
}
