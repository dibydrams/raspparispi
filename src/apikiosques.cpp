#include "apikiosques.h"

apikiosques::apikiosques()
{

}

int apikiosques::getId()
{
    return KIOSQUES;

}

QPixmap apikiosques::getPixmap()
{
    return QPixmap(":/Icons/iconekiosques.png");
}

void apikiosques::API_call()
{
    API_access=new QNetworkAccessManager(this);
    currentReply=API_access->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=liste_des_kiosques_presse_a_paris&facet=code_postal&facet=statut&geofilter.distance=48.8716%2C2.34599%2C600&timezone=Europe%2FParis&rows=-1")));
    connect(API_access, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_results(QNetworkReply*)));

}

void apikiosques::API_results(QNetworkReply *reply)
{
    m_list.clear();
    doc=QJsonDocument::fromJson(reply->readAll());
    obj=doc.object();
    arr=obj["records"].toArray();
    for(auto val:arr){
        QJsonObject objn=val.toObject();
        latitude=objn["fields"].toObject().value("geo_point_2d").toArray()[0].toDouble();
        longitude=objn["fields"].toObject().value("geo_point_2d").toArray()[1].toDouble();
        statut=objn["fields"].toObject().value("statut").toString();
        adresse=objn["fields"].toObject().value("adresse").toString();

        GeoObj geo;
        geo.latitude=latitude;
        geo.longitude=longitude;
        geo.pixmap=QPixmap(":/Icons/iconekiosques.png");


        m_list<<geo;
    }
    emit callFinished(m_list, KIOSQUES);
    reply->deleteLater();
}

void apikiosques::getInfo()
{
   API_call();
}
