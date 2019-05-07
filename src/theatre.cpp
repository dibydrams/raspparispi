#include "theatre.h"

/**
 * @brief theatre::theatre
 * @details constructeur simple et vide
 */
theatre::theatre()
{

}

/**
 * @brief theatre::getId
 * @return le numéro index de THEATRE  : type int
 */
Abstract_API::API_index theatre::getId()
{
    return THEATRE;
}

/**
 * @brief theatre::getPixmap
 * @return le QPixmap de l'icone theatre (pour le boutton de commande en bas de l'IHM)
 */
QPixmap theatre::getPixmap()
{
    return QPixmap(":/Icons/theatre.png");
}

/**
 * @brief theatre::theatreAPI_Call
 * @details fonction/slots qui effectue l'appel à l'API opendatasoft
 */
void theatre::theatreAPI_Call(){
    manager=new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://public.opendatasoft.com/api/records/1.0/search/?dataset=evenements-publics-cibul&q=theatre&rows=60&facet=tags&facet=placename&facet=department&facet=region&facet=city&facet=date_start&facet=date_end&facet=pricing_info&facet=updated_at&facet=city_district&refine.department=Paris&refine.date_start=2019&refine.tags=th%C3%A9%C3%A2tre&timezone=Europe%2FParis"));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(readJsonTheatre()));
}

/**
 * @brief theatre::readJsonTheatre
 * @details fonction qui va lire la réponse retournée par la requête envoyée précédement (theatreAPI_Call)
 * Fait appel à la classe "addrToCoord" qui va permettre de traduire les adresses en point gps (latitude et longitude).
 */
void theatre::readJsonTheatre(){
    m_list.clear();
    QByteArray responseBit = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(responseBit);
    QJsonObject replyObj = document.object();
    QJsonArray recordsJsonArray = replyObj["records"].toArray();

    foreach (const QJsonValue & value, recordsJsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject objectFields = obj["fields"].toObject();

        //coordinatedHelper
        QString adr=objectFields["address"].toString()+" "+objectFields["department"].toString();
        coordHelper=new addrToCoord(qApp,adr);
        double longitude=coordHelper->getLongitude();
        double latitude=coordHelper->getLatitude();
        coordHelper->deleteLater();

        // remplissage de geoObj
        GeoObj geo;
        geo.longitude =longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(247, 212, 120));
        m_list << geo;
    }
    emit callFinished(m_list, THEATRE);
}

/**
 * @brief theatre::getInfo
 * @details redifinition de la fonction virtuel pur getInfo(); fait appel à theatreAPI_Call();
 */
void theatre::getInfo(){
    theatreAPI_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}


