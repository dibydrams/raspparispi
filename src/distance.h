#ifndef DISTANCE_H
#define DISTANCE_H

/**
* \author Jean-Sébastien
* \date 6 mai 2019
* \version   1.0
*
* \class distance
* \brief  Class appelant l'API tomtom pour fournir la distance entre deux points géographiques
* ainsi que d'autre informations complémentaires relatives aux trajets
* \details Cette class a un constructeur surchargé permettant de faire appelle à l'API
* avec des coordonnées de type string ou double.
* Un QEventLoop est utilisé afin de rendre la requête et son retour synchrone
* (ce qui permettra d'envoyer de multiples requêtes d'affilé ou d'émettre des requêtes dans une boucle)
* Dans cette 1er version le point de départ sera toujours 6 rue Rougemont.
* Un exemple complet d'utilisation de cette classe se trouve en commentaire dans sanisette.cpp->sanisette::readJsonSani()
*/

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

/**
 * @brief The distance class
 * @details La classe contient les propriétés suivantes:
 * distanceInMeters (int)       : distance en mètres
 * timetravel (int)             : temps de trajet en secondes
 * delay (int)                  : retard en secondes
 * timetravelWithTraffic (int)  : temps de trajet en tenant compte du traffic, en secondes
 * arrival (Qstring)            : heure d'arrivée Qstring format DateTime
 *
 * La classe possède aussi un SLOT getDistanceReply(), qui sera appellée
 * à la reception du SIGNAL finished() d'un reply
 *
 */
class distance : public QObject
{

 Q_OBJECT

public:
    distance(QObject *parent);
    distance(QObject *parent, QString latitude,QString Longitude);
    distance(QObject *parent, QString latitude,QString Longitude,QString modeDeTransport);

    void sendRequest(QString longitude,QString latitude);
    void sendRequest(QString longitude,QString latitude,QString modeDeTransport);
    virtual ~distance();

    int getDistanceInMeters() const;
    void setDistanceInMeters(int value);

    int getTimetravel() const;
    void setTimetravel(int value);

    int getDelay() const;
    void setDelay(int value);

    int getTimetravelWithTraffic() const;
    void setTimetravelWithTraffic(int value);

    QString getArrival() const;
    void setArrival(const QString &value);

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QEventLoop loop;

    int distanceInMeters;
    int timetravel;
    int delay;
    int timetravelWithTraffic;
    QString arrival;

private slots:
    void getDistanceReply(QNetworkReply* reply);
};

#endif // DISTANCE_H


