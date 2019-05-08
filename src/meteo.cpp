#include "meteo.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantHash>




meteo::meteo()
{

    setRequest();
    connect(manager,&QNetworkAccessManager::finished,this,&meteo::replyFinished);

}


QVariantHash meteo::readJson()
{


    QHash <QString, QVariant> hash;

    /*Récupérer les valeurs de coord (lat el lon)*/

    QJsonDocument d = QJsonDocument::fromJson(req);
    QJsonObject obj = d.object();
    QJsonValue val = obj.value(QString("coord"));
    QJsonObject item = val.toObject();
    hash["Latitude"]=(item.value("lat").toDouble());
    hash["Longitude"] = item.value("lon").toDouble();

    /*Récupérer les valeurs de main (températures, humidité...)*/

    QJsonValue val1 = obj.value(QString("main"));
    QJsonObject item1 = val1.toObject();

    hash["temp"] = item1.value("temp").toDouble();
    hash["3"] = item1.value("humidity").toDouble();
    hash["6"] = item1.value("pressure").toDouble();
    hash["1"] = item1.value("temp_min").toDouble();
    hash["0"] = item1.value("temp_max").toDouble();


    /*Récupérer les valeurs de wind (vitesse et direction du vent)*/
    QJsonValue val2 = obj.value(QString("wind"));
    QJsonObject item2 = val2.toObject();
    hash["4"] = item2.value("speed").toDouble();
    hash["5"] = item2.value("deg").toDouble();

    /*Récupérer les valeurs sys*/
    QJsonValue val3 = obj.value(QString("sys"));
    QJsonObject item3 = val3.toObject();
    hash["Levé"] = item3.value("sunrise").toDouble();
    hash["Couché"] = item3.value("sunset").toDouble();

    /*Récupérer les valeurs de weather (array)*/
    QJsonArray tableauJSON;
    tableauJSON = obj["weather"].toArray();

    QJsonObject obj2 = tableauJSON[0].toObject();
    hash["main"] = obj2.value("main").toString();
    hash["2"] = obj2.value("description").toString();
    hash["icon"] = obj2.value("icon").toString();


    return hash;


}

void meteo::setRequest()
{

    manager = new QNetworkAccessManager(this);
    QUrl url("http://api.openweathermap.org/data/2.5/weather?q=Paris&APPID=5d9a9473c107d2bf83aea4040bfea135&units=metric&lang=fr");
    request.setUrl(url);
    reply = manager->get(request);

}


void meteo::replyFinished()
{
    req=reply->readAll();
    m_hash=readJson();
    emit received();

}




