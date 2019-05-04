#include "apibornes_elec.h"

ApiBornes_Elec::ApiBornes_Elec()
{

}

///
/// \brief ApiBornes_Elec::API_Call
///
void ApiBornes_Elec::API_Call()
{
   API_Access = new QNetworkAccessManager(this);

    QUrl url("https://opendata.paris.fr/api/records/1.0/search/?dataset=bornes-de-recharge-pour-vehicules-electriques&rows=-1&geofilter.distance=48.8716,2.34599,4000");
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = API_Access->get(request);
    connect(API_Access, SIGNAL(finished(QNetworkReply *)), this, SLOT(API_Results(QNetworkReply *)));
}

///
/// \brief ApiBornes_Elec::API_Results
/// \param reply
///
void ApiBornes_Elec::API_Results(QNetworkReply *reply)
{
    m_list.clear();

    doc = QJsonDocument::fromJson(reply->readAll());
    obj = doc.object();
    arr = obj["records"].toArray();

    for ( auto val :  arr) {

        QJsonObject objn = val.toObject();
        QJsonValue val2 = objn.value(QString("fields"));
        QJsonObject item = val2.toObject();

        longitude = item.value("longitude").toDouble();
        latitude = item.value("latitude").toDouble();

        if(isGeoBool(latitude) && isGeoBool(longitude))
        {
            GeoObj geo;

            geo.longitude = longitude;
            geo.latitude = latitude;

            geo.pixmap = Icon::iconMapOff(getPixmap(), QColor(51, 153, 255));

           m_list << geo;
        }
    }

    emit callFinished(m_list, BORNES_ELEC);  // Signal de fin de traitement de l'API
    reply->deleteLater();
}

///
/// \brief ApiBornes_Elec::getId
/// \return enum number API
///
Abstract_API::API_index ApiBornes_Elec::getId()
{
    return BORNES_ELEC;
}

///
/// \brief ApiBornes_Elec::getInfo
///
void ApiBornes_Elec::getInfo()
{
    API_Call();
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

///
/// \brief ApiBornes_Elec::getPixmap
/// \return QPixmap resources img
///
QPixmap ApiBornes_Elec::getPixmap()
{
    return QPixmap(":/Icons/iconelectric-car.png");
}

///
/// Check if geo exist
/// \brief ApiBornes_Elec::getBool
/// \param geo
/// \return bool
///
bool ApiBornes_Elec::isGeoBool(double geo)
{
    return (!static_cast<bool>(geo)) ? false : true;
}

