#include "distance.h"

/**
 * @brief distance::distance (constructor)
 * @param parent -> pointer sur QObject
 * @details constructeur simple et vide qui ne fera pas appel à l'API de lui même
 * Il faudra donc après optention de l'objet, lui demander d'effectuer une requête avec la fonction "sendRequest()"
 * Il faut utiliser "qApp" comme Parent pour que la QEventLoop fonctionne correctement
 */
distance::distance(QObject *parent) : QObject(parent)
{

}

/**
 * @brief distance::distance (constructor)
 * @details surcharge du constructeur permettant de renseigner longitude et latitude de destination;
 * va envoyer la requête immédiatement
 * @param parent        :  type pointer sur QObject ou descendant
 * @param longitude     :  type QString
 * @param latitude      :  type QString
 * Il faut utiliser "qApp" comme Parent pour que la QEventLoop fonctionne correctement
 */
distance::distance(QObject *parent,QString longitude,QString latitude) : QObject(parent)
{
    sendRequest(longitude,latitude);
    loop.exec();
}

/**
 * @brief distance::distance
 * @details surcharge du constructeur permettant de renseigner longitude et latitude de destination,
 * ainsi que le mode de transport
 * @param parent
 * @param latitude          : type QString
 * @param longitude         : type QString
 * @param modeDeTransport   : type QString
 * @example :   dist=new distance(qApp,"48.8977","2.3594000000000506","car");
 * Il faut utiliser "qApp" comme Parent pour que la QEventLoop fonctionne correctement
 *
 *  @example (ces trois appels peuvent fonctionner à la suite; et il faut faire un objet pour chaque appel)
 *
 *    dist=new distance(qApp,"48.8977","2.3594000000000506","car");
 *    qDebug()<<"*** Distance car compte rendu objet ***";
 *    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
 *    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<<dist->getArrival();
 *    dist->~distance();

 *    dist=new distance(qApp,"48.8977","2.3594000000000506","pedestrian");
 *    qDebug()<<"*** Distance pedestrian compte rendu objet ***";
 *    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
 *    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<<dist->getArrival();
 *    dist->~distance();

 *    dist=new distance(qApp,"48.8977","2.3594000000000506","bicycle");
 *    qDebug()<<"*** Distance bicycle compte rendu objet ***";
 *    qDebug()<<"Distance : : "<<dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<<dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<<dist->getDelay();
 *    qDebug()<<"Temps avec traffic : : "<<dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<<dist->getArrival();
 *    dist->~distance();
 */
distance::distance(QObject *parent, QString latitude, QString longitude, QString modeDeTransport): QObject(parent)
{
    sendRequest(longitude,latitude,modeDeTransport);
    loop.exec();
}

/**
 * @brief distance::sendRequest
 * @details fonction effectuant l'envoi de la requête via l'API TomTom
 * @param longitude     : type QString
 * @param latitude      : type QString
 */
void distance::sendRequest(QString longitude, QString latitude)
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getDistanceReply(QNetworkReply*)));
}

/**
 * @brief distance::sendRequest
 * @details surcharge de la fonction sendRequest permettant de renseigner en plus le mode de transport
 * @param longitude     : type QString
 * @param latitude      : type QString
 * @param ModeDeTransport   : type QString
 */
void distance::sendRequest(QString longitude, QString latitude, QString ModeDeTransport)
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=OeKOW9A0nmsjwQfqeo201YbNUKfQ50IA&&travelMode="+ModeDeTransport+"&language=fr-FR&computeTravelTimeFor=all");
    QNetworkRequest request;
    request.setUrl(url);
    currentReply = networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getDistanceReply(QNetworkReply*)));
}

/**
 * @brief distance::getDistanceReply
 * @details fonction/slot qui récupère la réponse de la requête émise précédemment (fonction senRequest)
 * Et qui va lire cette dernière et remplir l'objet distance avec les données correspiondants.
 * @param reply     : pointer sur un  QNetworkReply
 */
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
          this->setDistanceInMeters(summary["lengthInMeters"].toInt());
          this->setTimetravel(summary["noTrafficTravelTimeInSeconds"].toInt());
          this->setTimetravelWithTraffic(summary["liveTrafficIncidentsTravelTimeInSeconds"].toInt());
          this->setDelay(summary["trafficDelayInSeconds"].toInt());
          this->setArrival(arrival);
    }
    loop.exit();
}

distance::~distance(){
    delete networkManager;
}

int distance::getTimetravel() const
{
    return timetravel;
}

void distance::setTimetravel(int value)
{
    timetravel = value;
}

int distance::getDistanceInMeters() const
{
    return distanceInMeters;
}

void distance::setDistanceInMeters(int value)
{
    distanceInMeters = value;
}

int distance::getDelay() const
{
    return delay;
}

void distance::setDelay(int value)
{
    delay = value;
}

QString distance::getArrival() const
{
    return arrival;
}

void distance::setArrival(const QString &value)
{
    arrival = value;
}

int distance::getTimetravelWithTraffic() const
{
    return timetravelWithTraffic;
}

void distance::setTimetravelWithTraffic(int value)
{
    timetravelWithTraffic = value;
}










