#include "apiratp_station.h"

ApiRatp_Station::ApiRatp_Station()
{

}

void ApiRatp_Station::DoStationRequest()
{
    requestStation = new QNetworkRequest () ;
    requestStation->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    /*
     *  Get ID (STIF:StopPoint:...) by clicked (parameters or for in ratpGlobal.stopPointList);
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
