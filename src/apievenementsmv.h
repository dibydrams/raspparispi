#ifndef APIEVENEMENTSMV_H
#define APIEVENEMENTSMV_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

#include "Abstract_API.h"


class ApiEvenementsMV : public Abstract_API
{
    Q_OBJECT

public:
    ApiEvenementsMV();
    int getId() override;
    QPixmap getPixmap() override;

private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);
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

#endif // APIEVENEMENTSMV_H
