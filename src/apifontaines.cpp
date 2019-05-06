#include "apifontaines.h"

apifontaines::apifontaines()
{

}

apifontaines::~apifontaines()
{
    delete API_access;

}

Abstract_API::API_index apifontaines::getId()
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
    WidgetMap map;
    latCentre = QString::number(map.m_centreLatitude, 'g', 13);
    lonCentre = QString::number(map.m_centreLongitude, 'g', 13);
    QString rayon = "1000";
    qDebug() << "latCentre: " << latCentre;
    currentReply=API_access->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=fontaines-a-boire&facet=arro&facet=modele&rows=-1&facet=a_boire&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon)));
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
        if (drink==1) statut="P";
        else statut="X";



        GeoObj geo;
        geo.latitude=latitude;
        geo.longitude=longitude;
        geo.pixmap=Icon::iconMapOffStr(getPixmap(), statut, Qt::darkCyan);


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
