#ifndef APIQUEFAIRE_H
#define APIQUEFAIRE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <Abstract_API.h>
#include "icon.h"
#include "widgetmap.h"

class ApiQueFaire : public Abstract_API
{
    Q_OBJECT

public:
    ApiQueFaire();
    API_index getId() override;
    QPixmap getPixmap() override;

private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

private:
    QNetworkAccessManager *API_Access;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj> m_list;

    QString lat;
    QString lon;

    double longitude;
    double latitude;
signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);

};

#endif // APIQUEFAIRE_H
