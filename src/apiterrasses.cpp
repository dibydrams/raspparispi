#include "apiterrasses.h"
#include <QMetaEnum>
#include <QTextStream>
#include <QDebug>

ApiTerrasses::ApiTerrasses()
{

}

ApiTerrasses::~ApiTerrasses()
{
    delete API_Access;
    delete listTerrasse;
}
void ApiTerrasses::API_Call() // Gestion du call à l'API
{
    API_Access = new QNetworkAccessManager(this);

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=etalages-et-terrasses&rows=-1&facet=libelle_type&facet=red_profession&facet=type_lieu1&facet=type_lieu2&facet=lateralite&facet=longueur&facet=largeurmin&facet=largeurmax&facet=date_periode");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
//rajout debut
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
//rajout fin
}

void ApiTerrasses::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
// rajout debut
//    if(reply->error())
//        {
//            qDebug() << "ERReur de connection!";
//            qDebug() << reply->errorString();
//        }

// rajout fin
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();
    for ( auto val :  arr) {
        terrasse terra;


        QJsonObject objn = val.toObject();
        QJsonValue val2 = objn.value(QString("fields"));
        QJsonObject item = val2.toObject();
        terra.profession = item["red_profession"].toString();
        terra.type = item["libelle_type"].toString();
        terra.adresse = item["lieu1"].toString();
        terra.largeur = item["largeurmin"].toDouble();
        terra.latitude = item["geo_point_2d"].toArray()[0].toDouble();
        terra.longitude = item["geo_point_2d"].toArray()[1].toDouble();
        terra.typeIndice = "F";
        if(terra.type.contains("OUVERTE")) terra.typeIndice = "O";
        

        GeoObj geo;
        if(terra.type.contains("TERRASSE") && terra.largeur > 1)
        {
            if(utilitaire::inMap(terra.latitude, terra.longitude))
            {
                listTerrasse->append(terra);
                geo.latitude = terra.latitude;
                geo.longitude = terra.longitude;

                geo.pixmap = Icon::iconMapOffStr(getPixmap(), terra.typeIndice ,QColor(240, 200, 70));

                m_list << geo;
            }
        }


    }

    emit callFinished(m_list, TERRASSES);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}
//ajout debut
void ApiTerrasses::slotError(QNetworkReply::NetworkError)
{
qDebug()<<"Pas de connection";
}
//ajout fin
// Mon identifiant au sein de l'enumération (classe mère)
Abstract_API::API_index ApiTerrasses::getId()
{
    return TERRASSES;
}

void ApiTerrasses::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
QPixmap ApiTerrasses::getPixmap()
{
    return QPixmap(":/Icons/iconeterrace.png"); // icône PNG préférable
}
