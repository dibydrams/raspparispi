#ifndef PHARMAPI_H
#define PHARMAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

#include "Abstract_API.h"


class pharmapi : public Abstract_API
{
    Q_OBJECT

public:
    pharmapi();
    int getId() override;
    QPixmap getPixmap() override;

public slots:
    void getInfo() override;

private:
    QNetworkAccessManager *API_Access;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj> m_list;

    double longitude;
    double latitude;
  signals:
    void callFinished(QList<Abstract_API::GeoObj>, API_index);

};

#endif // PHARMAPI_H
