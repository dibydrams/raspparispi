#ifndef DISTANCE_H
#define DISTANCE_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

class distance : public QObject
{

 Q_OBJECT

public:
    distance(QObject *parent, QString latitude,QString Longitude);
    distance(QObject *parent, QString latitude,QString Longitude,QString modeDeTransport);
    distance(QObject *parent);

    void getDistance(QString longitude,QString latitude);
    void getDistance(QString longitude,QString latitude,QString modeDeTransport);
    virtual ~distance();

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
}

;

#endif // DISTANCE_H


