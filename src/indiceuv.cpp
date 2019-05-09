#include "indiceuv.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


IndiceUV::IndiceUV()
{

    setRequest();
    connect(manager,&QNetworkAccessManager::finished,this,&IndiceUV::replyFinished);

}


void IndiceUV::replyFinished()
{

    req=reply->readAll();
    i_hash=readJson();
    emit received();

}


QHash <QString, QVariant> IndiceUV::readJson()
{

    /*Récupérer les valeurs de l'indice UV*/
    QJsonDocument d = QJsonDocument::fromJson(req);
    QJsonObject obj = d.object();
    QVariantHash hash;
    hash["UV"]=obj.value("value").toDouble();

    return hash;


}

void IndiceUV::setRequest()
{

    manager = new QNetworkAccessManager(this);
    QUrl url("http://api.openweathermap.org/data/2.5/uvi?appid=5d9a9473c107d2bf83aea4040bfea135&lat=48.86&lon=2.35");
    request.setUrl(url);
    reply = manager->get(request);

}


