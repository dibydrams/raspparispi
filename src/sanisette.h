#ifndef SANISETTE_H
#define SANISETTE_H

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

class sanisette : public Abstract_API
{
    Q_OBJECT

public:

    sanisette();
    int getId() override;
    QPixmap getPixmap() override;

    void readJsonSaniAPI();

public slots:
    void sanisetteAPI_Call();
    void getInfo() override;

private:
    QNetworkAccessManager * manager;
    QNetworkRequest request;
    QNetworkReply * reply;
    double longitude;
    double latitude;
    QList<GeoObj> m_list;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, API_index);
};

#endif // SANISETTE_H
