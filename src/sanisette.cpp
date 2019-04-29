#include "sanisette.h"

sanisette::sanisette()
{

}

int sanisette::getId()
{
    return TOILETTES;
}

QPixmap sanisette::getPixmap()
{
    return QPixmap(":/Icons/toilettes.png");
}

void sanisette::sanisetteAPI_Call(){
    manager=new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=sanisettesparis&facet=arrondissement&facet=horaires_ouverture"));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(readJsonSani()));
}

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
            geo.pixmap = QPixmap();
            m_list << geo;
        }
        emit callFinished(m_list, TOILETTES);
}

void sanisette::getInfo(){
    sanisetteAPI_Call();
}


