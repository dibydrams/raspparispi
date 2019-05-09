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
 * @return int de l'index assigné à l'API
 */
Abstract_API::API_index sanisette::getId()
{
    return TOILETTES;
}

/**
 * @brief sanisette::getPixmap
 * @return Qpixmap représentant les Toilettes publiques
 */
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

    for (auto value :  recordsJsonArray) {
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
        QString strLat = QString("%1").arg(latitude, 0, 'g', 17);

        //remplissage du GeoObj
        GeoObj geo;
        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(),QColor(42, 132, 255));//
        geo.info.insert("adresse",adr);
        geo.info.insert("horaires",valueHO);
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
