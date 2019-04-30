#include "addrtocoord.h"

addrToCoord::addrToCoord(QObject *parent,QString addr) : QObject(parent){
    latitude = -1;
    longitude = -1;
    coordinates(addr);
    loop.exec();
}

addrToCoord::~addrToCoord()
{
    delete networkManager;
}

double addrToCoord::getLatitude() const
{
    return latitude;
}

double addrToCoord::getLongitude() const
{
    return longitude;
}

QString addrToCoord::getAddress() const
{
    return address;
}

void addrToCoord::coordinates(QString addr)
{
    address = addr;
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://geocoder.api.here.com/6.2/geocode.json?searchtext="+addr+"&app_id="+appId+"&app_code="+appCode);
    QNetworkRequest request;
    request.setUrl(url);

    currentReply = networkManager->get(request);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getCoordinates(QNetworkReply*)));
}

void addrToCoord::getCoordinates(QNetworkReply *reply)
{
    if (currentReply->error() != QNetworkReply::NoError){
        qDebug()<<"erreur\n";
        return;
    }

    QJsonDocument jsdoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsobj = jsdoc.object();

    latitude = jsobj.toVariantMap()["Response"].toMap()["View"].toList().at(0).toMap()["Result"].
                toList().at(0).toMap()["Location"].toMap()["DisplayPosition"].toMap()["Latitude"].toDouble();
    longitude = jsobj.toVariantMap()["Response"].toMap()["View"].toList().at(0).toMap()["Result"].
                toList().at(0).toMap()["Location"].toMap()["DisplayPosition"].toMap()["Longitude"].toDouble();

     loop.exit();
}
