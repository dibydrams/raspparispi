#ifndef COORDTOADDR_H
#define COORDTOADDR_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>

class coordToAddr : public QObject
{
    Q_OBJECT
public:
    coordToAddr(QObject *parent, double lat, double lon);
    virtual ~coordToAddr();
    void address(double lat, double lon);

    QString getStreet() const;

    int getPostalCode() const;

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QString street;
    int postalCode;
    QString appId = QString("jqvsYZofXOPjZ43oNgwv");
    QString appCode = QString("1ksmFUNCmrPeWNXknNFhtw");
    QString latitude;
    QString longitude;
    QEventLoop loop;

private slots:
    void getAddress(QNetworkReply* reply);
};

#endif // COORDTOADDR_H
