#include "sanisette.h"

/**
 * @brief sanisette::sanisette
 * @details constructeur simple
 */
sanisette::sanisette()
{

}

/**
 * @brief sanisette::getId
 * @return
 */
Abstract_API::API_index sanisette::getId()
{
    return TOILETTES;
}

QPixmap sanisette::getPixmap()
{
    return QPixmap(":/Icons/toilette.png");
}

/**
 * @brief sanisette::sanisetteAPI_Call
 */
void sanisette::sanisetteAPI_Call(){
    manager=new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=sanisettesparis&rows=500&facet=arrondissement&facet=horaires_ouverture"));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(readJsonSani()));
}

/**
 * @brief sanisette::readJsonSani
 */
void sanisette::readJsonSani(){
    m_list.clear();
    QByteArray responseBit=reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(responseBit);
    QJsonObject replyObj = document.object();
    QJsonArray recordsJsonArray = replyObj["records"].toArray();

    foreach (const QJsonValue & value, recordsJsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject objectFields = obj["fields"].toObject();
        QVariantHash objHasdh = obj.toVariantHash();
        QJsonArray objectGeom = objectFields["geom_x_y"].toArray();
        double latitude = objectGeom[0].toDouble();
        double longitude = objectGeom[1].toDouble();

        // remplissage de geoObj
        GeoObj geo;
        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(),QColor(42, 132, 255));//
        m_list << geo;
    }

    dist=new distance(qApp,"48.8977","2.3594000000000506","car");
   // qDebug()<<"getTimetravel : : "<<dist->getDistanceInMeters();
    qDebug()<<"*** Distance car compte rendu objet ***";
    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
    qDebug()<<"arrival :: "<<dist->getArrival();
    dist->~distance();

    dist=new distance(qApp,"48.8977","2.3594000000000506","pedestrian");
    qDebug()<<"*** Distance pedestrian compte rendu objet ***";
    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
    qDebug()<<"arrival :: "<<dist->getArrival();
    dist->~distance();

    dist=new distance(qApp,"48.8977","2.3594000000000506","bicycle");
    qDebug()<<"*** Distance bicycle compte rendu objet ***";
    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
    qDebug()<<"arrival :: "<<dist->getArrival();
    dist->~distance();

    emit callFinished(m_list, TOILETTES);
}

/**
 * @brief sanisette::getInfo
 */
void sanisette::getInfo(){
    sanisetteAPI_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}


