#ifndef APIESPACESVERTS_H
#define APIESPACESVERTS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QList>

#include "Abstract_API.h"

class ApiEspacesVerts : public Abstract_API
{
    Q_OBJECT

public:
    ApiEspacesVerts();
    int getId() override;
    QPixmap getPixmap() override;

private slots:
    void API_Call();
    void API_Results(QNetworkReply *reply);

public slots:
    void getInfo() override;

private:
    QNetworkAccessManager *manApiEspacesVerts;
    QNetworkReply *reply;
    QJsonDocument document;
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    QJsonValue val;
    QJsonObject jsObj;
    QJsonArray geoloc;
    QList<GeoObj> m_list;

    double longit;
    double lat;

signals:
    void callFinished(QList<Abstract_API::GeoObj>, API_index);
};

#endif // APIESPACESVERTS_H
