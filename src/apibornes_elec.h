#ifndef APIBORNES_ELEC_H
#define APIBORNES_ELEC_H

#include "Abstract_API.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "widgetmap.h"
#include "icon.h"

class ApiBornes_Elec : public Abstract_API
{
    Q_OBJECT

public:
    ApiBornes_Elec();
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
    bool isGeoBool(double geo);
signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);

};

#endif // APIBORNES_ELEC_H
