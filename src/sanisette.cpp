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
 * @details fonction qui va faire appel à l'API aopendata.paris (qui s'apppuie sur OpenDataSoft).
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
 * @details fonction qui va lire le retour de la requête au format Json et va remplir les propriété de l'objet.
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
        double arrondissement = objectFields["arrondissement"].toDouble();
        QString strArrondissement = QString("%1").arg(arrondissement);
        QString numero_voie = objectFields["numero_voie"].toString();
        QString nom_voie = objectFields["nom_voie"].toString();
        QString valueHO = objectFields["horaires_ouverture"].toString();
        QString adr=numero_voie+" "+nom_voie+ " Paris "+ strArrondissement;
        QString strLong = QString("%1").arg(longitude, 0, 'g', 17);
        qDebug()<<"strLong  "<< strLong;

        QString strLat = QString("%1").arg(latitude, 0, 'g', 17);
        qDebug()<<"strLat "<< strLat;
        dist=new distance(qApp,strLat,strLong,"pedestrian");
        int distance=dist->getDistanceInMeters();
        //QString distancestr=QString(distance);//
        qDebug()<<"distances : : "<<distance;
       // int timeTravelPedestrian=dist->getTimetravel();
        //QString timeTravelPedstr=QString(timeTravelPedestrian);//
        //qDebug()<<"timeTravelPedstr : : "<<timeTravelPedestrian;
       // dist->~distance();
//        dist=new class distance(qApp,strLat,strLong,"car");
//        int timeTravelCar=dist->getTimetravelWithTraffic();
//        QString timeTravelCarstr=QString(timeTravelCar);
//        qDebug()<<"timeTravelCarstr : : "<<timeTravelCarstr;
//        dist->~distance();
//        dist=new class distance(qApp,strLat,strLong,"bus");
//        int timeTravelBus=dist->getTimetravelWithTraffic();
//        QString timeTravelBusstr=QString(timeTravelBus);
//        qDebug()<<"timeTravelBusstr : : "<<timeTravelBusstr;
//        dist->~distance();
        qDebug()<<" adr : : "<<adr;
//        QMap<QString,QString> mapsanisette;
//        mapsanisette["adrr"]=adr;
//        mapsanisette["horaire"]=valueHO;
        // remplissage de geoObj
        GeoObj geo;
        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(),QColor(42, 132, 255));//
        m_list << geo;
    }
    emit callFinished(m_list, TOILETTES);
}

/**
 * @brief sanisette::getInfo
 * @details redéfinition de la fonction virtuel pure de ABSTRACT_API
 */
void sanisette::getInfo(){
    sanisetteAPI_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}


