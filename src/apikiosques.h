#ifndef APIKIOSQUES_H
#define APIKIOSQUES_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include "Abstract_API.h"
#include "icon.h"
#include "widgetmap.h"


class apikiosques : public Abstract_API
{
    Q_OBJECT
public:
    apikiosques();
    int getId()override;
    QPixmap getPixmap()override;
private slots:
    void API_call();
    void API_results(QNetworkReply *reply);

public slots:
    void getInfo() override;

private:
    QNetworkAccessManager *API_access;
    QNetworkReply *currentReply;
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray arr;
    QList<GeoObj>m_list;
    double latitude;
    double longitude;
    QString statut;
    QString adresse;
    QString latCentre;
    QString lonCentre;

    signals:
    void callFinished(QList<Abstract_API::GeoObj>, Abstract_API::API_index);



};

#endif // APIKIOSQUES_H
