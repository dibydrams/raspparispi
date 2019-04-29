#include "apiratp_station.h"

ApiRatp_Station::ApiRatp_Station()
{
    perimetreStifJson = LoadJson(":/Datas/perimetre-tr-plateforme-stif.json");
    PeriStifJson();
}

void ApiRatp_Station::DoStationRequest()
{
    requestStation = new QNetworkRequest () ;
    requestStation->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    /*
     *  Get ID (STIF:StopPoint:...) by clicked
     */

//    QByteArray encodedCode = QUrl::toPercentEncoding(Get ID);
    requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef=STIF%3AStopPoint%3AQ%3A411414%3A"));
//    requestStation->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-unitaire-stif/stop-monitoring?MonitoringRef="+encodedCode));

    replyStation = managerStation->get(*requestStation);

    connect(replyStation, &QNetworkReply::finished, this, &ApiRatp_Station::replyFinishedStation);

}

void ApiRatp_Station::replyFinishedStation()
{
//    qDebug() << replyStation->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyStation->readAll());

    QJsonValue Siri = doc.object().value("Siri");

    // Object from Stop Monitoring Delivery
    QJsonArray SMDarray = Siri.toObject()["ServiceDelivery"].toObject()["StopMonitoringDelivery"].toArray();
    // Object from Monitored Stop Visit
    QJsonArray MSVarray = SMDarray[0].toObject()["MonitoredStopVisit"].toArray();

    uiratp->showFinishedStation(MSVarray);
}

QJsonDocument ApiRatp_Station::LoadJson(QString fileName)
{
    QFile jsonFile(fileName);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void ApiRatp_Station::PeriStifJson()
{
    for (int i = 0; i < perimetreStifJson.array().count(); ++i)
    {
        // codifligne_line_externalcode = ID du Bus/Train/RER
        QString externalcodeLine = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["codifligne_line_externalcode"].toString();
        // reflex_zde_nom = Nom de l'arret,
        QString nomZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["reflex_zde_nom"].toString();
        // monitoringref_zde = Stif ID de l'arret,
        QString monoRefZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["monitoringref_zde"].toString();
        // gtfs_stop_id = ID de l'arret,
        QString idZDE = perimetreStifJson.array().at(i).toObject()["fields"].toObject()["gtfs_stop_id"].toString();


        // xy = Coordonnées GPS de l'arret
        double coordX = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(0).toDouble();
        double coordY = perimetreStifJson.array().at(i).toObject()["geometry"].toObject()["coordinates"].toArray().at(1).toDouble();
        QPointF coordsZDE(coordX,coordY);

        pointList.append(coordsZDE);
        StopPoint newStopPoint(externalcodeLine, nomZDE, monoRefZDE, idZDE, coordsZDE, i);
        stopPointList.append(newStopPoint);
    }

    std::sort(stopPointList.begin(), stopPointList.end(), StopPoint::compareStopPoint);
}


// Mon identifiant au sein de l'enumération (classe mère)
int ApiRatp_Station::getId()
{
    return RATP;
}

void ApiRatp_Station::getInfo()
{
    DoStationRequest();
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Station::getPixmap()
{
    return QPixmap(":/Icons/iconevents.png"); // icône PNG préférable
}
