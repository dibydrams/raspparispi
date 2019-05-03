#include "apifontaines.h"

apifontaines::apifontaines()
{

}

int apifontaines::getId()
{
    return FONTAINES;

}

QPixmap apifontaines::getPixmap()
{
     return QPixmap(":/Icons/iconefontaines.png");  // a rajouter dans sources:
}

void apifontaines::API_call()
{
    API_access=new QNetworkAccessManager(this);
    currentReply=API_access->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=fontaines-a-boire&facet=arro&facet=modele&facet=a_boire&geofilter.distance=48.8716+%2C+2.34599%2C+600&timezone=Europe%2FParis&rows=-1")));
    connect(API_access, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_results(QNetworkReply*)));

}

void apifontaines::API_results(QNetworkReply *reply)
{
    m_list.clear();
    doc=QJsonDocument::fromJson(reply->readAll());
    obj=doc.object();
    arr=obj["records"].toArray();
    for(auto val:arr){
        QJsonObject objn=val.toObject();
        latitude=objn["fields"].toObject().value("geo_point_2d").toArray()[0].toDouble();
        longitude=objn["fields"].toObject().value("geo_point_2d").toArray()[1].toDouble();
        modele=objn["fields"].toObject().value("modele").toString();
        adresse=objn["fields"].toObject().value("adr_s").toString();
        ouv_hiver=objn["fields"].toObject().value("ouv_hiver").toString();
        sdf=objn["fields"].toObject().value("sdf").toString();
        en_service=objn["fields"].toObject().value("en_service").toString();
        drink=objn["fields"].toObject().value("a_boire").toInt();


        GeoObj geo;
        geo.latitude=latitude;
        geo.longitude=longitude;
        geo.pixmap=QPixmap(":/Icons/iconefontainesmap.png");


        m_list<<geo;
    }
    emit callFinished(m_list, FONTAINES);
    reply->deleteLater();

}

void apifontaines::getInfo()
{
    API_call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}
