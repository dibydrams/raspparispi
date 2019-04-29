#include "pollution.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

Pollution::Pollution()
{

    setRequest();
    connect(manager,&QNetworkAccessManager::finished,this,&Pollution::replyFinished);

}

void Pollution::setRequest()
{

    manager = new QNetworkAccessManager(this);
    QUrl url("http://api.weatherbit.io/v2.0/current/airquality?lat=48.86&lon=2.35&key=9b80e0427ca94ad39b83354f3f8e2b64");
    request.setUrl(url);
    reply = manager->get(request);

}


void Pollution::replyFinished()
{

    req=reply->readAll();
    p_hash=readJson();
    emit received();

}


QVariantHash Pollution::readJson()
{

    QJsonDocument d = QJsonDocument::fromJson(req);
    QJsonObject obj = d.object();
    QHash <QString, QVariant> hash;


    /*Récupérer les valeurs des polluants (array)*/
    QJsonArray tableauJSON;
    tableauJSON = obj["data"].toArray();

    QJsonObject obj2 = tableauJSON[0].toObject();

    hash["AQI"]=(obj2.value("aqi").toDouble());
    hash["O3"]=(obj2.value("o3").toDouble());
    hash["SO2"]=(obj2.value("so2").toDouble());
    hash["NO2"]=(obj2.value("no2").toDouble());
    hash["PM25"]=(obj2.value("pm25").toDouble());
    hash["PM10"]=(obj2.value("pm10").toDouble());
    hash["CO"]=(obj2.value("co").toDouble());




    return hash;

}


