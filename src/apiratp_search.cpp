#include "apiratp_search.h"

ApiRatp_Search::ApiRatp_Search()
{

}

void ApiRatp_Search::DoUniRequest()
{
    requestUni = new QNetworkRequest () ;
    requestUni->setRawHeader(QByteArray("Authorization"), QByteArray("Basic ZnJhbmNvaXNmbG9yaWFuNEBnbWFpbC5Db206ZmxvZmxvMTIz"));

    QByteArray encodedCodeline;
    QByteArray encodedIdZde;
//    qDebug() << "code Transport" << indexTranspForUniReq << "code Station" << indexStationForUniReq;

//    if (ui->radioBus->isChecked())
//    {
//        encodedCodeline = QUrl::toPercentEncoding(ratpGlobal->busList[ratpGlobal->indexTranspForUniReq].codeLine);
//        encodedIdZde = QUrl::toPercentEncoding(ratpGlobal->busList[ratpGlobal->indexTranspForUniReq].mySPList[ratpGlobal->indexStationForUniReq].idZDE.replace(0,1,"s"));
//    }
//    else if (ui->radioMetro->isChecked())
//    {
//        encodedCodeline = QUrl::toPercentEncoding(ratpGlobal->metroList[ratpGlobal->indexTranspForUniReq].codeLine);
//        encodedIdZde = QUrl::toPercentEncoding(ratpGlobal->metroList[ratpGlobal->indexTranspForUniReq].mySPList[ratpGlobal->indexStationForUniReq].idZDE.replace(0,1,"s"));
//    }
//    else
//    {
        encodedCodeline = QUrl::toPercentEncoding(ratpGlobal->railList[ratpGlobal->indexTranspForUniReq].codeLine);
        encodedIdZde = QUrl::toPercentEncoding(ratpGlobal->railList[ratpGlobal->indexTranspForUniReq].mySPList[ratpGlobal->indexStationForUniReq].idZDE.replace(0,1,"s"));
//    }

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

    uiratp->showFinishedUni(arrayDoc);
}


// Mon identifiant au sein de l'enumération (classe mère)
int ApiRatp_Search::getId()
{
    return RATP;
}

void ApiRatp_Search::getInfo()
{
    DoUniRequest();
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiRatp_Search::getPixmap()
{
    return QPixmap(":/Icons/iconStation.png"); // icône PNG préférable
}
