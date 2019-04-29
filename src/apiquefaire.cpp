#include "apiquefaire.h"

ApiQueFaire::ApiQueFaire()
{

}

///
/// \brief ApiQueFaire::API_Call
///
void ApiQueFaire::API_Call() // Gestion du call à l'API
{
    API_Access = new QNetworkAccessManager(this);

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=que-faire-a-paris-&sort=-date_start&refine.address_city=Paris&refine.category=Animations&rows=20&geofilter.distance=48.8716,2.34599,2000");
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

///
/// \brief ApiQueFaire::API_Results
/// \param reply
///
void ApiQueFaire::API_Results(QNetworkReply *reply)
{
    m_list.clear();

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();

    for ( auto val :  arr) {

        QJsonObject objn = val.toObject();

        latitude = objn["fields"].toObject()["lat_lon"].toArray()[0].toDouble();
        longitude = objn["fields"].toObject()["lat_lon"].toArray()[1].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = QPixmap();
        geo.id = getId();

       m_list << geo;
    }

    emit callFinished(m_list);
    reply->deleteLater();
}

///
/// \brief ApiQueFaire::getId
/// \return
///
int ApiQueFaire::getId()
{
    return ANIMATIONS;
}

///
/// \brief ApiQueFaire::getInfo
///
void ApiQueFaire::getInfo()
{
    API_Call();
}

///
/// \brief ApiQueFaire::getPixmap
/// \return QPixmap
///
QPixmap ApiQueFaire::getPixmap()
{
    return QPixmap(":/Icons/icongroup.png"); // icône PNG préférable
}
