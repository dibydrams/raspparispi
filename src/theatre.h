#ifndef THEATRE_H
#define THEATRE_H
/**
* \author Jean-Sébastien
* \date 6 mai 2019
* \version   1.0
*
* \class theatre
* \brief  Class appelant l'API OpenDataSoft pour fournir les différents théatres produisant des spéctacles dans Paris.
*   Elle dérive de la classe Abstract_API. Et va faire appel à la classe "addrtocoord" pour transformer les adresses
*   en points gps (longitude et latitude).
*/

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantHash>
#include <QJsonObject>
#include "Abstract_API.h"
#include "icon.h"

/**
 * @brief The theatre class
 * @details La classe possède un constructeur simple et 3 slots/fonctions, ainsi qu'un signal
 */
class theatre : public Abstract_API
{
    Q_OBJECT

public:
    theatre();
    API_index getId() override;
    QPixmap getPixmap() override;

public slots:
    void getInfo() override;
    void theatreAPI_Call();
    void readJsonTheatre();

private:
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    QNetworkReply * reply;
    double longitude;
    double latitude;
    QList<GeoObj> m_list;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);

};

#endif // THEATRE_H
