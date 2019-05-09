#include "apiborneswifi.h"

ApiBornesWifi::ApiBornesWifi()
{

}

void ApiBornesWifi::API_Call()
{
    API_AccessWifi = new QNetworkAccessManager(this);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=sites-disposant-du-service-paris-wi-fi&rows=5000&facet=cp&facet=idpw&facet=etat2");
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = API_AccessWifi->get(request);
    connect(API_AccessWifi,SIGNAL(finished(QNetworkReply *)), this,SLOT(API_Results(QNetworkReply *)));
}

void ApiBornesWifi::API_Results(QNetworkReply *reply)
{
    m_list.clear();

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();

    for (auto val : arr)
    {
        QJsonObject objn = val.toObject();
        latitude = objn["geometry"].toObject()["coordinates"].toArray()[1].toDouble();
        longitude = objn["geometry"].toObject()["coordinates"].toArray()[0].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(157, 181, 233));

        geo.info.insert("Nom du site",objn["fields"].toObject()["nom_site"].toString());
        geo.info.insert("Adresse",objn["fields"].toObject()["arc_adresse"].toString());
        geo.info.insert("Code postal",objn["fields"].toObject()["cp"].toString());
        geo.info.insert("Nombre de bornes",objn["fields"].toObject()["nombre_de_borne_wifi"].toString());
        geo.info.insert("Etat",objn["fields"].toObject()["etat2"].toString());
        m_list << geo;
    }
    emit callFinished(m_list, BORNES_WIFI);
    reply->deleteLater();
}

Abstract_API::API_index ApiBornesWifi::getId()
{
    return BORNES_WIFI;
}

void ApiBornesWifi::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

QPixmap ApiBornesWifi::getPixmap()
{
    return QPixmap(":/Icons/iconwifi.png");
}
