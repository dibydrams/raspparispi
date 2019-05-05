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
#include "widgetmap.h"


class ApiEvenementsMV : public Abstract_API
{
    Q_OBJECT

public:
    ApiEvenementsMV();
    int getId() override;
    QPixmap getPixmap() override;
    WidgetMap settingsAccess;

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

    double longitude;
    double latitude;
  signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);

};

#endif // APIEVENEMENTSMV_H
