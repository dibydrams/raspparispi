#include "distance.h"


distance::distance(QObject *parent,QString longitude,QString latitude) : QObject(parent)
{
    getDistance(longitude,latitude);
    loop.exec();
}

distance::distance(QObject *parent, QString latitude, QString longitude, QString modeDeTransport): QObject(parent)
{
    getDistance(longitude,latitude,modeDeTransport);
    loop.exec();
}

void distance::getDistance(QString longitude, QString latitude)
{

    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getDistanceReply(QNetworkReply*)));
}

void distance::getDistance(QString longitude, QString latitude, QString ModeDeTransport)
{

    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode="+ModeDeTransport+"&language=fr-FR&computeTravelTimeFor=all");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getDistanceReply(QNetworkReply*)));
}

void distance::getDistanceReply(QNetworkReply *reply)
{
    if (currentReply->error() != QNetworkReply::NoError){
        qDebug()<<"erreur\n";
        return;
    }

    QByteArray responseBit=reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(responseBit);
    QJsonObject replyObj = document.object();
    QJsonArray routes = replyObj["routes"].toArray();
    foreach (const QJsonValue & value, routes){
        QJsonObject obj = value.toObject();
        QJsonObject summary = obj["summary"].toObject();
        QString arrival = summary["arrivalTime"].toString();

        //***remplisasge des propriété de l'objet***
//        this->setDistanceInMeters(summary["lengthInMeters"].toInt());
//        this->setTimetravel(summary["noTrafficTravelTimeInSeconds"].toInt());
//        this->setTimetravelWithTraffic(summary["liveTrafficIncidentsTravelTimeInSeconds"].toInt());
//        this->setDelay(summary["trafficDelayInSeconds"].toInt());
//        this->setArrival(arrival);

        qDebug()<<"*** Distance compte rendu JSONJSON ***";
        qDebug()<<"Distance : : "<<summary["lengthInMeters"].toInt();
        qDebug()<<"noTrafficTravelTimeInSeconds : : "<<summary["noTrafficTravelTimeInSeconds"].toInt();
        qDebug()<<"Retard prévu en seconde : : "<<summary["trafficDelayInSeconds"].toInt();
        qDebug()<<"arrival :: "<<arrival;
    }
    loop.exit();
}

distance::~distance(){
    delete networkManager;
}










