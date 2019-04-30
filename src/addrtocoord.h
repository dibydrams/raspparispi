#ifndef ADDRTOCOORD_H
#define ADDRTOCOORD_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QJsonArray>
#include <QEventLoop>

/**
 * @brief The addrToCoord class
 */
class addrToCoord : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief constructor
     * @param parent
     * @param addr: the address whose coordinates will be calculated
     */
    addrToCoord(QObject *parent, QString addr);
    virtual ~addrToCoord();

    /**
     * @brief getLatitude
     * @return the latitude of the address
     */
    double getLatitude() const;

    /**
     * @brief getLongitude
     * @return the longitude of the address
     */
    double getLongitude() const;

    /**
     * @brief getAddress
     * @return the address
     */
    QString getAddress() const;

    /**
     * @brief coordinates
     * @param addr
     */
    void coordinates(QString addr);

private:
    QNetworkReply* currentReply;
    QNetworkAccessManager *networkManager;
    QString address;
    QString appId = QString("jqvsYZofXOPjZ43oNgwv");
    QString appCode = QString("1ksmFUNCmrPeWNXknNFhtw");
    double latitude;
    double longitude;
    QEventLoop loop;

private slots:
    /**
     * @brief getCoordinates: function that calculates the coordinates of an address
     * @param reply
     */
    void getCoordinates(QNetworkReply* reply);
};

#endif // ADDRTOCOORD_H
