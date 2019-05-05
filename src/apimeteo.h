#ifndef APIMETEO_H
#define APIMETEO_H


#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

#include "Abstract_API.h"
#include "meteo.h"
#include "pollution.h"
#include "prevision.h"
#include "indiceuv.h"



class ApiMeteo : public Abstract_API
{
    Q_OBJECT

public:
    ApiMeteo();
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
    meteo *m_meteo;
    Pollution *p_pollution;
    IndiceUV *i_indice;
    Prevision *pm_prevision;

    double longitude;
    double latitude;
  signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);

};


#endif // APIMETEO_H
