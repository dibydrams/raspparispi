#ifndef DIST1_H
#define DIST1_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

class dist1 : public QObject
{

 Q_OBJECT

public:
    dist1(QObject *parent, QString latitude,QString Longitude);
    dist1(QObject *parent, QString latitude,QString Longitude,QString modeDeTransport);
    dist1(QObject *parent);

    void distance(QString longitude,QString latitude);
    void distance(QString longitude,QString latitude,QString modeDeTransport);
    virtual ~dist1();

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

    void getDistance(QNetworkReply* reply);
}

;

#endif // DIST1_H


