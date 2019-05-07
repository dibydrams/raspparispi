#include "apiterrasses.h"
#include <QMetaEnum>
#include <QTextStream>
#include <QDebug>
#include "dialogconnexion.h"
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QMessageBox>


ApiTerrasses::ApiTerrasses()
{

}

ApiTerrasses::~ApiTerrasses()
{
    delete API_Access;
    delete listTerrasse;
}
/// Gestion du call à l'API
/// \brief ApiTerrasses::API_Call
/// Gestion du call à l'API
void ApiTerrasses::API_Call() // Gestion du call à l'API
{
    API_Access = new QNetworkAccessManager(this);
    //cache bedut
    QNetworkDiskCache *cache = new QNetworkDiskCache(API_Access);
    cache->setCacheDirectory("/home/hedi/projet_raspparispi/raspparispi/cache");
    //cache->setCacheDirectory(QDesktopServices::storageLocation(QDesktopServices::CacheLocation));
    API_Access->setCache(cache);
    //cache fin
    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=etalages-et-terrasses&rows=-1&facet=libelle_type&facet=red_profession&facet=type_lieu1&facet=type_lieu2&facet=lateralite&facet=longueur&facet=largeurmin&facet=largeurmax&facet=date_periode");

    QNetworkRequest request;
    request.setUrl(url);
    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
    //cache debut
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    //cache fin
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));

}
/// Gestion des résultats au format JSON
/// \brief ApiTerrasses::API_Results
/// \param reply
///
void ApiTerrasses::API_Results(QNetworkReply *reply) // Gestion des résultats au format JSON
{
    qDebug() << reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool();
    m_list.clear(); // Reset de la liste de GeoObj à chaque passage dans la fonction
    if (currentReply->error() != QNetworkReply::NoError){
        qDebug()<<"Erreur !! \n";
        return;
    }
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
        terra.longueur = item["longueur"].toDouble();
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
                geo.id = getId();

                geo.info.insert("profession",terra.profession);
                geo.info.insert("type",terra.type);
                geo.info.insert("adresse", terra.adresse);
                geo.info.insert("surface",QString::number(terra.longueur * terra.largeur));

                m_list << geo;
            }
        }


    }

    emit callFinished(m_list, TERRASSES);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}
//ajout debut
/// Vérification de la connexion
/// \brief ApiTerrasses::slotError
///
void ApiTerrasses::slotError(QNetworkReply::NetworkError)
{
    qDebug()<<"Pas de connection";
    //DialogConnexion::afficherConnexion();
    QMessageBox msgBox;
    msgBox.setText("Veuillez verifier la connexion");
    msgBox.exec();

}
//ajout fin
// Mon identifiant au sein de l'enumération (classe mère)
///
/// \brief ApiTerrasses::getId
/// \return
///
Abstract_API::API_index ApiTerrasses::getId()
{
    return TERRASSES;
}
///
/// \brief ApiTerrasses::getInfo
///
void ApiTerrasses::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

// Envoi de l'icône de mon bouton (utilisation des resources - pas de PATH en dur)
///
/// \brief ApiTerrasses::getPixmap
/// \return
///
QPixmap ApiTerrasses::getPixmap()
{
    return QPixmap(":/Icons/iconeterrace.png"); // icône PNG préférable
}
