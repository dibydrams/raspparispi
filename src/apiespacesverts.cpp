#include "apiespacesverts.h"
#include <QThread>
#include <QMessageBox>
#include <QNetworkDiskCache>

/*Api traité par Thomas LY*/

ApiEspacesVerts::ApiEspacesVerts()
{
    firstCall();
    loop.exec();
}

ApiEspacesVerts::~ApiEspacesVerts()
{
    delete networkManager;
}

Abstract_API::API_index ApiEspacesVerts::getId()
{
    /*comme indiqué ci-dessus, cf classe : Abstract_API*/
    return ESPACES_VERTS;
}

QPixmap ApiEspacesVerts::getPixmap()
{
    /*récupère l'icône placé en ressources*/
    return QPixmap(":/Icons/iconespacesverts.png");
}

//void ApiEspacesVerts::API_Call()
//{
//    networkManager = new QNetworkAccessManager(this);

//    latCentre = QString::number(WidgetMap::centreLatitude, 'g', 13);
//    lonCentre = QString::number(WidgetMap::centreLongitude, 'g', 13);

//    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=espaces_verts&rows=1000&facet=type_ev&facet=categorie&facet=adresse_codepostal&facet=presence_cloture&facet=ouvert_ferme"+latCentre+"%2C"+lonCentre+"%2C"+rayon);
//    QNetworkRequest request;
//    request.setUrl(url);
//    currentReply = networkManager->get(request);

//    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
//}

void ApiEspacesVerts::API_Results(QNetworkReply *reply)
{
    m_list.clear();
    espverts->clear();

    document = QJsonDocument::fromJson(reply->readAll());

    obj = document.object();
    arr = obj["records"].toArray();
    for(QJsonValue val:arr)
    {
        obj = val.toObject();

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

        geo.info.insert("Nom de la rue/ de l'avenue",jsObj["fields"].toObject()["adresse_libellevoie"].toString());
        geo.info.insert("Nom du lieu",jsObj["fields"].toObject()["nom_ev"].toString());
        geo.info.insert("Arrondissement de Paris",jsObj["fields"].toObject()["adresse_codepostal"].toString());
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
    for(espacesverts p : *espverts)
    {
        gObj.longitude = longit;
        gObj.latitude = lat;
        gObj.pixmap = Icon::iconMapOff(getPixmap(), QColor(126, 170, 44));

        m_list << gObj;
    }
    emit callFinished(m_list, ESPACES_VERTS);
    currentReply->deleteLater();
}

void ApiEspacesVerts::getInfo()
{
//    API_Call();
//    QApplication::setOverrideCursor(Qt::WaitCursor);

    firstCall();
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

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=espaces_verts&rows=1000&facet=type_ev&facet=categorie&facet=adresse_codepostal&facet=presence_cloture&facet=ouvert_ferme"+latCentre+"%2C"+lonCentre+"%2C"+rayon);

    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(API_Results(QNetworkReply*)));
}
