#ifndef APIKIOSQUES_H
#define APIKIOSQUES_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include"Abstract_API.h"


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
    void getInfo()override;
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

    signals:
    void callFinished(QList<Abstract_API::GeoObj>, API_Index);



};

#endif // APIKIOSQUES_H
