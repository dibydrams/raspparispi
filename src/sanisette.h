#ifndef SANISETTE_H
#define SANISETTE_H

/**
* \author   Jean-Sébastien
* \date     6 mai 2019
* \version  1.0
*
* \class  sanisette
* \brief  Class appelant l'API OpenDataSoft pour fournir les différents sanisettes  dans Paris.
*         Elle dérive de la classe Abstract_API.
*/
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantHash>
#include <QJsonObject>
#include <QMap>
#include "Abstract_API.h"
#include "icon.h"
#include "distance.h"

/**
 * @brief The sanisette class
 * @details Class faisant appel à l'API Data Paris (Open Data Soft)
 * Class dérivant l'Abstract_API
 */
class sanisette : public Abstract_API
{
    Q_OBJECT

public:
    sanisette();
    API_index getId() override;
    QPixmap getPixmap() override;

public slots:
    void sanisetteAPI_Call();
    void readJsonSani();
    void getInfo() override;

private:
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    QNetworkReply * reply;
    double longitude;
    double latitude;
    QList<GeoObj> m_list;
    distance *dist;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);
};

#endif // SANISETTE_H
