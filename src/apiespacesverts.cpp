#include "apiespacesverts.h"
#include <QThread>

ApiEspacesVerts::ApiEspacesVerts()
{
    firstCall();
    loop.exec();
}

Abstract_API::API_index ApiEspacesVerts::getId()
{
    return ESPACES_VERTS;
}

QPixmap ApiEspacesVerts::getPixmap()
{
    return QPixmap(":/Icons/iconespacesverts.png");
}

//void ApiEspacesVerts::API_Call()
//{
//    manApiEspacesVerts = new QNetworkAccessManager(this);
//    connect(manApiEspacesVerts, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
//    manApiEspacesVerts->get(QNetworkRequest(QUrl("https://opendata.paris.fr/api/records/1.0/search/?dataset=espaces_verts&rows=-1&sort=-nsq_espace_vert&facet=type_ev&facet=id_division&facet=adresse_codepostal&facet=ouvert_ferme&facet=id_atelier_horticole&facet=competence&facet=categorie&facet=presence_cloture&facet=proprietaire&facet=gestionnnaire")));
//}

void ApiEspacesVerts::API_Results(QNetworkReply *reply)
{
    m_list.clear();
    espverts->clear();

    document = QJsonDocument::fromJson(reply->readAll());
    jsonObject = document.object();
    jsonArray = jsonObject["records"].toArray();
    for(QJsonValue val:jsonArray){
        jsObj = val.toObject();

        geoloc = jsObj["fields"].toObject()["geom_x_y"].toArray();
        double lat = geoloc[0].toDouble();
        double longit = geoloc[1].toDouble();

        GeoObj geo;

        geo.longitude = longit;
        geo.latitude = lat;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(126, 170, 44));

        /*Ce sont les informations que je souhaite récupéré du JSON, pour l'API espaces verts.
         *Comme une "QMap <QString,QString> info" à été ajouté dans la classe Abstract_API.h,
         *celà nous permet de sélectionner les infos que nous souhaitons afficher, lors du clic.*/

        //geo.info.insert("Type de voie",jsObj["fields"].toObject()["adresse_typevoie"].toString());
        geo.info.insert("Nom de la rue/ de l'avenue",jsObj["fields"].toObject()["adresse_libellevoie"].toString());
        geo.info.insert("Nom du lieu",jsObj["fields"].toObject()["nom_ev"].toString());
        geo.info.insert("Code postal",jsObj["fields"].toObject()["adresse_codepostal"].toString());
        geo.info.insert("Catégorie",jsObj["fields"].toObject()["categorie"].toString());
        geo.info.insert("Presence de clôture",jsObj["fields"].toObject()["presence_cloture"].toString());
        geo.info.insert("Ouvert ou ferme",jsObj["fields"].toObject()["ouvert_ferme"].toString());

        m_list << geo;
    }
    loop.exit();
    //    emit callFinished(m_list, ESPACES_VERTS);
    //    reply->deleteLater();
}

void ApiEspacesVerts::copieGeoObj()
{
    GeoObj gObj;
    for(espacesverts p : *espverts){
        GeoObj geo;

        geo.longitude = longit;
        geo.latitude = lat;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(126, 170, 44));

        m_list << geo;
    }
    emit callFinished(m_list, ESPACES_VERTS);
    currentReply->deleteLater();
}

void ApiEspacesVerts::getInfo()
{
    //API_Call();
    networkManager = new QNetworkAccessManager(this);
    QUrl url("");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(copieGeoObj()));
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

void ApiEspacesVerts::firstCall()
{
    networkManager = new QNetworkAccessManager(this);
    latCentre = QString::number(WidgetMap::centreLatitude, 'g', 13);
    lonCentre = QString::number(WidgetMap::centreLongitude, 'g', 13);
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=espaces_verts&rows=-1&facet=type_ev&facet=id_division&facet=adresse_codepostal&facet=ouvert_ferme&facet=id_atelier_horticole&facet=competence&facet=categorie&facet=presence_cloture&facet=proprietaire&facet=gestionnnaire&geofilter.distance="+latCentre+"%2C"+lonCentre+"%2C"+rayon);
    //qDebug() << url;
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
}
