#include "apikiosques.h"

apikiosques::apikiosques()
{

}

apikiosques::~apikiosques()
{
    delete API_access;

}

Abstract_API::API_index apikiosques::getId()
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

    //Acces aux setting de WidgetMap.h
    latCentre = QString::number(WidgetMap::centreLatitude, 'g', 13);
    lonCentre = QString::number(WidgetMap::centreLongitude, 'g', 13);

    QString rayon = "1000";
    qDebug() << "latCentre: " << latCentre;
    currentReply=API_access->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=liste_des_kiosques_presse_a_paris&rows=-1&facet=code_postal&facet=statut&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon)));
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
        lon=QString::number(longitude, 'g', 13);
        lat=QString::number(latitude, 'g', 13);
        dist=new distance(qApp,lon,lat);
        if (statut=="Ouvert") stat="O";
        else stat="F";


        GeoObj geo;
        geo.latitude=latitude;
        geo.longitude=longitude;
        if (stat=="O") geo.pixmap=Icon::iconMapOffStr(getPixmap(), stat, Qt::darkMagenta);
        else geo.pixmap=Icon::iconMapOffClose(getPixmap(), Qt::darkMagenta);

        /*Ce sont les informations que je souhaite récupéré du JSON, pour l'API kiosques.
         *Comme une "QMap <QString,QString> info" à été ajouté dans la classe Abstract_API.h,
         *celà nous permet de sélectionner les infos que nous souhaitons afficher, lors du clic.*/

        geo.info.insert("adresse",adresse);
        geo.info.insert("statut",statut);
        geo.info.insert("distance",(QString)dist->getDistanceInMeters());
        qDebug<<"distance"<<(QString)dist->getDistanceInMeters();



        m_list<<geo;
    }
    emit callFinished(m_list, KIOSQUES);
    reply->deleteLater();
}

void apikiosques::getInfo()
{
   API_call();
   QApplication::setOverrideCursor(Qt::WaitCursor);
}
