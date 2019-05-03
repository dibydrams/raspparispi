#ifndef DISTANCE_H
#define DISTANCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QBitArray>
#include <QEventLoop>
#include <QDebug>

class distance : public QObject
{
    Q_OBJECT

public:
    explicit distance (QObject *parent = nullptr);
    explicit distance(QString latitudeDest, QString longitudeDest,  QObject *parent = nullptr);
    explicit distance(QString latitudeDest, QString longitudeDest, QString modeDeTransport, QObject *parent = nullptr);
    explicit distance(double latitudeDest, double longitudeDest, QObject *parent = nullptr);
    explicit distance(double latitudeDest, double longitudeDest,  QString modeDeTransport, QObject *parent = nullptr);
    virtual ~distance();

    QString setRequest(QString latitudeDest, QString longitudeDest);
    QString setRequest(QString latitudeDest, QString longitudeDest, QString modeDeTransport);
    QString setRequest(double latitudeDest, double longitudeDest);
    QString setRequest(double latitudeDest, double longitudeDest, QString modeDeTransport);

    int getDistanceInMeters() const;
    void setDistanceInMeters(int value);

    int getTimetravel() const;
    void setTimetravel(int value);

    int getDelay() const;
    void setDelay(int value);

    int getTimetravelWithTraffic() const;
    void setTimetravelWithTraffic(int value);

    void setR();
    void readJson();
    void readJson(QNetworkReply*replyToRead);

    QString getArrival() const;
    void setArrival(const QString &value);

private:
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    QNetworkReply * reply;
    QHash <QString, QVariant> distance_hash;
    QEventLoop loop;

    int distanceInMeters;
    int timetravel;
    int delay;
    int timetravelWithTraffic;
    QString arrival;

public slots:
    void dataReading();

signals:
    void readed();

};

#endif // DISTANCE_H
