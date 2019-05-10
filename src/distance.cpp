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
distance::distance(QObject *parent,QString latitude,QString longitude) : QObject(parent)
{
    sendRequest(latitude,longitude);
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
 * @example 1 :   dist=new distance(qApp,"48.8977","2.3594000000000506","car");
 *  "qApp" nécessairement Parent pour que la QEventLoop fonctionne correctement
 *
 * @example 2 : (ces trois appels peuvent fonctionner à la suite. Il faut faire un objet pour chaque appel)
 *
 *    dist=new distance(qApp,"48.8977","2.3594000000000506","car");
 *    qDebug()<<"*** Distance car compte rendu objet ***";
 *    qDebug()<<"Distance : : "<< dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<< dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<< dist->getDelay();
 *    qDebug()<<"Temps avec traffic : : "<< dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<< dist->getArrival();
 *    dist->~distance();

 *    dist=new distance(qApp,"48.8977","2.3594000000000506","pedestrian");
 *    qDebug()<<"*** Distance piéton compte rendu objet ***";
 *    qDebug()<<"Distance : : "<< dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<< dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<< dist->getDelay(); // sera toujours 0 seconde pour le trajet piéton
 *    qDebug()<<"Temps avec traffic : : "<< dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<< dist->getArrival();
 *    dist->~distance();

 *    dist=new distance(qApp,"48.8977","2.3594000000000506","bus");
 *    qDebug()<<"*** Distance bus compte rendu objet ***";
 *    qDebug()<<"Distance : : "<< dist->getDistanceInMeters();
 *    qDebug()<<"noTrafficTravelTimeInSeconds : : "<< dist->getTimetravel();
 *    qDebug()<<"Retard prévu en seconde : : "<< dist->getDelay();
 *    qDebug()<<"Temps avec traffic : : "<< dist->getTimetravelWithTraffic();
 *    qDebug()<<"arrival :: "<< dist->getArrival();
 *    dist->~distance();
 */
distance::distance(QObject *parent, QString latitude, QString longitude, QString modeDeTransport): QObject(parent)
{
    sendRequest(latitude,longitude,modeDeTransport);
    loop.exec();
}

/**
 * @brief distance::sendRequest
 * @details fonction effectuant l'envoi de la requête via l'API TomTom
 * @param longitude     : type QString
 * @param latitude      : type QString
 */
void distance::sendRequest(QString latitude, QString longitude)
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=NCWallOQKXc5bHkNpL6av4toT58GMwcj&&travelMode=pedestrian&language=fr-FR&computeTravelTimeFor=all");
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
void distance::sendRequest(QString latitude, QString longitude, QString ModeDeTransport)
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://api.tomtom.com/routing/1/calculateRoute/48.8716,2.345990000000029:"+latitude+","+longitude+"/json?key=NCWallOQKXc5bHkNpL6av4toT58GMwcj&&travelMode="+ModeDeTransport+"&language=fr-FR&computeTravelTimeFor=all");
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
        qDebug()<<"erreur : : "<<currentReply->error();
        qDebug()<<"\n";
        //return;
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

/**
 * @brief distance::kilometers_meters
 * @param meters type int
 * @details Fonction statique qui prend une distance en mètre et la formate afin qu'elle soit facilement
 * interprétable par l'utilisateur
 * @return QString de distance formater (avec mètres et/ou kilomètres)
 */
QString distance::kilometers_meters(int meters)
{   QString stringDist;
    int kilometers=meters/1000;
    int meters2=meters%1000;
    if(kilometers>=1){
        stringDist=  QString::number(kilometers)+","+QString::number(meters2)+" km";
    }else {
        stringDist= QString::number(meters)+" m";
    }
    return stringDist;
}

/**
 * @brief distance::time_hours_minutes_seconds
 * @param seconds type int
 * @details Fonction statique qui prend un temps en secondes et le formate
 * afin qu'il soit facilement interprété par l'utilisateur
 * @return QString du temps (avec heures et/ou minutes et/ou secondes)
 */
QString distance::time_hours_minutes_seconds(int seconds)
{
    QString stringTime;
    int hours=seconds/3600;
    int minutes;
    int seconds2;
    if (hours>0){
        int secondsAfterHours=seconds%3600;
        minutes=secondsAfterHours/60;
        seconds2=secondsAfterHours%60;
        if (seconds2>0)
            stringTime= QString::number(hours)+"h "+QString::number(minutes)+"min "+QString::number(seconds2)+"sec";
        else
            stringTime= QString::number(hours)+"h "+QString::number(minutes)+"min";
    }else{
        minutes=seconds/60;
        if (minutes>0){
            seconds2=seconds%60;
            stringTime= QString::number(minutes)+"min "+QString::number(seconds2)+"sec";
        }else{
            stringTime= QString::number(seconds)+"sec";
        }
    }
    return stringTime;
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

distance::~distance(){
    delete networkManager;
}
