#include "apievenementsmv.h"
#include "icon.h"
#include "widgetmap.h"

ApiEvenementsMV::ApiEvenementsMV()
{

}

void ApiEvenementsMV::API_Call() // Gestion du call à l'API
{
    API_Access = new QNetworkAccessManager(this);

    // Accès aux settings de widgetmap.h
    double conf_longitude  = settingsAccess.m_centreLongitude;
    double conf_latitude = settingsAccess.m_centreLatitude;

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

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOffStr(getPixmap(), "O", QColor(252, 181, 75));

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
    //qDebug() << "acces settings carte centreLatitude: " << WidgetMap::centreLatitude;
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiEvenementsMV::getPixmap()
{
    return QPixmap(":/Icons/eventarene.png"); // icône PNG préférable
}
