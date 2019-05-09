#include "pharmapi.h"
#include "icon.h"
#include <QSqlQuery>
//#include <QDebug>

pharmapi::pharmapi()
{

}

void pharmapi::API_Call()
{
    API_Access = new QNetworkAccessManager(this);

    // Accès aux settings de widgetmap.h
//    double conf_longitude  = settingsAccess.m_centreLongitude;
//    double conf_latitude = settingsAccess.m_centreLatitude;
    double conf_longitude = WidgetMap::centreLongitude;
    double conf_latitude = WidgetMap::centreLatitude;

    QString lat = QString::number(conf_latitude);
        QString lon = QString::number(conf_longitude);
        QString rayon = "1000";
        QUrl url("https://data.iledefrance.fr/api/records/1.0/search/?dataset=carte-des-pharmacies-dile-de-france&rows=500&facet=libdepartement&facet=commune&refine.libdepartement=PARIS&geofilter.distance="+lat+"%2C"+lon+"%2C"+rayon);
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

void pharmapi::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();

    for (auto val : arr)
    {
        QJsonObject objn = val.toObject();
        longitude = objn["geometry"].toObject()["coordinates"].toArray()[0].toDouble();
        latitude = objn["geometry"].toObject()["coordinates"].toArray()[1].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(0, 153, 0));
        geo.id = getId();

        /*Ce sont les informations que je souhaite récupéré du JSON, pour l'API espaces verts.
         *Comme une "QMap <QString,QString> info" à été ajouté dans la classe Abstract_API.h,
         *celà nous permet de sélectionner les infos que nous souhaitons afficher, lors du clic.*/

        geo.info.insert("nom",objn["fields"].toObject()["rs"].toString());
        geo.info.insert("telephone",objn["fields"].toObject()["telephone"].toVariant().toString());

       m_list << geo;
    }

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("/home/dibydrams/pharmloc.db");
//    db.open();

//    if(db.open())
//    {
//        qDebug() << "Vous êtes maintenant connecté à la base de donnée pharmloc.";
//        QSqlQuery query;
//        if(query.exec("SELECT * FROM pharmloc"))
//        {
//            while(query.next())
//            {
//                qDebug() << "Ajout d'une nouvelle pharmacie";
//                // Récupère les valeurs dans des variables.
//                latitude = query.value(1).toDouble();
//                longitude = query.value(2).toDouble();
//                qDebug() << "Pharmlat : " << latitude;
//                qDebug() << "Pharmlong : "<< longitude;

//                GeoObj geo;

//                geo.longitude = longitude;
//                geo.latitude = latitude;
//                geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(252, 181, 75));

//                m_list << geo;
//            }
//            qDebug() << "Fin des requêtes.";
//        }
//    }
//    db.close();

    emit callFinished(m_list, PHARMACIES);  // Signal de fin de traitement de l'API
//    qDebug()<<"emit"<<PHARMACIES;
    reply->deleteLater();
}

// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index pharmapi::getId()
{
    return PHARMACIES;
}

void pharmapi::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap pharmapi::getPixmap()
{
    return QPixmap(":/Icons/pharmicon.png"); // icône PNG préférable
}
