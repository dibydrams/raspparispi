#include "apiparkingpublic.h"
#include <QThread>

apiParkingPublic::apiParkingPublic()
{
    firstCall();
    loop.exec();
}

apiParkingPublic::~apiParkingPublic()
{
    delete networkManager;
    delete listParkingPublic;
    delete listVoie;
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
    emit callFinished(listGeoObj, PARKING_PUBLIC);
}

void apiParkingPublic::firstRequest()
{
    QSettings *save = new QSettings("raspparispi", "parking_public");
    for(int i=0; i<listParkingPublic->size(); ++i){
        save->setValue(QString::number(i)+"/rue", listParkingPublic->operator[](i).v.rue);
        save->setValue(QString::number(i)+"/codePostal", listParkingPublic->operator[](i).v.codePostal);
        save->setValue(QString::number(i)+"/tarif", listParkingPublic->operator[](i).tarif);
        save->setValue(QString::number(i)+"/nb", listParkingPublic->operator[](i).nb);
        save->setValue(QString::number(i)+"/latitude", listParkingPublic->operator[](i).latitude);
        save->setValue(QString::number(i)+"/longitude", listParkingPublic->operator[](i).longitude);
    }
    loop.exit();
}

void apiParkingPublic::firstCall()
{
    networkManager = new QNetworkAccessManager(this);
    latCentre = QString::number(WidgetMap::centreLatitude, 'g', 13);
    lonCentre = QString::number(WidgetMap::centreLongitude, 'g', 13);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=stationnement-voie-publique-emplacements&rows=-1&facet=regpri&facet=regpar&facet=typsta&facet=arrond&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon);
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
}

void apiParkingPublic::API_Results(QNetworkReply *reply)
{
    listGeoObj.clear();
    listVoie->clear();
    listParkingPublic->clear();

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
    firstRequest();
}

void apiParkingPublic::getInfo()
{
    networkManager = new QNetworkAccessManager(this);

    QUrl url("");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(copyGeoObj()));

    QApplication::setOverrideCursor(Qt::WaitCursor);
}
