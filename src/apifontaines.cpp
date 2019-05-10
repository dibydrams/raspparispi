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
 /// Affichage de l'icone fontaines
QPixmap apifontaines::getPixmap()
{
     return QPixmap(":/Icons/iconefontaines.png");  // a rajouter dans Resources:
}
 /// Fonction qui recupere les données des fontaines
void apifontaines::API_call()
{
    //Acces reseaux internet
    API_access=new QNetworkAccessManager(this);

    //Acces aux setting de WidgetMap.h
    latCentre = QString::number(WidgetMap::centreLatitude, 'g', 13);
    lonCentre = QString::number(WidgetMap::centreLongitude, 'g', 13);

    QString rayon = "1000";
    qDebug() << "latCentre: " << latCentre;
    //Requette sur l'opendataparis avec l'adresse et le rayon de recherche , geofilter.distance dans l'API
    currentReply=API_access->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=fontaines-a-boire&facet=arro&facet=modele&rows=-1&facet=a_boire&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon)));
    connect(API_access, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_results(QNetworkReply*)));


}
/// Traitement des données recupéré avec la requette, en format json
void apifontaines::API_results(QNetworkReply *reply)
{
    m_list.clear();//<reset de la liste GeoObj
    doc=QJsonDocument::fromJson(reply->readAll());
    obj=doc.object();
    arr=obj["records"].toArray(); //< Conversion du document json "records" en tableau
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
        lon=QString::number(longitude, 'g', 13);
        lat=QString::number(latitude, 'g', 13);
        //dist=new distance(qApp,lat,lon);


        GeoObj geo;
        geo.latitude=latitude;
        geo.longitude=longitude;
        if (statut=="P") geo.pixmap=Icon::iconMapOffStr(getPixmap(), statut, Qt::darkCyan);
        else geo.pixmap=Icon::iconMapOffClose(getPixmap(), Qt::darkCyan);

        /*Ce sont les informations que je souhaite récupéré du JSON, pour l'API fontaines.
         *Comme une "QMap <QString,QString> info" à été ajouté dans la classe Abstract_API.h,
         *celà nous permet de sélectionner les infos que nous souhaitons afficher, lors du clic.*/

        geo.info.insert("adresse",adresse);
        geo.info.insert("modele",modele);
        geo.info.insert("en_service",en_service);
        geo.info.insert("ouverture hiver", ouv_hiver);
        geo.info.insert("sdf",sdf);
        //geo.info.insert("distance",(QString)dist->getDistanceInMeters());
        // qDebug<<"distance"<<(QString)dist->getDistanceInMeters();


        m_list<<geo;
    }
    emit callFinished(m_list, FONTAINES);//<signal de fin de traitement de l'API
    reply->deleteLater();

}
/// la premiere fonction appellé par la fenêtre principale
void apifontaines::getInfo()
{
    API_call();
    QApplication::setOverrideCursor(Qt::WaitCursor);

}
