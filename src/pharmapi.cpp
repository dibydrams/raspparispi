#include "pharmapi.h"

pharmapi::pharmapi()
{

}

void pharmapi::API_Call() // Gestion du call à l'API
{
   API_Access = new QNetworkAccessManager(this);

    QUrl url("https://api.predicthq.com/v1/events/?country=FR&active.gte=2019-05-10&active.lte=2019-05-10&within=1km@48.871602,2.345994&category=expos, sports, community, concerts, conferences, festivals");
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer wH3fafHllNhQBCFfhFkQbNTUToSpql"));

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

void pharmapi::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["results"].toArray();
    for ( auto val :  arr) {

        QJsonObject objn = val.toObject();
        longitude = objn["location"].toArray()[0].toDouble();
        latitude = objn["location"].toArray()[1].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = QPixmap();
        geo.id = getId();

       m_list << geo;
    }

    emit callFinished(m_list);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}

// Mon identifiant au sein de l'enumération (classe mère)
int pharmapi::getId()
{
    return EVENEMENTS;
}

void pharmapi::getInfo()
{
    API_Call();
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap pharmapi::getPixmap()
{
    return QPixmap(":/Icons/pharmicon.png"); // icône PNG préférable
}
