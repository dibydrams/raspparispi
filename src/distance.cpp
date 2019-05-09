#include "distance.h"

/*Par défaut les coordonnées de départ sont celles de 6 rue Rougemont à Paris
 *Par défaut le mode de transport est piéton
 */
distance::distance(QObject *parent): QObject(parent)
{

}

distance::~distance(){
    delete manager;
}

distance::distance( QString longitudeDest, QString latitudeDest, QObject *parent): QObject(parent)
{
    manager = new QNetworkAccessManager ();
    request.setUrl(setRequest(longitudeDest,latitudeDest));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()), this,SLOT(dataReading()));
    loop.exec();
}

distance::distance(QString longitudeDest, QString latitudeDest,  QString modeDeTransport, QObject *parent):QObject(parent)
{
    manager = new QNetworkAccessManager ();
    request.setUrl(setRequest(longitudeDest,latitudeDest,modeDeTransport));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()), this,SLOT(dataReading()));
    loop.exec();
}

distance::distance(double longitudeDest, double latitudeDest,  QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager ();
    setR();
    QString rek=setRequest(longitudeDest,latitudeDest);
    connect(reply,SIGNAL(finished()), this,SLOT(dataReading()));
    loop.exec();
}

/*Les différents modes de transport (QString modeDeTransport)
 * pedestrian
 * bicycle
 * motorcycle
 * van
 * bus
 * taxi
 * truck
 */
distance::distance(double longitudeDest, double latitudeDest,  QString modeDeTransport, QObject *parent) :QObject (parent)
{
    manager = new QNetworkAccessManager ();
    request.setUrl(setRequest(longitudeDest,latitudeDest,modeDeTransport));
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()), this,SLOT(dataReading()));
    loop.exec();
}

void distance::setR(){
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:48.75,2.2999999999999545/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all"));
    reply = manager->get(request);
}

QString distance::setRequest(QString longitudeDest, QString latitudeDest)
{
    QString rek="https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+longitudeDest+","+latitudeDest+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all";
    return rek;
}

QString distance::setRequest(QString longitudeDest, QString latitudeDest, QString modeDeTransport)
{
    QString rek="https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+longitudeDest+","+latitudeDest+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode="+modeDeTransport+"&language=fr-FR&computeTravelTimeFor=all";
    return rek;
}

QString distance::setRequest(double longitudeDest, double latitudeDest)
{
    QString strLong = QString("%1").arg(longitudeDest, 0, 'g', 17);
    QString strLat = QString("%1").arg(latitudeDest, 0, 'g', 17);
    QString rek="https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+strLong+","+strLat+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all";
    return rek;
}
QString distance::setRequest(double longitudeDest, double latitudeDest,  QString modeDeTransport)
{
    QString strLong = QString("%1").arg(longitudeDest, 0, 'g', 17);
    QString strLat = QString("%1").arg(latitudeDest, 0, 'g', 17);
    QString rek="https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+strLong+","+strLat +"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode="+modeDeTransport+"&language=fr-FR&computeTravelTimeFor=all";
    return rek;
}

void distance::dataReading()
{
    readJson();
    reply->deleteLater();
    emit readed();
}

void distance::readJson(){
    QByteArray responseBit=reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(responseBit);
    QJsonObject replyObj = document.object();
    QJsonArray routes = replyObj["routes"].toArray();
    foreach (const QJsonValue & value, routes){
        QJsonObject obj = value.toObject();
        QJsonObject summary = obj["summary"].toObject();
        QString arrival = summary["arrivalTime"].toString();

        //***remplisasge des propriété de l'objet***
        this->setDistanceInMeters(summary["lengthInMeters"].toInt());
        this->setTimetravel(summary["noTrafficTravelTimeInSeconds"].toInt());
        this->setTimetravelWithTraffic(summary["liveTrafficIncidentsTravelTimeInSeconds"].toInt());
        this->setDelay(summary["trafficDelayInSeconds"].toInt());
        this->setArrival(arrival);

//        qDebug()<<"*** Distance compte rendu JSONJSON ***";
//        qDebug()<<"Distance : : "<<summary["lengthInMeters"].toInt();
//        qDebug()<<"noTrafficTravelTimeInSeconds : : "<<summary["noTrafficTravelTimeInSeconds"].toInt();
//        qDebug()<<"Retard prévu en seconde : : "<<summary["trafficDelayInSeconds"].toInt();
//        qDebug()<<"arrival :: "<<arrival;
    }

    loop.exit();
}


QString distance::getArrival() const
{
    return arrival;
}

void distance::setArrival(const QString &value)
{
    arrival = value;
}

int distance::getDistanceInMeters() const
{
    return distanceInMeters;
}

void distance::setDistanceInMeters(int value)
{
    distanceInMeters = value;
}

int distance::getTimetravel() const
{
    return timetravel;
}

void distance::setTimetravel(int value)
{
    timetravel = value;
}

int distance::getDelay() const
{
    return delay;
}

void distance::setDelay(int value)
{
    delay = value;
}

int distance::getTimetravelWithTraffic() const
{
    return timetravelWithTraffic;
}

void distance::setTimetravelWithTraffic(int value)
{
    timetravelWithTraffic = value;
}
