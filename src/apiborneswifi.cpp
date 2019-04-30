#include "apiborneswifi.h"

ApiBornesWifi::ApiBornesWifi()
{

}

void ApiBornesWifi::API_Call()
{
    API_AccessWifi = new QNetworkAccessManager(this);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=sites-disposant-du-service-paris-wi-fi&facet=cp&facet=idpw&facet=etat2");
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
        latitude = objn["fields"].toObject()["geo_point_2d"].toArray()[0].toDouble();
        longitude = objn["fields"].toObject()["geo_point_2d"].toArray()[1].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOffV2(getPixmap(), getId(), QColor(126, 170, 44));

        m_list << geo;
    }
    emit callFinished(m_list, BORNES_WIFI);
    reply->deleteLater();
}

int ApiBornesWifi::getId()
{
    return BORNES_WIFI;
}

void ApiBornesWifi::getInfo()
{
    API_Call();
}

QPixmap ApiBornesWifi::getPixmap()
{
    return QPixmap(":/Icons/iconwifi.png");
}
