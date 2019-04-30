#include "apiterrasses.h"
#include <QMetaEnum>
#include <QTextStream>
#include <QDebug>

ApiTerrasses::ApiTerrasses()
{

}
void ApiTerrasses::API_Call() // Gestion du call à l'API
{
   API_Access = new QNetworkAccessManager(this);

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=etalages-et-terrasses");
    QNetworkRequest request;
    request.setUrl(url);


    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

void ApiTerrasses::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();
    for ( auto val :  arr) {

         QJsonObject objn = val.toObject();
         QJsonValue val2 = objn.value(QString("fields"));
         QJsonObject item = val2.toObject();
        longitude = item["geo_point_2d"].toArray()[1].toDouble();
        latitude = item["geo_point_2d"].toArray()[0].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = QPixmap();

       m_list << geo;
    }

    emit callFinished(m_list, TERRASSES);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}

// Mon identifiant au sein de l'enumération (classe mère)
int ApiTerrasses::getId()
{
    return TERRASSES;
}

void ApiTerrasses::getInfo()
{
    API_Call();
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiTerrasses::getPixmap()
{
    return QPixmap(":/Icons/iconeterrace.png"); // icône PNG préférable
}
