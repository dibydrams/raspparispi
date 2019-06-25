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
    //API weatherbit
    /*manager = new QNetworkAccessManager(this);
    QUrl url("http://api.weatherbit.io/v2.0/current/airquality?lat=48.86&lon=2.35&key=9b80e0427ca94ad39b83354f3f8e2b64");
    request.setUrl(url);
    reply = manager->get(request);*/

    //API waqi
    manager = new QNetworkAccessManager(this);
    QUrl url("https://api.waqi.info/feed/paris/?token=a74334edb92ad4b8ba053a6fa13c2c7ca7fb6f8d");
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


    /*Récupérer les valeurs des polluants (array) WEATHERBIT*/
    /*QJsonArray tableauJSON;
    tableauJSON = obj["data"].toArray();

    QJsonObject obj2 = tableauJSON[0].toObject();

    hash["AQI"]=(obj2.value("aqi").toDouble());
    hash["O3"]=(obj2.value("o3").toDouble());
    hash["SO2"]=(obj2.value("so2").toDouble());
    hash["NO2"]=(obj2.value("no2").toDouble());
    hash["PM25"]=(obj2.value("pm25").toDouble());
    hash["PM10"]=(obj2.value("pm10").toDouble());
    hash["CO"]=(obj2.value("co").toDouble());*/

    /*Récupérer les valeurs des polluants WAQI*/

      QJsonObject obj2 = obj["data"].toObject();
      hash["AQI"]=(obj2.value("aqi").toDouble());

      QJsonObject obj3 = obj2["iaqi"].toObject();

      QJsonObject obj4 = obj3["o3"].toObject();
      hash["O3"]=(obj4.value("v").toDouble());

      QJsonObject obj5 = obj3["so2"].toObject();
      hash["SO2"]=(obj5.value("v").toDouble());

      QJsonObject obj6 = obj3["no2"].toObject();
      hash["NO2"]=(obj6.value("v").toDouble());

      QJsonObject obj7 = obj3["pm25"].toObject();
      hash["PM25"]=(obj7.value("v").toDouble());

      QJsonObject obj8 = obj3["pm10"].toObject();
      hash["PM10"]=(obj8.value("v").toDouble());

      QJsonObject obj9 = obj3["co"].toObject();
      hash["CO"]=(obj9.value("v").toDouble());


    qDebug() << hash;

    return hash;

}


