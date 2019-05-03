#include "apiratp_search.h"

ApiRatp_Search::ApiRatp_Search()
{

}

void ApiRatp_Search::DoUniRequest(QString _transport, QString _station)
{
    managerUni = new QNetworkAccessManager(this) ;
    requestUni = new QNetworkRequest () ;
    requestUni->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QByteArray encodedCodeline;
    QByteArray encodedIdZde;
//    qDebug() << "code Transport" << indexTranspForUniReq << "code Station" << indexStationForUniReq;
    encodedCodeline = QUrl::toPercentEncoding(_transport);
    encodedIdZde = QUrl::toPercentEncoding(_station.replace(0,1,"s"));

//    qDebug() << encodedIdZde << encodedCodeline;

    requestUni->setUrl(QUrl("https://api-lab-trone-stif.opendata.stif.info/service/tr-vianavigo/departures?line_id="+encodedCodeline+"&stop_point_id="+encodedIdZde));

    replyUni = managerUni->get(*requestUni);

    connect(replyUni, &QNetworkReply::finished, this, &ApiRatp_Search::replyFinishedUni);
}

void ApiRatp_Search::replyFinishedUni()
{
    qDebug() << replyUni->error();
    QJsonDocument doc = QJsonDocument::fromJson(replyUni->readAll());

    QJsonArray arrayDoc = doc.array();

    emit ShowFinishedUni(arrayDoc);

//    uiratp->showFinishedUni(arrayDoc);
}


// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index ApiRatp_Search::getId()
{
    return RATP;
}

void ApiRatp_Search::getInfo()
{

}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Search::getPixmap()
{
    return QPixmap(":/Icons/iconSearch.png"); // icône PNG préférable
}
