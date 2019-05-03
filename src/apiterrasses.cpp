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
}

void ApiTerrasses::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
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
        QString typeIndice = "F";
        if(terra.type.contains("OUVERTE")) typeIndice = "O";
        

        GeoObj geo;
        if(terra.type.contains("TERRASSE") && terra.largeur > 1)
        {
            if(utilitaire::inMap(terra.latitude, terra.longitude))
            {
                listTerrasse->append(terra);
                geo.latitude = terra.latitude;
                geo.longitude = terra.longitude;

                geo.pixmap = Icon::iconMapOffStr(getPixmap(), typeIndice ,QColor(240, 200, 70));

                m_list << geo;
            }
        }


    }

    emit callFinished(m_list, TERRASSES);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}

// Mon identifiant au sein de l'enumération (classe mère)
int ApiTerrasses::getId()
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
