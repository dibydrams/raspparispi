#include "apiquefaire.h"

ApiQueFaire::ApiQueFaire()
{

}

///
/// \brief ApiQueFaire::API_Call
///
void ApiQueFaire::API_Call()
{
    API_Access = new QNetworkAccessManager(this);

    lat = QString::number(static_cast<double>(WidgetMap::centreLatitude));
    lon = QString::number(static_cast<double>(WidgetMap::centreLongitude));

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=que-faire-a-paris-&sort=-date_start&refine.address_city=Paris&refine.category=Animations&rows=-1&geofilter.distance=" + lat + "," + lon + ",5000");
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
        QJsonValue val2 = objn.value(QString("fields"));
        QJsonObject item = val2.toObject();

        latitude = objn["fields"].toObject()["lat_lon"].toArray()[0].toDouble();
        longitude = objn["fields"].toObject()["lat_lon"].toArray()[1].toDouble();

        GeoObj geo;

        geo.longitude = longitude;
        geo.latitude = latitude;
        geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(182, 66, 244));
        geo.id = ANIMATIONS;

        // Animations Type
        geo.info.insert("Titre", item.value("title").toString());
        geo.info.insert("Adresse", item.value("adresse_street").toString());
        geo.info.insert("Code Postal", item.value("address_zipcode").toString());
        geo.info.insert("Description", item.value("lead_text").toString());
        geo.info.insert("Transport", item.value("transport").toString());
        geo.info.insert("Prix", item.value("price_detail").toString());
        // Handicap
        geo.info.insert("Sourd", item.value("deaf").toString());
        geo.info.insert("Mal voyant", item.value("blind").toString());
        // Start
        geo.info.insert("Date de début", item.value("Date de début").toString());
        geo.info.insert("Date de fin", item.value("Date de fin").toString());

       m_list << geo;
    }

    emit callFinished(m_list, ANIMATIONS);
    reply->deleteLater();
}

///
/// \brief ApiQueFaire::getId
/// \return
///
Abstract_API::API_index ApiQueFaire::getId()
{
    return ANIMATIONS;
}

///
/// \brief ApiQueFaire::getInfo
///
void ApiQueFaire::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

///
/// \brief ApiQueFaire::getPixmap
/// \return QPixmap
///
QPixmap ApiQueFaire::getPixmap()
{
    return QPixmap(":/Icons/iconfireworks.png");
}
