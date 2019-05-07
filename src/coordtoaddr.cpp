#include "coordtoaddr.h"

coordToAddr::coordToAddr(QObject *parent, double lat, double lon): QObject(parent)
{
    address(lat, lon);
    loop.exec();
}

coordToAddr::~coordToAddr()
{
    delete networkManager;
}

void coordToAddr::address(double lat, double lon)
{
    latitude = QString::number(lat, 'g', 13);
    longitude = QString::number(lon, 'g', 13);

    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://reverse.geocoder.api.here.com/6.2/reversegeocode.json?prox="+latitude+"%2C"+longitude+"%2C50&mode=retrieveAddresses&maxresults=1&gen=9&app_id="+appId+"&app_code="+appCode);

    QNetworkRequest request;
    request.setUrl(url);

    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAddress(QNetworkReply*)));
}

QString coordToAddr::getStreet() const
{
    return street;
}

int coordToAddr::getPostalCode() const
{
    return postalCode;
}

void coordToAddr::getAddress(QNetworkReply *reply)
{
    if (currentReply->error() != QNetworkReply::NoError){
        //qDebug()<<"erreur\n";
        return;
    }

    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();

    street = jsobj.toVariantMap()["Response"].toMap()["View"].toList().at(0).toMap()["Result"].toList().at(0).toMap()["Location"].toMap()["Address"].toMap()["Street"].toString();
    postalCode = jsobj.toVariantMap()["Response"].toMap()["View"].toList().at(0).toMap()["Result"].toList().at(0).toMap()["Location"].toMap()["Address"].toMap()["PostalCode"].toInt();
    loop.exit();
}
