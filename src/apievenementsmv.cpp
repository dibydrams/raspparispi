#include "apievenementsmv.h"
#include "icon.h"

ApiEvenementsMV::ApiEvenementsMV()
{

}

void ApiEvenementsMV::API_Call() // Gestion du call à l'API
{
    API_Access = new QNetworkAccessManager(this);

    //  Accès aux settings de widgetmap.h
    //  double conf_longitude  = settingsAccess.m_centreLongitude;
    //  double conf_latitude = settingsAccess.m_centreLatitude;
    double conf_longitude  = WidgetMap::centreLongitude;
    double conf_latitude = WidgetMap::centreLatitude;

    QString lat = QString::number(conf_latitude);
    QString lon = QString::number(conf_longitude);

    QUrl url("https://api.predicthq.com/v1/events/?country=FR&active.gte=2019-05-10&active.lte=2019-05-10&within=1km@" + lat + "," + lon +"&category=expos, sports, community, concerts, conferences, festivals");
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer wH3fafHllNhQBCFfhFkQbNTUToSpql"));

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

void ApiEvenementsMV::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{  
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["results"].toArray();
    for ( auto val :  arr) {

        QJsonObject objn = val.toObject();
        longitude = objn["location"].toArray()[0].toDouble();
        latitude = objn["location"].toArray()[1].toDouble();

        // Traitement de l'horaire de début
        QString horaire;
        QString tmp = objn["start"].toString();
        horaire = tmp.at(11);
        horaire = horaire + tmp.at(12);
        horaire = horaire + "h" + tmp.at(14);
        horaire = horaire + tmp.at(15);

        // Traitement de l'adresse
        QString tmp2 = objn["entities"].toArray()[0].toObject()["formatted_address"].toString();
       QStringList elem = tmp2.split("\n");
       QString adresse = elem.join(", ");

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(252, 181, 75));
        geo.id = EVENEMENTS;

        geo.info.insert("Titre : ", objn["title"].toString());
        geo.info.insert("Catégorie : ", objn["category"].toString());
        geo.info.insert("Horaire : ", horaire);
        geo.info.insert("Lieu: ", objn["entities"].toArray()[0].toObject()["name"].toString());
        geo.info.insert("Adresse : ", adresse);

       m_list << geo;
    }

    emit callFinished(m_list, EVENEMENTS);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}

// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index ApiEvenementsMV::getId()
{
    return EVENEMENTS;
}

void ApiEvenementsMV::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //qDebug() << "acces settings carte centreLongitude: " << WidgetMap::centreLongitude;
    //qDebug() << "acces settings carte centreLatitude: " << WidgetMap::BBOXmaxLongitude;
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiEvenementsMV::getPixmap()
{
    return QPixmap(":/Icons/eventarene.png"); // icône PNG préférable
}
